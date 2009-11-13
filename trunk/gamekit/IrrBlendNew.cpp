
#if 0
#include "autogenerated/blender.h"
#include "bMain.h"
#include "bFile.h"


	int fileLen;
	char*memoryBuffer =  btReadBuffer(file,&fileLen);

	bParse::bFile blendFile(memoryBuffer, fileLen);
	blendFile.parse();
	{
	bParse::bMain* mainPtr = blendFile.getMain();

	// bMain contains sorted void* pointers.

	// Iterate through the scene.
	bParse::bListBasePtr *sceneBase = mainPtr->getScene();
	int numScenes = sceneBase->size();
	printf("File contains %i scene(s)\n", numScenes);

	bParse::bListBasePtr* objBase = mainPtr->getObject();
	int numObj = objBase->size();
	printf("File contains %i object(s)\n", numObj);
	
	bParse::bListBasePtr* camBase = mainPtr->getCamera();
	int numCam = camBase->size();
	printf("File contains %i camera(s)\n", numCam);
	


	for (int sce = 0; sce<numScenes; sce++)
	{
		// Get the scene structure.
		Blender::Scene *scene = (Blender::Scene*) sceneBase->at(sce);

		// ListBase pointers must be linked
		mainPtr->linkList(&scene->base);

		// Loop all objects in the scene.
		Blender::Base *base = (Blender::Base*)scene->base.first;
		while (base)
		{
			// Lookup object pointer.
			base->object = (Blender::Object*)mainPtr->findLibPointer(base->object);

			if (base->object)
			{
				Blender::Object *ob = base->object;
				printf("Current object : %s\n", ob->id.name);

				switch (ob->type)
				{
				//OB_MESH
				case 1:
					{
						printf("\tObject is a mesh\n");

						// Lookup data pointer
						ob->data = mainPtr->findLibPointer(ob->data);

						if (ob->data)
						{
							Blender::Mesh *me = (Blender::Mesh*)ob->data;
							printf("\t\tFound mesh data for %s\n", me->id.name);
							printf("\t\tTotal verts %i, faces %i\n", me->totvert, me->totface);
						}
					}break;

				//OB_LAMP
				case 10:
					{

						printf ("\tObject is a lamp\n");

						ob->data = mainPtr->findLibPointer(ob->data);
						if (ob->data)
						{
							Blender::Lamp *la = (Blender::Lamp*)ob->data;
							printf("\t\tFound lamp data for %s\n", la->id.name);
							printf("\t\tRGB, %f,%f,%f\n", la->r, la->g, la->b);
						}

					}break;
				//OB_CAMERA
				case 11:
					{
						printf ("\tObject is a camera\n");

						ob->data = mainPtr->findLibPointer(ob->data);
						if (ob->data)
						{
							Blender::Camera *cam = (Blender::Camera*)ob->data;
							printf("\t\tFound camera data for %s\n", cam->id.name);
							printf("\t\t(lens, near, far) %f,%f,%f\n", cam->lens, cam->clipsta, cam->clipend);
						}
					}break;
				}
			}
			base = (Blender::Base*)base->next;
		}
	}

	mainPtr->dumpChunks(blendFile.getFileDNA());
	}

	
	fseek(file, 0, SEEK_SET); /* seek to start */

#endif
