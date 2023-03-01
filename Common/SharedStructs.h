#ifndef __SHAREDSTRUCT_H__
#define __SHAREDSTRUCT_H__


#include <Windows.h>
#include <chrono>
#include <vector>


// ------------------------------
// Structs
// ------------------------------
typedef struct
{
	WORD Size;
	BYTE Key;
	BYTE CheckSum;
	WORD PacketId;
	WORD ClientId;
	DWORD TimeStamp;
} PacketHeader;

typedef struct {
	PacketHeader Header;
	char Password[12];
	char Login[16];

    char Unknow[52];
	UINT32 CliVer;
	UINT32 Unknow_84;
	unsigned char Mac[8];
	char Keys[12];
} p20D;
#endif //__SHAREDSTRUCT_H__