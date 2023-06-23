#include "main.h"
#include "libmy/lib.h"
#include "manage.h"
#include "nv.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
int main(void)
{
	MainInit();
	MainExec();

	return 0;
}
//---------------------------------------------------------------------------
EWRAM_CODE void MainInit(void)
{
	LibInit();
	ManageInit();
}
//---------------------------------------------------------------------------
IWRAM_CODE void MainExec(void)
{
	for(;;)
	{
		// ó·äOéQè∆
//		if(NvIsNext() == FALSE)
//		{
			// VBlankIntrWait
			SystemCall(5);
//		}

		LibExec();
		ManageExec();
	}
}
