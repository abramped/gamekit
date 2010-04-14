/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2010 Charlie C.

    Contributor(s): none yet.
-------------------------------------------------------------------------------
  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#include "OgreRoot.h"
#include "OgreRenderSystem.h"
#include "OgreSceneManager.h"
#include "OgreEntity.h"
#include "OgreSceneNode.h"
#include "OgreMaterialManager.h"
#include "OgreMesh.h"
#include "OgreSubMesh.h"

#include "gkEntity.h"
#include "gkGameObjectGroup.h"
#include "gkScene.h"
#include "gkEngine.h"
#include "gkLogger.h"
#include "gkUserDefs.h"
#include "gkActionManager.h"
#include "gkAction.h"
#include "gkSkeleton.h"

using namespace Ogre;


gkEntity::gkEntity(gkScene *scene, const gkString& name, gkObject::Loader* loader)
:       gkGameObject(scene, name, GK_ENTITY, loader),
        m_entityProps(), m_entity(0), m_animProps(), m_active(0), m_default(0),
        m_animTime(-1.0), m_blendTime(0.0), m_activeName(""),
        m_skeleton(0)
{
}


void gkEntity::loadImpl(void)
{
    gkGameObject::loadImpl();

    if (m_entity != 0)
        return;

    SceneManager *manager = m_scene->getManager();

    if (m_entityProps.prefab != -1)
        m_entity = manager->createEntity(m_name, (SceneManager::PrefabType)m_entityProps.prefab);
    else
    {
        if (m_entityProps.source.empty())
            return;

        m_entity = manager->createEntity(m_name, m_entityProps.source);
        if (m_parent && m_parent->getType() == GK_SKELETON)
        {
            // attach entity to skeleton
            m_skeleton = static_cast<gkSkeleton*>(m_parent);
            m_skeleton->setEntity(m_entity);
        }
    }
    if (!m_startPose.empty())
        _resetPose();

    // moved static & ghost check to gkGameObjectLoader::setEntity
    m_entity->setCastShadows(m_entityProps.casts);
    m_node->attachObject(m_entity);

    if (m_instance != 0 && gkEngine::getSingleton().getUserDefs().buildInstances)
    {
        // only do something if more than one object
        if (m_instance->getGroup()->getInstances().size() > 1) 
        {
            Ogre::InstancedGeometry *geom = m_instance->getGroup()->getGeometry();
            if (!geom)
            {
                geom = manager->createInstancedGeometry(m_instance->getGroup()->getName().str());
                m_instance->getGroup()->attachGeometry(geom);
            }

            if (geom)  
                geom->addSceneNode(m_node);
        }
    }
    // else no instancing but we can benefit from sharing a single mesh
}


void gkEntity::unloadImpl(void)
{
    if (m_entity != 0)
    {
        // sanity check
        GK_ASSERT(m_scene);
        SceneManager *manager = m_scene->getManager();
        GK_ASSERT(manager);

        if (!m_startPose.empty())
        {
            _resetPose();
            m_default = 0;
        }
        if (m_node)
            m_node->detachObject(m_entity);

        manager->destroyEntity(m_entity);
        m_entity = 0;


        m_skeleton = 0;

    }

    gkGameObject::unloadImpl();
}

void gkEntity::playAction(const gkString& act, gkScalar blend)
{
    if (m_skeleton)
    {
        if (m_active != 0)
        {
            if (act != m_active->getName())
            {
                if (m_skeleton->hasAction(act))
                {
                    m_active = m_skeleton->getAction(act);
                    m_actionMgr.setAction(m_active);
                }
                else return;
            }

            m_active->setBlendFrames(blend);
            m_animTime = 0.416f;
            m_actionMgr.update(m_animTime);
        }
    }

}


gkObject *gkEntity::clone(const gkString &name)
{
    // will need to set other properties in a bit!
    return new gkEntity(m_scene, name, m_manual ? m_manual->clone() : 0);
}



void gkEntity::_resetPose(void)
{
    if (m_skeleton)
    {
        if (!m_startPose.empty())
        {

            if (m_skeleton->hasAction(m_startPose))
            {
                m_active = m_skeleton->getAction(m_startPose);
                m_actionMgr.setAction(m_active);
                m_active->evaluate(gkEngine::getSingleton().getUserDefs().startframe);
            }
        }
    }
    m_animTime = 0;
}


void gkEntity::updateAnimations(void)
{
}
