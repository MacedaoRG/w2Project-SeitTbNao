#include "cServer.h"
#include "Basedef.h"
#include "SendFunc.h"
#include "GetFunc.h"

bool CUser::RequestRessuctPlayer(PacketHeader *Header)
{// 00423207
	if(pUser[clientId].Status != USER_PLAY || pMob[clientId].Mobs.Player.Status.curHP > 0)
	{
		SendHpMode(clientId);

		return true;
	}

	pMob[clientId].Mobs.Player.Status.curHP = 2;
	
	CrackCount = 0;

	SendScore(clientId);
	SendSetHpMp(clientId);

	DoRecall(clientId);

	SendEtc(clientId);
	Log(clientId, LOG_INGAME, "Usuario reviveu");
	return true;
}