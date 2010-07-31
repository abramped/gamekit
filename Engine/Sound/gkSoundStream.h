/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2010 Nestor Silveira & Charlie C.

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
#ifndef _gkSoundStream_h_
#define _gkSoundStream_h_

#include "Utils/utCommon.h"



class gkSoundStream
{
	// Sound playback stream (read only).

public:
	virtual ~gkSoundStream() {}

	// read a temporary block, should equal getBitsPerSecond!
	virtual const char *read(UTsize len, UTsize &br) = 0;

	// read a temporary block, should equal getBitsPerSecond!
	virtual const char *read(UTsize pos, UTsize len, UTsize &br) = 0;

	// end of stream test
	virtual bool        eos(void) = 0;


	// seek to new position
	virtual void        seek(UTsize pos, int way) = 0;

	// OpenAL fromat code
	virtual int         getFormat(void)         const = 0;

	// Samples per second
	virtual int         getSampleRate(void)     const = 0;

	// Read block size
	virtual int         getBitsPerSecond(void)  const = 0;
};



#endif//_gkSoundStream_h_
