#include "manage.h"
#include "libmy/irq.arm.h"
#include "ags.arm.h"
#include "img.h"
#include "anm.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void ManageInit(void)
{
	AgsInit();

	IrqSetVbl();
}
//---------------------------------------------------------------------------
EWRAM_CODE void ManageExec(void)
{
	for(;;)
	{
		VBlankIntrWait();

		if(AnmIsPause() == false)
		{
			AnmExec();
		}
	}
}
