/*
	"$Id: CpuSet.c,v 1.3 2005/08/23 17:02:06 wntrmute Exp $"

	libgba bios CpuSet functions

	Copyright 2003-2004 by Dave Murphy.

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Library General Public
	License as published by the Free Software Foundation; either
	version 2 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Library General Public License for more details.

	You should have received a copy of the GNU Library General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
	USA.

	Please report all bugs and problems through the bug tracker at
	"http://sourceforge.net/tracker/?group_id=114505&atid=668551".

	"$Header: /cvsroot/devkitpro/libgba/src/CpuSet.c,v 1.3 2005/08/23 17:02:06 wntrmute Exp $"

*/
#include "sys.arm.h"

//---------------------------------------------------------------------------------
IWRAM_CODE void CpuSet( const void *source,  void *dest, u32 mode)
{
	SystemCall(11);
}
//---------------------------------------------------------------------------------
IWRAM_CODE void CpuFastSet( const void *source,  void *dest, u32 mode)
{
	SystemCall(12);
}
//---------------------------------------------------------------------------------
IWRAM_CODE void LZ77UnCompWram(void *source, void *dest)
{
	SystemCall(17);
}
//---------------------------------------------------------------------------------
IWRAM_CODE void LZ77UnCompVram(void *source, void *dest)
{
	SystemCall(18);
}
