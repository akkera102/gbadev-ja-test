#include "manage.h"
#include "libmy/libmy.h"


//---------------------------------------------------------------------------
int main(void)
{
	LibMyInit();

	ManageInit();
	ManageExec();

	return 0;
}
