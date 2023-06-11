#include "main.h"
#include "libmy/libmy.h"
#include "manage.h"
#include "nv.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE int main(void)
{
	MainInit();
	MainExec();

	return 0;
}
//---------------------------------------------------------------------------
EWRAM_CODE void MainInit(void)
{
	LibMyInit();
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

		LibMyExec();
		ManageExec();
	}
}
