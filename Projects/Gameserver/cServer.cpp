#include "cServer.h"

STRUCT_GUI_INFO GUI;
STRUCT_SERVER_INFO sServer;
STRUCT_GAMESERVER sData;
char FailAccount[16][16];
unsigned int CurrentTime;


void AddFailAcount(char *account)
{
	for(INT32 LOCAL_1 = 0; LOCAL_1 < 16; LOCAL_1 ++)
	{
		if(!FailAccount[LOCAL_1][0])
		{
			strncpy_s(FailAccount[LOCAL_1], account, 16);

			break;
		}
	}
}

INT32 CheckFailAccount(char *account)
{
	INT32 LOCAL_1 = 0,
		  LOCAL_2 = 0;

	for(; LOCAL_2 < 16; LOCAL_2 ++)
	{
		if(FailAccount[LOCAL_2][0] && !strncmp(account, FailAccount[LOCAL_2], 16))
			LOCAL_1++;
	}

	return LOCAL_1;
}