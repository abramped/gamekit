/* Copyright (C) 2006 Charlie C
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/
// Auto generated from makesdna dna.c
#ifndef __BLENDER_RENDERDATA__H__
#define __BLENDER_RENDERDATA__H__


// -------------------------------------------------- //
#include "blender_Common.h"
#include "blender_FFMpegCodecData.h"
#include "blender_ListBase.h"
#include "blender_rctf.h"
#include "blender_rcti.h"

namespace Blender {


    // ---------------------------------------------- //
    class RenderData
    {
    public:
        AviCodecData *avicodecdata;
        QuicktimeCodecData *qtcodecdata;
        FFMpegCodecData ffcodecdata;
        int cfra;
        int sfra;
        int efra;
        int images;
        int framapto;
        short flag;
        short threads;
        float ctime;
        float framelen;
        float blurfac;
        float edgeR;
        float edgeG;
        float edgeB;
        short fullscreen;
        short xplay;
        short yplay;
        short freqplay;
        short depth;
        short attrib;
        short rt1;
        short rt2;
        short stereomode;
        short dimensionspreset;
        short filtertype;
        short size;
        short maximsize;
        short xsch;
        short ysch;
        short xasp;
        short yasp;
        short xparts;
        short yparts;
        short winpos;
        short planes;
        short imtype;
        short subimtype;
        short bufflag;
        short quality;
        short scemode;
        int mode;
        short renderer;
        short ocres;
        short rpad[2];
        short alphamode;
        short osa;
        short frs_sec;
        short edgeint;
        rctf safety;
        rctf border;
        rcti disprect;
        ListBase layers;
        short actlay;
        short pad;
        int pad2;
        float gauss;
        float postmul;
        float postgamma;
        float posthue;
        float postsat;
        float dither_intensity;
        short bake_osa;
        short bake_filter;
        short bake_mode;
        short bake_flag;
        short GIquality;
        short GIcache;
        short GImethod;
        short GIphotons;
        short GIdirect;
        short YF_AA;
        short YFexportxml;
        short YF_nobump;
        short YF_clamprgb;
        short yfpad1;
        int GIdepth;
        int GIcausdepth;
        int GIpixelspersample;
        int GIphotoncount;
        int GImixphotons;
        float GIphotonradius;
        int YF_numprocs;
        int YF_raydepth;
        int YF_AApasses;
        int YF_AAsamples;
        float GIshadowquality;
        float GIrefinement;
        float GIpower;
        float GIindirpower;
        float YF_gamma;
        float YF_exposure;
        float YF_raybias;
        float YF_AApixelsize;
        float YF_AAthreshold;
        char backbuf[160];
        char pic[160];
        char ftype[160];
    };
}


#endif//__BLENDER_RENDERDATA__H__
