#ifndef __CFILEDB_H__
#define __CFILEDB_H__

#include <ctime>
#include "Basedef.h"
#include <memory>

struct STRUCT_ACCOUNT_DATABASE
{
	INT32 Login{};
	INT32 Slot{};
	bool IsBanned;

	STRUCT_ACCOUNT Account{};
	UINT8 Skillbar[4][8]{ {} };  // Possivel segunda barra de skill
};

class CLog;

class CFileDB
{
public:
	STRUCT_ACCOUNT_DATABASE *Account{ nullptr };

	CFileDB();

	INT32 GetIndex(char *accountName);
	INT32 GetIndex(INT32 server, INT32 id);
	INT32 SendDBMessage(INT32 server, INT32 id, const char *msg);
	INT32 DBReadAccount(STRUCT_ACCOUNT *file);
	INT32 DBWriteAccount(STRUCT_ACCOUNT *file);
	INT32 DBExportAccount(STRUCT_ACCOUNT *file);

	INT32 CreateCharacter(const char *ac, char *ch);
	INT32 DeleteCharacter(const char *ch, char *ac);

	INT32 GetEncPassword(int idx, int *Enc);

	INT32 SendDBSignal(INT32 server, INT32 clientId, INT32 signal);
	INT32 SendDBSignalParm2(INT32 server, INT32 clientId, INT32 packetId, INT32 parm1, INT32 parm2);
	INT32 SendDBSignalParm3(INT32 server, INT32 clientId, INT32 packetId, INT32 parm1, INT32 parm2, INT32 parm3);
	INT32 SendDBSignalParm1(INT32 server, INT32 clientId, INT32 packetId, INT32 parm1);

	void SendAdditionalAccountInfo(INT32 conn, INT32 clientId);
	INT32 ProcessMessage(char *msg, INT32 conn);
	
	void DBGetSelChar(st_CharList *p, STRUCT_ACCOUNT *file);

	void SendDBSavingQuit(INT32 id, INT32 mode);
	void AddAccountList(INT32 index);
	void RemoveAccountList(INT32 index);
	void GetAccountByChar(char *acc, char *cha);
};

extern CFileDB cFileDB;

#endif