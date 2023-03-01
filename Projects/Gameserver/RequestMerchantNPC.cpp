#include "cServer.h"
#include "Basedef.h"
#include "SendFunc.h"
#include "GetFunc.h"
#include "CNPCGener.h"
#include "CEventManager.h"
#include <algorithm>

void NPCEvento(int clientId, int npcId)
{
	// NPCs sao baseados no seu level
	// O Level deve iniciar por 500 (primeiro npc) e terminar ata 509
	int mobId = pMob[npcId].Mobs.Player.bStatus.Level - 500;

	// Checagem para limite de NPCs
	if(mobId < 0 || mobId >= MAX_NPCEVENTO)
		return;

	char szTMP[256];
	STRUCT_NPC_EVENT *ev = &npcEvent[mobId];

	if(ev->goldRequired > pMob[clientId].Mobs.Player.Gold)
	{
		sprintf_s(szTMP, "Sao necessarios %d de gold", ev->goldRequired);

		SendSay(npcId, szTMP);
		return;
	}

	for(int i = 0; i < 10 ; i++)
	{
		STRUCT_ITEM *item = &ev->itemRequired[i];
		if(item->Index <= 0 || item->Index >= 6500)
			continue;

		// Quantidade de itens possuados pelo usuario
		int amountItem = GetInventoryAmount(clientId, item->Index);
		int reqAmount = ev->amountRequired[i];

		// Checagem se possui a quantidade necessaria
		if(amountItem < reqAmount)
		{
			SendSay(npcId, "Traga-me [%02d] %s", reqAmount, ItemList[item->Index].Name);

			return;
		}

		int eventId = -1;
		for(int g = 0; g < 3; g++)
		{
			if(item->Effect[g].Index == 41)
			{
				eventId = item->Effect[g].Value;
				break;
			}
		}

		if(reqAmount > 0)
		{
			for(INT32 x = 0; x < 30; x++)
			{
				INT32 itemId = pMob[clientId].Mobs.Player.Inventory[x].Index;
				if(itemId != item->Index)
					continue;

				// Checa se o item que esta buscando a necessario ter o ID DO EVENTO
				// Se for, busca o adicional no item ;)
				bool isEvent = true;
				if(eventId != -1)
				{
					isEvent = false;

					for(int w = 0; w < 3; w++)
					{
						if(pMob[clientId].Mobs.Player.Inventory[x].Effect[w].Index == 41)
						{
							if(pMob[clientId].Mobs.Player.Inventory[x].Effect[w].Value == eventId)
							{
								isEvent = true;

								break;
							}
						}
					}
				}

				// Se deu continue a porque o item precisa de um eventId poram nao foi encontrado
				if(!isEvent)
					continue;

				INT32 totalAmount = 1;
				for(INT32 o = 0; o < 3; o++)
				{
					if(pMob[clientId].Mobs.Player.Inventory[x].Effect[o].Index == 61)
					{
						totalAmount = pMob[clientId].Mobs.Player.Inventory[x].Effect[0].Value;

						break;
					}
				}

				if(totalAmount <= 0)
					totalAmount = 1;

				reqAmount -= totalAmount;
			}

			if(pMob[clientId].Mobs.Player.Inventory[60].Index == 3467)
			{
				float remainingDays = TimeRemaining(pMob[clientId].Mobs.Player.Inventory[60].EFV1, pMob[clientId].Mobs.Player.Inventory[60].EFV2, pMob[clientId].Mobs.Player.Inventory[60].EFV3 + 1900);
				for(INT32 x = 30; x < 45; x++)
				{
					INT32 itemId = pMob[clientId].Mobs.Player.Inventory[x].Index;
					if(itemId != item->Index)
						continue;

					// Checa se o item que esta buscando a necessario ter o ID DO EVENTO
					// Se for, busca o adicional no item ;)
					bool isEvent = true;
					if(eventId != -1)
					{
						isEvent = false;

						for(int w = 0; w < 3; w++)
						{
							if(pMob[clientId].Mobs.Player.Inventory[x].Effect[w].Index == 41)
							{
								if(pMob[clientId].Mobs.Player.Inventory[x].Effect[w].Value == eventId)
								{
									isEvent = true;

									break;
								}
							}
						}
					}

					// Se deu continue a porque o item precisa de um eventId poram nao foi encontrado
					if(!isEvent)
						continue;

					INT32 totalAmount = 1;
					for(INT32 o = 0; o < 3; o++)
					{
						if(pMob[clientId].Mobs.Player.Inventory[x].Effect[o].Index == 61)
						{
							totalAmount = pMob[clientId].Mobs.Player.Inventory[x].Effect[0].Value;

							break;
						}
					}

					if(totalAmount <= 0)
						totalAmount = 1;

					reqAmount -= totalAmount;
				}
			}

			if(pMob[clientId].Mobs.Player.Inventory[61].Index == 3467)
			{
				float remainingDays = TimeRemaining(pMob[clientId].Mobs.Player.Inventory[61].EFV1, pMob[clientId].Mobs.Player.Inventory[61].EFV2, pMob[clientId].Mobs.Player.Inventory[61].EFV3 + 1900);
				
				for(INT32 x = 45; x < 60; x++)
				{
					INT32 itemId = pMob[clientId].Mobs.Player.Inventory[x].Index;
					if(itemId != item->Index)
						continue;

					// Checa se o item que esta buscando a necessario ter o ID DO EVENTO
					// Se for, busca o adicional no item ;)
					bool isEvent = true;
					if(eventId != -1)
					{
						isEvent = false;

						for(int w = 0; w < 3; w++)
						{
							if(pMob[clientId].Mobs.Player.Inventory[x].Effect[w].Index == 41)
							{
								if(pMob[clientId].Mobs.Player.Inventory[x].Effect[w].Value == eventId)
								{
									isEvent = true;

									break;
								}
							}
						}
					}

					// Se deu continue a porque o item precisa de um eventId poram nao foi encontrado
					if(!isEvent)
						continue;

					INT32 totalAmount = 1;
					for(INT32 o = 0; o < 3; o++)
					{
						if(pMob[clientId].Mobs.Player.Inventory[x].Effect[o].Index == 61)
						{
							totalAmount = pMob[clientId].Mobs.Player.Inventory[x].Effect[0].Value;

							break;
						}
					}

					if(totalAmount <= 0)
						totalAmount = 1;

					reqAmount -= totalAmount;
				}
			}
		}

		if(reqAmount > 0)
		{
			SendSay(npcId, "Traga-me [%02d] %s", reqAmount, ItemList[item->Index].Name);

			return;
		}
	}

	// Retirado dos itens
	// Isto deixara os slots vazios
	for(int i = 0 ; i < 10; i++)
	{
		STRUCT_ITEM *item = &ev->itemRequired[i];
		if(item->Index <= 0 || item->Index >= MAX_ITEMLIST)
			continue;
		
		INT32 reqAmount = ev->amountRequired[i];

		int eventId = -1;
		for(int g = 0; g < 3; g++)
		{
			if(item->Effect[g].Index == 41)
			{
				eventId = item->Effect[g].Value;
				break;
			}
		}

		INT32 itemId = item->Index;
		for(INT32 t = 0; t < 60 ; t++)
		{
			if(itemId != pMob[clientId].Mobs.Player.Inventory[t].Index)
				continue;

			// Checa se o item que esta buscando a necessario ter o ID DO EVENTO
			// Se for, busca o adicional no item ;)
			bool isEvent = true;
			if(eventId != -1)
			{
				isEvent = false;

				for(int w = 0; w < 3; w++)
				{
					if(pMob[clientId].Mobs.Player.Inventory[t].Effect[w].Index == 41)
					{
						if(pMob[clientId].Mobs.Player.Inventory[t].Effect[w].Value == eventId)
						{
							isEvent = true;

							break;
						}
					}
				}
			}

			// Se deu continue a porque o item precisa de um eventId poram nao foi encontrado
			if(!isEvent)
				continue;

			
			if(pMob[clientId].Mobs.Player.Inventory[t].Index == itemId)
			{
				while(pMob[clientId].Mobs.Player.Inventory[t].Index == itemId)
				{
					AmountMinus(&pMob[clientId].Mobs.Player.Inventory[t]);

					reqAmount--;
					if(reqAmount <= 0)
						break;
				}

				SendItem(clientId, SlotType::Inv, t, &pMob[clientId].Mobs.Player.Inventory[t]);
			}

			if(reqAmount <= 0)
				break;
		}
	}
	
	int gold = pMob[clientId].Mobs.Player.Gold - ev->goldRequired;
	if(gold < 0)
		gold = 0;

	if(gold > 2000000000)
		gold = 2000000000;

	pMob[clientId].Mobs.Player.Gold = gold;

	SendSignalParm(clientId, clientId, 0x3AF, gold);

	// Geraaao do RAND
	int _rand = Rand () % 300;

	// Loop para ver qual item sera entregue
	for(int i = 0 ; i < 10 ; i++)
	{
		// Pegea a rate atual do item
		int interator = ev->Rates[i];

		// Checa se o item vai ser entregue
		// Caso esteja abaixo do valor gerado o item a entregue
		if(interator < _rand)
			continue;

		for(int x = 0; x < 10; x++)
		{
			// Ponteiro para o item que sera recebido
			STRUCT_ITEM *item = &ev->itemEarned[i][x];
			
			if(item->Index <= 0 || item->Index >= 6500)
				continue;

			if(item->Index == 3214) 
			{
				pMob[clientId].Mobs.Player.Gold += 500000;

				SendSignalParm(clientId, SERVER_SIDE, clientId, pMob[clientId].Mobs.Player.Gold);
				
				// Log do item recebido
				Log(clientId, LOG_INGAME, "[EVENTO BONE]  NPC %d - Recebido 500.000 de gold - %d %d", mobId, _rand, interator);
				
				// Envia a mensagem de que o item chegou
				SendClientMessage(clientId, "!Chegou 500.000 de gold");
				continue;
			}

			// Busca por um slot vazio no inventario do usuario
			int slotId = GetFirstSlot(clientId, 0);
			if(slotId == -1)
			{
				// Log para item que caiu no chao
				Log(clientId, LOG_INGAME, "[EVENTO BONE] NPC %d - Item caiu no chao [%s] [%d] [%d %d %d %d %d %d] - %d %d", mobId, ItemList[item->Index].Name, item->Index, item->EF1, 
					item->EFV1, item->EF2, item->EFV2, item->EF3, item->EFV3, _rand, interator);

				// Envia mensagem dizendo que falta espaa no inventario
				SendClientMessage(clientId, "!Falta espaao no inventario");

				// Envia a mensagem de que o item chegou
				SendClientMessage(clientId, "!Chegou um item: [%s]", ItemList[item->Index].Name);
			}
			else
			{
				// Copia o item entregue para o personagem
				memcpy(&pMob[clientId].Mobs.Player.Inventory[slotId], item, sizeof STRUCT_ITEM);

				// Atualiza o slot
				SendItem(clientId, SlotType::Inv, slotId, item);

				if(mobId == 5 || mobId == 6)
					Log(SERVER_SIDE, LOG_INGAME, "[EVENTO BONE]  %s - NPC %d - Recebido [%s] [%d] [%d %d %d %d %d %d] - %d %d", pMob[clientId].Mobs.Player.Name, mobId, ItemList[item->Index].Name, item->Index, item->EF1, 
						item->EFV1, item->EF2, item->EFV2, item->EF3, item->EFV3, _rand, interator);

				// Log do item recebido
				Log(clientId, LOG_INGAME, "[EVENTO BONE]  NPC %d - Recebido [%s] [%d] [%d %d %d %d %d %d] - %d %d", mobId, ItemList[item->Index].Name, item->Index, item->EF1, 
					item->EFV1, item->EF2, item->EFV2, item->EF3, item->EFV3, _rand, interator);
				
				// Envia a mensagem de que o item chegou
				SendClientMessage(clientId, "!Chegou um item: [%s]", ItemList[item->Index].Name);
			}
		}
		
		if(ev->msg[i][0])
			SendClientMessage(clientId, ev->msg[i]);

		if(ev->Pos[i].X != 0 && ev->Pos[i].Y != 0)
		{
			Teleportar(clientId, ev->Pos[i].X, ev->Pos[i].Y);

			Log(clientId, LOG_INGAME, "Teleportado para area %d %d (%d %d)", ev->Pos[i].X, ev->Pos[i].Y, pMob[clientId].Target.X, pMob[clientId].Target.Y);
		}

		// Para o loop pelas checagens de rates
		break;
	}

	static const char *szRomano[] = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IV", "X"};

	if(ev->npcId[0])
		sprintf_s(szTMP, "%s", ev->npcId);
	else
		sprintf_s(szTMP, "NPC %s", szRomano[mobId]);

	SendSay(npcId, szTMP);
}

bool CUser::RequestMerchantNPC(PacketHeader *Header)
{
	p28B *p = (p28B*)(Header); // LOCAL_523

	INT32 npcId = p->npcId;
	INT32 LOCAL_525 = p->click;

	if(npcId < MAX_PLAYER || npcId >= 30000)
		return false;

	auto distance = GetDistance(pMob[npcId].Target.X, pMob[npcId].Target.Y, pMob[clientId].Target.X, pMob[clientId].Target.Y);
	if (distance > VIEWGRIDX / 2)
	{
		AddCrackError(clientId, 2, CRACK_USER_PKTHACK);

		Log(clientId, LOG_INGAME, "Clicado no NPC %s fora do range %ux %uy %ux %uy. Distancia: %d", pMob[npcId].Mobs.Player.Name, pMob[npcId].Target.X, pMob[npcId].Target.Y, pMob[clientId].Target.X, pMob[clientId].Target.Y, distance);
		return true;
	}

	INT32 LOCAL_526 = -1;
	INT32 LOCAL_527 = pMob[npcId].Mobs.Player.Info.Value;

	if(LOCAL_527 == 90)	LOCAL_526 = 0;
	if(LOCAL_527 == 4)	LOCAL_526 = 1;
	if(LOCAL_527 == 10)	LOCAL_526 = 2;
	if(LOCAL_527 == 11)	LOCAL_526 = 3;
	if(LOCAL_527 == 12) LOCAL_526 = 4;
	if(LOCAL_527 == 13) LOCAL_526 = 5;
	if(LOCAL_527 == 14)	LOCAL_526 = 6;
	if(LOCAL_527 == 15)	LOCAL_526 = 7;
	if(LOCAL_527 == 20)	LOCAL_526 = 8;
	if(LOCAL_527 == 19)	LOCAL_526 = 9;
	if(LOCAL_527 == 26)	LOCAL_526 = 58;
	if(LOCAL_527 == 31)	LOCAL_526 = 13;
	if(LOCAL_527 == 30)	LOCAL_526 = 14;
	if(LOCAL_527 == 36)	LOCAL_526 = 8;
	if(LOCAL_527 == 40)	LOCAL_526 = 9;
	if(LOCAL_527 == 41)	LOCAL_526 = 10;
	if(LOCAL_527 == 43)	LOCAL_526 = 11;
	if(LOCAL_527 == 58)	LOCAL_526 = 1;
	if(LOCAL_527 == 62)	LOCAL_526 = 15;
	if(LOCAL_527 == 8)	LOCAL_526 = 100;
	if(LOCAL_527 == 51)	LOCAL_526 = 51;

	INT32 race = pMob[npcId].Mobs.Player.bStatus.Merchant.Merchant,
		  face = pMob[npcId].Mobs.Player.Equip[0].Index;

	Log(clientId, LOG_INGAME, "Clicado no NPC [%s]. Face %d. Race: %d. GenerateId: %d. Posiaao do usuario: %ux %uy. Posiaao do NPC: %dx %dy", pMob[npcId].Mobs.Player.Name, face, race, pMob[npcId].GenerateID, pMob[clientId].Target.X, pMob[clientId].Target.Y, pMob[npcId].Target.X, pMob[npcId].Target.Y);

	// 00428D24
	INT32 LOCAL_528 = 1,
		  LOCAL_529 = 1,
		  LOCAL_530 = 1;

	LOCAL_528 <<= LOCAL_526;
	LOCAL_529 = LOCAL_529 << (LOCAL_526 + 1);
	LOCAL_530 = LOCAL_530 << (LOCAL_526 - 1);

#pragma region NPC CONFIGURADO POR TXT
	if(pMob[npcId].Mobs.Player.bStatus.Level >= 700 && pMob[npcId].Mobs.Player.bStatus.Level <= 750)
	{
		STRUCT_MOB *player = &pMob[clientId].Mobs.Player;
		STRUCT_MOB *mob = &pMob[npcId].Mobs.Player;

		INT32 questId = mob->bStatus.Level - 700;
		if(questId < 0 || questId >= MAX_NPCQUEST)
			return true;

		Log(clientId, LOG_INGAME, "O NPC %s foi clicado. QuestId: %d", mob->Name, questId);

		char szTMP[108];
		STRUCT_NPCQUEST_CFILE *npc = &questNPC[questId];

		for(INT32 i = 0; i < MAX_NPCQUEST_CONDITION;i ++)
		{
			stNPCQuest_Condition *cond = &npc->Condition[i];
			if(cond->maxLevel != 0)
			{
				INT32 level = player->bStatus.Level;
				if(level < cond->minLevel || level > cond->maxLevel)
				{
					SendSay(npcId, cond->Speech);

					return true;
				}
			}
			else if(cond->Equip.ItemID != 0)
			{
				if(player->Equip[cond->Equip.Slot].Index != cond->Equip.ItemID)
				{
					SendSay(npcId, cond->Speech);

					return true;
				}
			}
			else if(cond->Exp)
			{
				if(player->Exp < cond->Exp)
				{
					SendSay(npcId, cond->Speech);

					return true;
				}
			}
			else if(cond->Gold)
			{
				if(player->Gold < cond->Gold)
				{
					SendSay(npcId, cond->Speech);

					return true;
				}
			}
			else if(cond->Evolution)
			{
				// 0 = all, 1 = mortal, 2 = arch, 3 = cele, 4 = sub, 5 = mortal + arch, 6 = arch + cele, 7 = arch+cele+sub, 8=cele+sub
				INT32 ev = player->Equip[0].EFV2;

				bool can = true;
				switch(cond->Evolution)
				{
				case 1:
				case 2:
				case 3:
				case 4:
					if(ev != 1)
						can = false;

					break;

				case 5:
					if(ev != 1 && ev != 2)
						can = false;
				
					break;

				case 6:
					if(ev != 2 && ev != 3)
						can = false;
			
					break;
				case 7:
					if(ev != 2 && ev != 3 && ev != 4)
						can = false;
				
					break;
				case 8:
					if(ev != 3 && ev != 4)
						can = false;

					break;
				}

				if(!can)
				{
					SendSay(npcId, cond->Speech);

					return true;
				}
			}
			else if(cond->Class)
			{
				if((player->ClassInfo + 1) != cond->Class)
				{
					SendSay(npcId, cond->Speech);

					return true;
				}
			}
			else // item
			{
				for(INT32 x = 0; x < MAX_NPCQUEST_CONDITION_ITEM; x++)
				{
					if(!cond->Item.Amount)
						continue;
				
					int amountItem = GetInventoryAmount(clientId, cond->Item.Item);
					if(amountItem < cond->Item.Amount)
					{
						sprintf_s(szTMP, "Traga-me [%d] %s", cond->Item.Amount, ItemList[cond->Item.Item].Name);
						SendSay(npcId, szTMP);

						return true;
					}
				}
			}
		}

		Log(clientId, LOG_INGAME, "O usuario tinha todos os requisitos para a troca, entregando itens");

		// Se chegamos ata aqui, quer dizer que o jogador possuia todos os requerimentosn necessarios.
		// entao comeaamos a entregar todos as premiaaase
		for(INT32 i = 0; i < MAX_NPCQUEST_REWARD; i++)
		{
			stNPCQuest_Reward *r = &npc->Reward[i];
			if(r->Exp != 0)
			{
				if(r->Exp > 0)
				{
					while(player->Exp >= g_pNextLevel[player->Equip[0].EFV2][player->bStatus.Level])
						player->bStatus.Level ++;
				}
				else
				{
					while(player->bStatus.Level > 0 && player->Exp < g_pNextLevel[player->Equip[0].EFV2][player->bStatus.Level - 1])
						player->bStatus.Level --;
				}

				Log(clientId, LOG_INGAME, "Foram removidos %d de experiancia", r->Exp);
			}

			else if(r->Level)
			{
				INT32 level = player->bStatus.Level + r->Level;

				if(player->Equip[0].EFV2 >= 3)
				{
					if(level > 199)
						level = 199;

					player->bStatus.Level = level;
					player->Exp = g_pNextLevel[player->Equip[0].EFV3][player->bStatus.Level];
				}
				else
				{
					if(level > 399)
						level = 399;

					player->bStatus.Level = level;
					player->Exp = g_pNextLevel[player->Equip[0].EFV3][player->bStatus.Level];
				}

				Log(clientId, LOG_INGAME, "Foram adicionados %d leveis", level);
			}
			else if(r->Gold)
			{
				INT64 gold = player->Gold + r->Gold;

				if(gold >= 2000000000LL)
					gold = 2000000000LL;

				player->Gold = static_cast<int>(gold);
				Log(clientId, LOG_INGAME, "Foram adiciaondos %d gold", r->Gold);
			}
			else if (r->Teleport.X != 0 && r->Teleport.Y != 0)
			{
				Teleportar(clientId, r->Teleport.X, r->Teleport.Y);

				Log(clientId, LOG_INGAME, "Usuario teleportado para %dx %dy", r->Teleport.X, r->Teleport.Y);
			}
			else if(r->Equip.Item.Index != 0)
			{
				Log(clientId, LOG_INGAME, "Setado o item %s do slot %d. Item anteriormente no slot: %s", r->Equip.Item.toString().c_str(), r->Equip.Slot, player->Equip[r->Equip.Slot].toString().c_str());

				memset(&player->Equip[r->Equip.Slot], 0, sizeof STRUCT_ITEM);
				memcpy(&player->Equip[r->Equip.Slot], &r->Equip.Item, sizeof STRUCT_ITEM);

				SendItem(clientId, SlotType::Equip, r->Equip.Slot, &player->Equip[r->Equip.Slot]);
			}
			else
			{
				for(INT32 x = 0; x < MAX_NPCQUEST_REWARD_ITEM; x++)
				{
					if(r->Item[x].Amount == 0)
						continue;

					INT32 slotId = GetFirstSlot(clientId, 0);
					if (slotId == -1)
					{
						Log(clientId, LOG_INGAME, "Item %s nao recebido por falta de espaao no inventario", r->Item[x].Item.toString().c_str());

						continue;
					}

					memcpy(&player->Inventory[slotId], &r->Item[x].Item, sizeof STRUCT_ITEM);
					SendItem(clientId, SlotType::Inv, slotId, &player->Inventory[slotId]);

					Log(clientId, LOG_INGAME, "Item %s entregue", r->Item[x].Item.toString().c_str());
				}
			}

			if(r->Speech[0])
				SendSay(npcId, r->Speech);
		}

		// A partir deste ponto, o sistema vai comeaar a remover o que for necessario
		if(npc->Remove.Gold)
		{
			if(player->Gold < npc->Remove.Gold)
				player->Gold = 0;
			else
				player->Gold -= npc->Remove.Gold;

			Log(clientId, LOG_INGAME, "Removido %d gold", npc->Remove.Gold);
		}

		if(npc->Remove.Exp)
		{
			Log(clientId, LOG_INGAME, "Experiancia atual: %lld. Experiancia removida: %d", player->Exp, npc->Remove.Exp);

			if(player->Exp + npc->Remove.Exp > 4200000000000)
				player->Exp = 4200000000000;
			else
				player->Exp += npc->Remove.Exp;

			while(player->bStatus.Level > 0 && player->Exp < g_pNextLevel[player->Equip[0].EFV2][player->bStatus.Level - 1])
				player->bStatus.Level --;
		}

		if(npc->Remove.Equip.Item != 0)
		{
			if (npc->Remove.Equip.Item == player->Equip[npc->Remove.Equip.Slot].Index)
			{
				Log(clientId, LOG_INGAME, "Item %s equipado em %d removido", player->Equip[npc->Remove.Equip.Slot].toString().c_str(), npc->Remove.Equip.Slot);
				memset(&player->Equip[npc->Remove.Equip.Slot], 0, sizeof STRUCT_ITEM);

				SendItem(clientId, SlotType::Equip, npc->Remove.Equip.Slot, &player->Equip[npc->Remove.Equip.Slot]);
			}
			else
				Log(clientId, LOG_INGAME, "Item %d nao removido por estar equipado.", npc->Remove.Equip.Item);
		}

		for(INT32 i = 0; i < MAX_NPCQUEST_REWARD;i++)
		{
			stNPCQuest_Remove *rem = &npc->Remove;

			if(rem->Item[i].Amount == 0)
				continue;

			INT32 amount = rem->Item[i].Amount;

			Log(clientId, LOG_INGAME, "Removendo item %d. Quantidade: %d", rem->Item[i].Item, amount);
			for(INT32 t = 0; t < 60; t++)
			{
				if(player->Inventory[t].Index == rem->Item[i].Item)
				{
					while(player->Inventory[t].Index == player->Inventory[t].Index)
					{
						AmountMinus(&player->Inventory[t]);

						amount--;
						if(amount <= 0)
							break;
					}

					SendItem(clientId, SlotType::Inv, t, &player->Inventory[t]);
				}

				if(amount <= 0)
					break;
			}
		}

		SendEtc(clientId);
		SendScore(clientId);
		return true;
	}
#pragma endregion
#pragma region NPC EVENTO
		if(pMob[npcId].Mobs.Player.Status.Level >= 500 && pMob[npcId].Mobs.Player.Status.Level <= (500 + MAX_NPCEVENTO))
		{
			NPCEvento(clientId, p->npcId);

			return true;
		}
#pragma endregion
#pragma region GOD GOVERNEMENT
	if(LOCAL_527 == 4 && face == 271)
	{
		INT32 need  = 100,
			  total = GetTotKill(clientId);

		if(total < need)
		{
			SendSay(npcId, g_pLanguageString[_NN_Need_XX_Fame], need);

			return true;
		}

		INT32 totaloop  = total / need,
		      guild     = pMob[clientId].Mobs.Player.GuildIndex,
			  totalFame = 0;

		for(INT32 i = 0; i < totaloop; i++)
		{
			if(guild != 0)
				totalFame += 5;

			pMob[clientId].Mobs.Fame += 10;
		}

		if(totalFame != 0)
			SetGuildFame(guild,  g_pGuild[guild].Fame + totalFame);

		SetTotKill(clientId, total - totaloop * need);
		SetPKPoint(clientId, GetPKPoint(clientId) + (10 * totaloop));

		p364 packet;
		GetCreateMob(clientId, (BYTE*)&packet);

		GridMulticast_2(pMob[clientId].Target.X, pMob[clientId].Target.Y, (BYTE*)&packet, 0);

		pMob[clientId].GetCurrentScore(clientId);
		SendScore(clientId);

		Log(clientId, LOG_INGAME, "Resetou pontos PK. Total: %d, loop: %d. Total guildfame %d. GuildID: %d",
			total, totaloop, totalFame, guild);

		if(totalFame != 0)
			Log(SERVER_SIDE, LOG_INGAME, "Guild %s [%d] ganhou %d de fame por resetar pk. Fame anterior: %d", g_pGuild[guild].Name.c_str(), guild, totalFame, g_pGuild[guild].Fame);
	}
#pragma endregion
#pragma region MOUNT MASTER
	else if(LOCAL_526 == 58)
	{ // 00428D91
		STRUCT_ITEM *LOCAL_531 = &pMob[clientId].Mobs.Player.Equip[14];

		if(LOCAL_531->Index < 2330 || LOCAL_531->Index >= 2390)
		{
			SendClientMessage(clientId, "Voca nao possui uma montaria");

			return true;
		}

		INT16 LOCAL_532 = *(WORD*)&LOCAL_531->Effect[0].Index;
		if(LOCAL_532 > 0)
		{
			SendClientMessage(clientId, "Sua montaria nao esta morta");

			return true;
		}

		INT32 LOCAL_533 = ItemList[LOCAL_531->Index].Price;
		if(LOCAL_525 == 0)
		{
			SendClientMessage(clientId, g_pLanguageString[_DS_S_cure_price_D], ItemList[LOCAL_531->Index].Name, LOCAL_533);

			return true;
		}

		if(pMob[clientId].Mobs.Player.Gold < LOCAL_533)
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_Havent_Money_So_Much]);

			return true;
		}

		if(LOCAL_533 < 0 || LOCAL_533 > 100000000)
			return true;

		pMob[clientId].Mobs.Player.Gold -= LOCAL_533;
		
		INT32 LOCAL_534 = GetItemAbility(LOCAL_531, EF_MOUNTLIFE);
		LOCAL_534 = (LOCAL_534 - (Rand() % 4));
		
		if(LOCAL_534 <= 0)
		{
			Log(clientId, LOG_INGAME, "Reviver montaria: morta. %s [%d] [%d %d %d %d %d %d]", ItemList[LOCAL_531->Index].Name, LOCAL_531->Index, LOCAL_531->EF1, LOCAL_531->EFV1, LOCAL_531->EF2, LOCAL_531->EFV2, LOCAL_531->EF3, LOCAL_531->EFV3);

			memset(LOCAL_531, 0, sizeof STRUCT_ITEM);
			SendClientMessage(clientId, g_pLanguageString[_NN_Cure_faild]);
		}
		else
		{
			int level = LOCAL_531->Effect[1].Index;
			if (level > 120)
			{
				int rand = Rand() % 100;
				int protector = GetFirstSlot(clientId, 3251);
				if (rand <= 25 && protector == -1)
				{
					LOCAL_531->Effect[1].Index--;
					Log(clientId, LOG_INGAME, "Perdeu um navel devido. Level atual: %d", level - 1);
				}

				if (protector != -1)
				{
					Log(clientId, LOG_INGAME, "Nao perdeu navel devido ao usso do Protetor Abenaoado");

					AmountMinus(&pMob[clientId].Mobs.Player.Inventory[protector]);
					SendItem(clientId, SlotType::Inv, protector, &pMob[clientId].Mobs.Player.Inventory[protector]);
				}
			}

			Log(clientId, LOG_INGAME, "Reviver concluado %s [%d] [%d %d %d %d %d %d]", ItemList[LOCAL_531->Index].Name, LOCAL_531->Index, LOCAL_531->EF1, LOCAL_531->EFV1, LOCAL_531->EF2, LOCAL_531->EFV2, LOCAL_531->EF3, LOCAL_531->EFV3);

			SendClientMessage(clientId, g_pLanguageString[_NN_Cured]);
			LOCAL_531->Effect[1].Value = LOCAL_534;
			
			*(WORD*)&LOCAL_531->Effect[0].Index = 20;
			LOCAL_531->Effect[2].Index = 5;
		}

		pMob[clientId].GetCurrentScore(clientId);
		
		SendItem(clientId, SlotType::Equip, 14, LOCAL_531);
		MountProcess(clientId, 0);
		SendEtc(clientId);
	}
#pragma endregion
#pragma region KIBITA
	else if(LOCAL_527 == 10 && face == 51)
	{ // Kibita
		time_t rawnow = time(NULL);
		struct tm now; localtime_s(&now, &rawnow);

		STRUCT_MOB *player = &pMob[clientId].Mobs.Player;

		if (now.tm_wday != 6 && now.tm_wday != 0 && now.tm_hour == 21 && pMob[clientId].Mobs.Player.Equip[0].EFV2 == MORTAL && pMob[clientId].Mobs.Player.Status.Level <= 299)
		{
			INT32 slotId = GetFirstSlot(clientId, 420);
			if (slotId != -1)
			{
				INT32 i = 0;
				for (; i < 32; i++)
				{
					if (pMob[clientId].Mobs.Affects[i].Index == 29)
						break;
				}

				if (i == 32)
				{
					for (i = 0; i < 32; i++)
						if (pMob[clientId].Mobs.Affects[i].Index == 0)
							break;
				}

				if (i != 32)
				{
					pMob[clientId].Mobs.Affects[i].Index = 29;
					pMob[clientId].Mobs.Affects[i].Value = 99;
					pMob[clientId].Mobs.Affects[i].Time = 450;

					pMob[clientId].GetCurrentScore(clientId);

					SendScore(clientId);
					SendAffect(clientId);

					AmountMinus(&player->Inventory[slotId]);
					SendItem(clientId, SlotType::Inv, slotId, &player->Inventory[slotId]);

					Teleportar(clientId, 2462, 1843);
					return true;
				}
			}
		}

		if(player->bStatus.Level >= 369 && pMob[clientId].Mobs.Player.Equip[0].EFV2 == MORTAL)
		{
			INT32 searchedId = 5334;
			if(player->ClassInfo == 1)
				searchedId = 5336;
			else if(player->ClassInfo == 2)
				searchedId = 5335;
			else if(player->ClassInfo == 3)
				searchedId = 5337;
		
			INT32 slotId = GetFirstSlot(clientId, searchedId),
				  cape   = player->Equip[15].Index;

			if(slotId != -1 && cape != 574 && cape != 1769 && cape != 1768)
			{
				memset(&player->Inventory[slotId], 0, sizeof STRUCT_ITEM);
				memset(&player->Equip[15], 0, sizeof STRUCT_ITEM);

				if(player->CapeInfo == CAPE_BLUE)
					player->Equip[15].Index = 1768;
				else if(player->CapeInfo == CAPE_RED)
					player->Equip[15].Index = 1769;
				else if(player->CapeInfo == CAPE_WHITE)
					player->Equip[15].Index = 574;

				SendItem(clientId, SlotType::Inv, slotId, &player->Inventory[slotId]);
				SendItem(clientId, SlotType::Equip, 15, &player->Equip[15]);

				if(!(player->Learn[0] & (1 << 30)))
					player->Learn[0] |= 1 << 30;

				CharLogOut(clientId);
				SendClientMessage(clientId, g_pLanguageString[_NN_God_Continue_Blessing]);

				SendSignalParm(clientId, clientId, 0x3B4, pUser[clientId].inGame.CharSlot);

				Log(clientId, LOG_INGAME, "Adquirido capa %d, adquirindo soul", player->Equip[15].Index);
				return true;
			}
		}

		SendClientMessage(clientId, g_pLanguageString[_NN_Sorry]);
	}
#pragma endregion
#pragma region ZAKUM GATE
	else if(LOCAL_526 == 14)
	{ // 0042961E - zakum  - 7D7558 o castelo zakum esta
		int slotId = GetFirstSlot(clientId, 751);
			
		if (slotId == -1)
		{
			SendClientMessage(clientId, "Traga-me a chave para ter acesso ao Castelo de Zakum");

			return true;
		}


		auto& zakum = sServer.Zakum;
		if (zakum.IsOperating && zakum.Users.size() != 0)
		{
			int attackerId = zakum.Users.back();

			SendClientMessage(clientId, g_pLanguageString[_SD_Zakum_Quest_by_S_N], pMob[attackerId].Mobs.Player.Name, zakum.Users.size());
			return true;
		}

		// limpa a lista de usuarios
		zakum.Users.clear();

		std::stringstream str;
		str << "[Grupo para a quest IMP Zakum]" << std::endl;

		int leader = pMob[clientId].Leader;
		if (leader == 0)
			leader = clientId;

		str << "Personagem " << pMob[leader].Mobs.Player.Name << "(" << pUser[leader].User.Username << ")" << std::endl;
		for (int i = 0; i < 12; ++i)
		{
			int memberId = pMob[leader].PartyList[i];
			if (memberId <= 0 || memberId >= MAX_PLAYER)
				continue;

			zakum.Users.push_back(memberId);

			str << "Personagem " << pMob[memberId].Mobs.Player.Name <<  "(" << pUser[memberId].User.Username << ")" << std::endl;
		}

		zakum.Users.push_back(leader);

		for (const auto& userId : zakum.Users)
		{
			Log(userId, LOG_INGAME, str.str().c_str());

			Teleportar(userId, 2241, 1261);
		}

		// Zakum gate
		zakum.StartTime = std::chrono::steady_clock::now();
		zakum.IsOperating = true;

		AmountMinus(&pMob[clientId].Mobs.Player.Inventory[slotId]);
		SendItem(clientId, SlotType::Inv, slotId, &pMob[clientId].Mobs.Player.Inventory[slotId]);
	}
#pragma endregion
#pragma region DRAGaO DE ARZAN
	else if(LOCAL_526 == 15) 
	{ // 004296AD - provavel griupan
		INT32 LOCAL_619[18] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
		INT32 LOCAL_637[18] = {4, 3, 2, 2, 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

		if(pMob[clientId].Mobs.Player.Gold < 2000000)
		{
			SendSay(npcId, g_pLanguageString[_NN_snowimp_need_2MGold]);

			return true;
		}

		INT32  LOCAL_655 = 0;
		for(; LOCAL_655 < 64; LOCAL_655++)
		{
			INT32 LOCAL_656 = pMob[clientId].Mobs.Player.Inventory[LOCAL_655].Index;
			if(LOCAL_656 < 1721 || LOCAL_656 > 1725)
				continue;

			INT32 LOCAL_657 = LOCAL_656 - 1721;
			for(INT32 LOCAL_658 = 0; LOCAL_658 < 18; LOCAL_658 ++)
			{
				if(LOCAL_619[LOCAL_658] == -1 && LOCAL_637[LOCAL_658] == LOCAL_657)
				{
					LOCAL_619[LOCAL_658] = LOCAL_655;

					break;
				}
			}
		}
		
		if(LOCAL_619[0] == -1 || LOCAL_619[1] == -1 || LOCAL_619[2] == -1 || LOCAL_619[3] == -1 || LOCAL_619[4] == -1 || 
			LOCAL_619[5] == -1 || LOCAL_619[6] == -1 || LOCAL_619[7] == -1 || LOCAL_619[8] == -1 || LOCAL_619[9] == -1 || 
			LOCAL_619[10] == -1 || LOCAL_619[11] == -1 || LOCAL_619[12] == -1 || LOCAL_619[13] == -1 || LOCAL_619[14] == -1 || 
			LOCAL_619[15] == -1 || LOCAL_619[16] == -1 || LOCAL_619[17] == -1)
		{
			SendSay(npcId, g_pLanguageString[_NN_Need_5_materials]);

			return true;
		}

		for(LOCAL_655 = 0; LOCAL_655 < 18; LOCAL_655 ++)
		{
			INT32 LOCAL_659 = LOCAL_619[LOCAL_655];
			if(LOCAL_659 < 0 || LOCAL_659 >= 64)
			{
				// TODO : Error
				return true;
			}

			memset(&pMob[clientId].Mobs.Player.Inventory[LOCAL_659], 0, sizeof STRUCT_ITEM);
			SendItem(clientId, SlotType::Inv, LOCAL_659, &pMob[clientId].Mobs.Player.Inventory[LOCAL_659]);
		}

		pMob[clientId].Mobs.Player.Gold -= 2000000;
		SendEtc(clientId);

		INT32 LOCAL_660 = Rand() & 0x80000003;

		STRUCT_ITEM LOCAL_662{};
		LOCAL_662.Index = 1726;
		LOCAL_662.Effect[0].Index = EF_SANC;
		
		SetItemSanc(&LOCAL_662, LOCAL_660, 0);

		for (INT32 LOCAL_780 = 1; LOCAL_780 <= 2; LOCAL_780++)
		{
			INT32 LOCAL_781 = Rand() & 0x80000007;
			if (LOCAL_781 == 0)
			{
				LOCAL_662.Effect[LOCAL_780].Index = EF_HP;
				LOCAL_662.Effect[LOCAL_780].Value = (Rand() % 41) + 20;
			}
			else if (LOCAL_781 == 1)
			{
				LOCAL_662.Effect[LOCAL_780].Index = EF_DAMAGE;
				LOCAL_662.Effect[LOCAL_780].Value = (Rand() % 21) + 5;
			}
			else if (LOCAL_781 == 2)
			{
				LOCAL_662.Effect[LOCAL_780].Index = EF_ATTSPEED;
				LOCAL_662.Effect[LOCAL_780].Value = (Rand() % 11) + 5;
			}
			else if (LOCAL_781 == 3)
			{
				LOCAL_662.Effect[LOCAL_780].Index = EF_MP;
				LOCAL_662.Effect[LOCAL_780].Value = (Rand() % 51) + 20;
			}
			else if (LOCAL_781 == 4)
			{
				LOCAL_662.Effect[LOCAL_780].Index = EF_MAGIC;
				LOCAL_662.Effect[LOCAL_780].Value = (Rand() % 7) + 2;
			}
			else if (LOCAL_781 == 5)
			{
				LOCAL_662.Effect[LOCAL_780].Index = EF_STR;
				LOCAL_662.Effect[LOCAL_780].Value = (Rand() & 0x8000000F) + 5;
			}
			else if (LOCAL_781 == 6)
			{
				LOCAL_662.Effect[LOCAL_780].Index = EF_INT;
				LOCAL_662.Effect[LOCAL_780].Value = (Rand() & 0x8000000F) + 5;
			}
			else if (LOCAL_781 == 7)
			{
				LOCAL_662.Effect[LOCAL_780].Index = EF_DEX;
				LOCAL_662.Effect[LOCAL_780].Value = (Rand() & 0x8000000F) + 5;
			}
		}

		INT32 LOCAL_663 = 0;
		for(; LOCAL_663 < 64; LOCAL_663 ++)
		{
			if(pMob[clientId].Mobs.Player.Inventory[LOCAL_663].Index == 0)
				break;
		}

		if(LOCAL_663 < 0 || LOCAL_663 >= 64)
		{
			INT32 LOCAL_668 = pMob[clientId].Target.X;
			INT32 LOCAL_669 = pMob[clientId].Target.Y;

			CreateItem(LOCAL_668, LOCAL_669, &LOCAL_662, Rand() % 0x80000003, 1);
			return true;
		}

		memcpy(&pMob[clientId].Mobs.Player.Inventory[LOCAL_663], &LOCAL_662, sizeof STRUCT_ITEM);
		SendItem(clientId, SlotType::Inv, LOCAL_663, &pMob[clientId].Mobs.Player.Inventory[LOCAL_663]);

		SendSay(npcId, g_pLanguageString[_NN_snowimp_create_success]);

		Log(clientId, LOG_INGAME, "Gerado Griupan com sucesso");
	} 
#pragma endregion
#pragma region DRAGaO DE ARMIA (nao concluado)
	else if(LOCAL_526 == 1)
	{ // 00429CBB - Provavel dg armia
		INT32 LOCAL_671 = 0;
		for(; LOCAL_671 < 60; LOCAL_671 ++)
		{
			INT32 LOCAL_672 = pMob[clientId].Mobs.Player.Inventory[LOCAL_671].Index;
			if(LOCAL_672 <= 0)
				continue;

			INT32 LOCAL_673 = 0;
			for(; LOCAL_673 < 8; LOCAL_673 ++)
			{
				INT32 LOCAL_674 = sServer.Treasure[LOCAL_673].Source;
				if(LOCAL_674 <= 0)
					continue;

				if(LOCAL_672 == LOCAL_674)
					break;
			}

			if(LOCAL_673 == 8)
				continue;

			memset(&pMob[clientId].Mobs.Player.Inventory[LOCAL_671], 0, sizeof STRUCT_ITEM);
			SendItem(clientId, SlotType::Inv, LOCAL_671, &pMob[clientId].Mobs.Player.Inventory[LOCAL_671]);

			INT32 LOCAL_739 = Rand() % 1000;

			STRUCT_ITEM LOCAL_741;
			memset(&LOCAL_741, 0, sizeof STRUCT_ITEM);
			
			if(LOCAL_739 < sServer.Treasure[LOCAL_673].Rate[0])
				LOCAL_741 = sServer.Treasure[LOCAL_673].Target[0];
			else if(LOCAL_739 < sServer.Treasure[LOCAL_673].Rate[1])
				LOCAL_741 = sServer.Treasure[LOCAL_673].Target[1];
			else if(LOCAL_739 < sServer.Treasure[LOCAL_673].Rate[2])
				LOCAL_741 = sServer.Treasure[LOCAL_673].Target[2];
			else if(LOCAL_739 < sServer.Treasure[LOCAL_673].Rate[3])
				LOCAL_741 = sServer.Treasure[LOCAL_673].Target[3];
			else if(LOCAL_739 < sServer.Treasure[LOCAL_673].Rate[4])
				LOCAL_741 = sServer.Treasure[LOCAL_673].Target[4];

			if(LOCAL_741.Index == 0)
			{
				SendSay(npcId, g_pLanguageString[_NN_Next_Chance]);

				return true;
			}

			INT32 LOCAL_742 = GetFirstSlot(clientId, 0);
			if(LOCAL_742 == -1)
			{
				CreateItem(pMob[clientId].Target.X, pMob[clientId].Target.Y, &LOCAL_741, Rand() % 3, 1);

				return true;
			}

			memcpy(&pMob[clientId].Mobs.Player.Inventory[LOCAL_742], &LOCAL_741, sizeof STRUCT_ITEM);
			SendItem(clientId, SlotType::Inv, LOCAL_742, &LOCAL_741);

			SendSay(npcId, g_pLanguageString[_NN_Congratulations]);
			return true;
		}

		INT32 LOCAL_755[7];
		memset(LOCAL_755, 0, sizeof LOCAL_755);

		INT32 LOCAL_756 = 0;
		
		for(LOCAL_671 = 0; LOCAL_671 < 60; LOCAL_671 ++)
		{
			INT32 LOCAL_757 = pMob[clientId].Mobs.Player.Inventory[LOCAL_671].Index;

			if(LOCAL_757 >= 421 && LOCAL_757 <= 427)
			{
				INT32 LOCAL_758 = LOCAL_757 - 421;
				LOCAL_755[LOCAL_758] = 1;
				LOCAL_756++;
			}
		}

		if(LOCAL_755[0] == 0 || LOCAL_755[1] == 0 || LOCAL_755[2] == 0 || LOCAL_755[3] == 0 || LOCAL_755[4] == 0 || 
			LOCAL_755[5] == 0 || LOCAL_755[6] == 0)
		{
			SendSay(npcId, g_pLanguageString[_NN_Gather_7_Clistals]);

			return true;
		}

		if(!pMob[clientId].Mobs.Player.Equip[6].Index)
		{
			SendSay(npcId, g_pLanguageString[_NN_Equip_Weapon_To_Enchant]);

			return true;
		}

		INT32 LOCAL_759 = GetItemSanc(&pMob[clientId].Mobs.Player.Equip[6]);
		if(LOCAL_759 > 6)
		{
			SendSay(npcId, "Permitido somente para armas ata +6");

			return true;
		}

		STRUCT_ITEM* LOCAL_761 = &pMob[clientId].Mobs.Player.Equip[6];

		INT32 LOCAL_764 = LOCAL_756 / 10 * 25;
		INT32 LOCAL_765 = ItemList[LOCAL_761->Index].Level;
		
		// nao necessariamente nesta ordem, mas a isso
		LOCAL_761->Effect[0].Index = 0;
		LOCAL_761->Effect[1].Index = 0;
		LOCAL_761->Effect[2].Index = 0;
		LOCAL_761->Effect[0].Value = 0;
		LOCAL_761->Effect[1].Value = 0;
		LOCAL_761->Effect[2].Value = 0;

		SetItemBonus(LOCAL_761, LOCAL_765 + LOCAL_764, 1, pMob[clientId].DropBonus);

		for(LOCAL_671 = 0; LOCAL_671 < 60; LOCAL_671 ++)
		{
			INT32 LOCAL_766 = pMob[clientId].Mobs.Player.Inventory[LOCAL_671].Index;
			if(LOCAL_766 >= 421 && LOCAL_766 <= 427)
				memset(&pMob[clientId].Mobs.Player.Inventory[LOCAL_671], 0, sizeof STRUCT_ITEM);
		}

		SendCarry(clientId);

		SendItem(clientId, SlotType::Equip, 6, &pMob[clientId].Mobs.Player.Equip[6]);

		SendSay(npcId, g_pLanguageString[_SN_Now_I_Will_Enchant_Your], pMob[clientId].Mobs.Player.Name);
		SetAffect(clientId, 0x2C, 200, 200);

		SendAffect(clientId);

		p364 create;
		GetCreateMob(clientId, (BYTE*)&create);

		GridMulticast_2(pMob[clientId].Target.X, pMob[clientId].Target.Y, (BYTE*)&create, 0);

		INT32 LOCAL_760 = pMob[clientId].Mobs.Player.Equip[0].Index / 10;
		if(LOCAL_760 == 0)
			SendEmotion(clientId, 0x17, 0);
		else if(LOCAL_760 == 1)
			SendEmotion(clientId, 0x15, 0);
		else if(LOCAL_760 == 2)
			SendEmotion(clientId, 0x15, 0);
		else if(LOCAL_760 == 3)
			SendEmotion(clientId, 0x15, 0);
		
	}
#pragma endregion
#pragma region PEGAR QUEST DO AMULETO MaSTICO (NPC DE ARZAN)
	else if(LOCAL_526 == 2)
	{ // 0042A67D - NPC do Amuleto Mastico
		if((pMob[clientId].Mobs.Player.QuestInfo.Mystical_GetQuest) == 0 && pMob[clientId].Mobs.Player.bStatus.Level >= 59)
		{
			if(LOCAL_525 == 0)
			{
				SendSay(npcId, g_pLanguageString[_NN_Monster_Attaking_Us_Help]);

				return true;
			}

			pMob[clientId].Mobs.Player.QuestInfo.Mystical_GetQuest = 1;

			SendSay(npcId, g_pLanguageString[_NN_Get_Watching_Town_Mission]);
			return true;

		}

		SendSay(npcId, g_pLanguageString[_NN_Hurry_Helping_them]);
		return true;
	}
#pragma endregion
#pragma region ENTREGA DO AMULETO MaSTICO (Exploit Leader, algo assim)
	else if(LOCAL_526 == 3)
	{// 0042A7F6
		if((pMob[clientId].Mobs.Player.QuestInfo.Mystical_GetQuest) && !(pMob[clientId].Mobs.Player.QuestInfo.Mystical_CanGetAmuleto))
		{
			SendSay(npcId, g_pLanguageString[_SN_All_Villagers_Thanks_Your], pMob[clientId].Mobs.Player.Name);

			return true;
		}

		if((pMob[clientId].Mobs.Player.QuestInfo.Mystical_GetQuest) && (pMob[clientId].Mobs.Player.QuestInfo.Mystical_GetAmuleto) == 0 && pMob[clientId].Mobs.Player.bStatus.Level >= 59)
		{
			INT32 LOCAL_769 = pMob[clientId].Mobs.Player.bStatus.Level;
			INT32 LOCAL_770 = 551;
			INT32 LOCAL_771 = 1;

			if(LOCAL_769 < 50)
			{
				LOCAL_770 = (Rand() & 0x80000003) + 551;
				LOCAL_771 = 1;
			}
			else if(LOCAL_769 < 80)
			{
				LOCAL_770 = (Rand() & 0x80000003) + 555;
				LOCAL_771 = 2;
			}
			else
			{
				LOCAL_770 = (Rand() & 0x80000003) + 559;
				LOCAL_771 = 3;
			}

			STRUCT_ITEM LOCAL_772;
			LOCAL_772.Index = LOCAL_770;

			LOCAL_772.Effect[0].Index = EF_SANC;
			LOCAL_772.Effect[0].Value = 0;

			for(INT32 LOCAL_780 = 1; LOCAL_780 <= 2; LOCAL_780++)
			{
				INT32 LOCAL_781 = Rand() & 0x80000007;
				if(LOCAL_781 == 0)
				{
					LOCAL_772.Effect[LOCAL_780].Index = EF_HP;
					LOCAL_772.Effect[LOCAL_780].Value = (Rand() % 41) + 20;
				}
				else if(LOCAL_781 == 1)
				{
					LOCAL_772.Effect[LOCAL_780].Index = EF_DAMAGE;
					LOCAL_772.Effect[LOCAL_780].Value = (Rand() % 21) + 5;
				}
				else if(LOCAL_781 == 2)
				{
					LOCAL_772.Effect[LOCAL_780].Index = EF_ATTSPEED;
					LOCAL_772.Effect[LOCAL_780].Value = (Rand() % 11) + 5;
				}
				else if(LOCAL_781 == 3)
				{
					LOCAL_772.Effect[LOCAL_780].Index = EF_MP;
					LOCAL_772.Effect[LOCAL_780].Value = (Rand() % 51) + 20;
				}
				else if(LOCAL_781 == 4)
				{
					LOCAL_772.Effect[LOCAL_780].Index = EF_MAGIC;
					LOCAL_772.Effect[LOCAL_780].Value = (Rand() % 7) + 2;
				}
				else if(LOCAL_781 == 5)
				{
					LOCAL_772.Effect[LOCAL_780].Index = EF_STR;
					LOCAL_772.Effect[LOCAL_780].Value = (Rand() & 0x8000000F) + 5;
				}
				else if(LOCAL_781 == 6)
				{
					LOCAL_772.Effect[LOCAL_780].Index = EF_INT;
					LOCAL_772.Effect[LOCAL_780].Value = (Rand() & 0x8000000F) + 5;
				}
				else if(LOCAL_781 == 7)
				{
					LOCAL_772.Effect[LOCAL_780].Index = EF_DEX;
					LOCAL_772.Effect[LOCAL_780].Value = (Rand() & 0x8000000F) + 5;
				}
			}

			INT32 LOCAL_782 = GetFirstSlot(clientId, 0);
			if(LOCAL_782 == -1)
			{
				SendSay(npcId, g_pLanguageString[_NN_CarryFull]);

				return true;
			}

			Log(clientId, LOG_INGAME, "Adquirido %s [%d] [%d %d %d %d %d %d] quest Amuleto Mastico", ItemList[LOCAL_772.Index].Name, LOCAL_772.Index, LOCAL_772.EF1, LOCAL_772.EFV1, LOCAL_772.EF2, LOCAL_772.EFV2, LOCAL_772.EF3, LOCAL_772.EFV3);

			memcpy(&pMob[clientId].Mobs.Player.Inventory[LOCAL_782], &LOCAL_772, sizeof STRUCT_ITEM);
			SendItem(clientId, SlotType::Inv, LOCAL_782, &pMob[clientId].Mobs.Player.Inventory[LOCAL_782]);

			SendSay(npcId, g_pLanguageString[_NN_Give_You_Some_Reward]);
			
			pMob[clientId].Mobs.Player.QuestInfo.Mystical_GetAmuleto = 1;

			SendClientMessage(clientId, g_pLanguageString[_NN_Watching_Town_Awarded]);
		}

		if((pMob[clientId].Mobs.Player.QuestInfo.Mystical_GetQuest) == 0)
		{
			SendSay(npcId, g_pLanguageString[_NN_Guard_This_Village]);

			return true;
		}

		SendSay(npcId, g_pLanguageString[_NN_Thanks_for_Helping_us]);
	}
#pragma endregion
#pragma region JEFFI
	else if(LOCAL_526 == 4)
	{// 0042AE24
		if(pMob[clientId].Mobs.Player.Equip[13].Index != 447 && pMob[clientId].Mobs.Player.Equip[13].Index != 692)
		{
			INT32 LOCAL_787 = GetInventoryAmount(clientId, 419),
				  LOCAL_788 = GetInventoryAmount(clientId, 420);

			if(LOCAL_787 < 10 && LOCAL_788 < 10)
			{
				SendSay(npcId, g_pLanguageString[_NN_Need_10_Particle]);

				return true;
			}

			if(pMob[clientId].Mobs.Player.Gold < 1000000)
			{
				SendSay(npcId, g_pLanguageString[_NN_Need_1000000_Gold]);

				return true;
			}

			INT32 totalPL = 0,
				  totalPO = 0,
				  totalRO = LOCAL_787,
				  totalRL = LOCAL_788;

			while(true)
			{
				if(LOCAL_787 >= 10)
				{
					Combine(clientId, 419, 412);
					LOCAL_787 -= 10;

					totalPO++;
				}

				if(LOCAL_788 >= 10)
				{
					Combine(clientId, 420, 413);
					LOCAL_788 -= 10;

					totalPL++;
				}

				if(LOCAL_787 < 10 && LOCAL_788 < 10)
					break;
			}

			// SUPER IMPROVAVEL DISSO ACONTECER MAS BELEZA PODE ACONTECER!!!
			if (LOCAL_787 != -1 || LOCAL_788 != -1)	
			{
				pMob[clientId].Mobs.Player.Gold -= 1000000;

				SetAffect(clientId, 44, 20, 20);

				SendScore(clientId);
				SendCarry(clientId);
				SendEtc(clientId);
				SendAffect(clientId);
				Log(clientId, LOG_INGAME, "%s usou o npc Jeffi e compos PO/PL. Resto de ori: %d Resto de lac: %d. Poeira de Ori: %d. Poeira de Lac: %d", pMob[clientId].Mobs.Player.Name,
					totalRO, totalRL, totalPO, totalPL);
			}
			return true;
		}

		INT32 LOCAL_790 = 0;
		if(pMob[clientId].Mobs.Player.Equip[13].Index == 447)
			LOCAL_790 = 1000000;
		else if(pMob[clientId].Mobs.Player.Equip[13].Index == 692)
			LOCAL_790 = 5000000;
		else
			return true;

		if(pMob[clientId].Mobs.Player.Gold < LOCAL_790)
		{
			if(LOCAL_790 == 1000000)
				SendSay(npcId, g_pLanguageString[_NN_Need_1000000_Gold]);
			else
				SendSay(npcId, g_pLanguageString[_NN_Need_5000000_Gold]);

			return true;
		}

		if(LOCAL_790 == 1000000)
		{
			pMob[clientId].Mobs.Player.Gold -= 1000000;

			pMob[clientId].Mobs.Player.Equip[13].Index = 448 + (Rand () % 3);
		}
		else
		{
			pMob[clientId].Mobs.Player.Gold -= 5000000;

			pMob[clientId].Mobs.Player.Equip[13].Index = 693 + (Rand () % 3);
		}

		SendItem(clientId, SlotType::Equip, 13, &pMob[clientId].Mobs.Player.Equip[13]);
		SendEtc(clientId);

		SendSay(npcId, g_pLanguageString[_NN_Processing_Complete]);
		SetAffect(clientId, 44, 20, 20);

		SendScore(clientId);
		SendAffect(clientId);

		Log(clientId, LOG_INGAME, "Usou o npc Jeffi e compas o item: %s", ItemList[pMob[clientId].Mobs.Player.Equip[13].Index].Name);
	}
#pragma endregion
#pragma region SHAMa
	else if(LOCAL_526 == 5)
	{// 0042B1D9
		INT32 LOCAL_791 = pMob[clientId].Mobs.Player.Equip[13].Index, 
			  LOCAL_792 = LOCAL_791,
			  LOCAL_793;

		if(LOCAL_791 == 448 || LOCAL_791 == 449 || LOCAL_791 == 450)
		{
			if((pMob[clientId].Mobs.Player.QuestInfo.Reset50))
			{
				SendSay(npcId, g_pLanguageString[_NN_Youve_Done_It_Already]);

				return true;
			}

			LOCAL_792 = LOCAL_792 - 448;
			LOCAL_793 = 1;
		}
		else if(LOCAL_791 == 693 || LOCAL_791 == 694 || LOCAL_791 == 695)
		{
			LOCAL_792 = LOCAL_792 - 693;
			LOCAL_793 = 2;
		}
		else
		{
			SendSay(npcId, g_pLanguageString[_NN_Need_Pure_Divine]);

			return true;
		}

		INT32 LOCAL_794 = 50;
		if(LOCAL_793 == 2)
			LOCAL_794 = 100;

		INT32 LOCAL_795 = pMob[clientId].Mobs.Player.MasterPoint;
		for(INT32 LOCAL_796 = 0; LOCAL_796 < 4; LOCAL_796 ++)
		{
			if(pMob[clientId].Mobs.Player.bStatus.Mastery[LOCAL_796] > LOCAL_794)
			{
				LOCAL_795 += LOCAL_794;

				pMob[clientId].Mobs.Player.bStatus.Mastery[LOCAL_796] -= LOCAL_794;
			}
			else
			{
				LOCAL_795 += pMob[clientId].Mobs.Player.bStatus.Mastery[LOCAL_796];

				pMob[clientId].Mobs.Player.bStatus.Mastery[LOCAL_796] = 0;
			}
		}

		pMob[clientId].Mobs.Player.MasterPoint = LOCAL_795;
		
		int initial = (LOCAL_792 * 8); 
		for(int i = initial; i < initial + 8;i++)
		{
			int has = (pMob[clientId].Mobs.Player.Learn[0] & (1 << i));
			if(has != 0)
				pMob[clientId].Mobs.Player.Learn[0] -= (1 << i);
		}

		pMob[clientId].GetCurrentScore(clientId);

		memset(&pMob[clientId].Mobs.Player.Equip[13], 0, sizeof STRUCT_ITEM);

		SendItem(clientId, SlotType::Equip, 13, &pMob[clientId].Mobs.Player.Equip[13]);

		SendEtc(clientId);
		SendSay(npcId, g_pLanguageString[_NN_Initialize_Skill]);

		SetAffect(clientId, 44, 20, 20);

		SendScore(clientId);
		SendAffect(clientId);
		if (LOCAL_793 == 1)
			pMob[clientId].Mobs.Player.QuestInfo.Reset50 = 1;
		if (LOCAL_793 == 2)
			pMob[clientId].Mobs.Player.QuestInfo.Reset100 = 1;

		for (int i = 0; i < 16; i++)
		{
			if (i < 4)
				pMob[clientId].Mobs.Player.SkillBar1[i] = -1;
			
			pMob[clientId].Mobs.SkillBar[i] = -1;
		}
		
		p378 m_refreshSkillBar{};
		m_refreshSkillBar.Header.PacketId = 0x378;
		m_refreshSkillBar.Header.ClientId = clientId;
		m_refreshSkillBar.Header.Size = sizeof p378;

		memcpy(m_refreshSkillBar.SkillBar1, pMob[clientId].Mobs.Player.SkillBar1, 4);
		memcpy(m_refreshSkillBar.SkillBar2, pMob[clientId].Mobs.SkillBar, 16);

		pUser[clientId].AddMessage((BYTE*)&m_refreshSkillBar, sizeof m_refreshSkillBar);

		SendClientMessage(clientId, g_pLanguageString[_NN_Qest06Complete]);
	}
#pragma endregion
#pragma region REI DOS REINOS
	else if(LOCAL_526 == 7)
	{ // 0042B5EE
		INT32 LOCAL_797 = pMob[npcId].Mobs.Player.CapeInfo;
		INT32 LOCAL_798 = pMob[clientId].Mobs.Player.CapeInfo;
		INT32 LOCAL_799 = pMob[clientId].Mobs.Player.bStatus.Level;
		INT32 LOCAL_800 = 0;
		INT32 LOCAL_801 = pMob[clientId].Mobs.Player.Equip[15].Index;
		INT32 LOCAL_802 = 0;

		if(LOCAL_801 == 543 || LOCAL_801 == 545)
			LOCAL_798 = 7;

		if(LOCAL_801 == 544 || LOCAL_801 == 546)
			LOCAL_798 = 8;

		if(LOCAL_801 == 543 || LOCAL_801 == 544 || LOCAL_801 == 1768 || LOCAL_801 == 1769 || LOCAL_801 == 574 || LOCAL_801 == 3191 || LOCAL_801 == 3192 || LOCAL_801 == 3193 || LOCAL_801 == 3197 || LOCAL_801 == 3198 || LOCAL_801 == 3199)
			LOCAL_800 = 2;

		if(LOCAL_801 == 545 || LOCAL_801 == 546 || LOCAL_801 == 549)
			LOCAL_800 = 1;

		if (LOCAL_798 == CAPE_WHITE && LOCAL_801 != 0 && LOCAL_801 != 4081 && LOCAL_801 != 4006)
			LOCAL_800 = 3;

		if(LOCAL_798 != 0 && LOCAL_798 != LOCAL_797)
			return true;

		INT32 LOCAL_803 = sServer.Sapphire;
		if(LOCAL_803 == 0)
		{
			LOCAL_803 = 4;
			sServer.Sapphire = 4;
		}

		if(LOCAL_797 == 8)
		{
			if(sServer.Sapphire == 1)
				LOCAL_803 = 35;

			if(sServer.Sapphire == 2)
				LOCAL_803 = 32;

			if(sServer.Sapphire == 4)
				LOCAL_803 = 16;

			if(sServer.Sapphire == 16)
				LOCAL_803 = 4;

			if(sServer.Sapphire == 32)
				LOCAL_803 = 2;

			if(sServer.Sapphire == 35)
				LOCAL_803 = 1;
		}

		if(pMob[clientId].Mobs.Player.Equip[13].Index == 4081 && pMob[clientId].Mobs.Player.Status.Level >= 219 && pMob[clientId].Mobs.Player.Status.Level < 250 && pMob[clientId].Mobs.Player.CapeInfo == 0)
		{
			memset(&pMob[clientId].Mobs.Player.Equip[13], 0, sizeof STRUCT_ITEM);

			INT32 capeId = 0;
			switch(pMob[npcId].Mobs.Player.Equip[0].Index)
			{
				case 303:
					capeId = 545; // blue
					break;
				case 304:
					capeId = 546; // red
					break;
			}
			
			if(capeId != 0)
			{
				memset(&pMob[clientId].Mobs.Player.Equip[15], 0, sizeof STRUCT_ITEM);
				pMob[clientId].Mobs.Player.Equip[15].Index = capeId;

				SendItem(clientId, SlotType::Equip, 15, &pMob[clientId].Mobs.Player.Equip[15]);

				SendClientMessage(clientId, "Bem vindo, novo aventureiro");
			}
				
			SendItem(clientId, SlotType::Equip, 13, &pMob[clientId].Mobs.Player.Equip[13]);
			Log(clientId, LOG_INGAME, "%s pegou a capa com o emblema do reino. Capa: %d", pMob[clientId].Mobs.Player.Name, capeId);
			return true;
		}

		if(LOCAL_800 == 2 && pMob[clientId].Mobs.Player.Equip[0].EFV2 == MORTAL && pMob[clientId].Mobs.Player.Status.Level >= 299)
		{ // Fazer arch
			if(pMob[clientId].Mobs.Player.Equip[10].Index != 1742)
				return true;

			if(pMob[clientId].Mobs.Player.Equip[11].Index < 1760 || pMob[clientId].Mobs.Player.Equip[11].Index > 1763)
				return true;

			INT32 _face = pMob[clientId].Mobs.Player.Equip[0].Index;
			if((_face >= 22 && _face <= 25) || _face == 32)
				_face = 21;

			INT32 sephirot = pMob[clientId].Mobs.Player.Equip[11].Index;
			if(_face == 1)
				_face = 6 + (sephirot - 1760);
			else if(_face == 11)
				_face = 16 + (sephirot - 1760);
			else if(_face == 21)
				_face = 26 + (sephirot - 1760);
			else if(_face == 31)
				_face = 36 + (sephirot - 1760);
			else
			{
				SendClientMessage(clientId, "Contate a administraaao!");

				return true;
			}

			if(_face == pMob[clientId].Mobs.Player.Equip[0].Index)
			{
				SendClientMessage(clientId, "Contate a administraaao!");

				return true;
			}

			INT32 slot = -1;
			for(INT32 i = 0; i < 4; i++)
			{
				if(!pUser[clientId].CharList.Name[i][0])
				{
					slot = i;
					break;
				}
			}

			if(slot == -1)
			{
				SendClientMessage(clientId, "Voca nao possui espaao para criaaao do personagem arch");

				return true;
			}

			Log(clientId, LOG_INGAME, "Arch criado. Sephirot: %d. Face: %d. Level: %d. SlotId: %d", sephirot, _face, pMob[clientId].Mobs.Player.Status.Level, pUser[clientId].inGame.CharSlot);
			Log(SERVER_SIDE, LOG_INGAME, "Criado o arch do personagem %s. Sephirot: %d. Face: %d. Level: %d. SlotId: %d", pMob[clientId].Mobs.Player.Name, 
				sephirot, _face, pMob[clientId].Mobs.Player.Status.Level, pUser[clientId].inGame.CharSlot);

			SendNotice("Parabans %s pela criaaao do personagem Arch", pMob[clientId].Mobs.Player.Name);

			MSG_DBNewArch packet;
			memset(&packet, 0, sizeof packet);

			packet.Header.PacketId = 0x80B;
			packet.Header.Size = sizeof packet;
			packet.Header.ClientId = clientId;

			packet.ClassID = _face;
			packet.ClassInfo = (sephirot - 1760);
			packet.MortalSlot = pUser[clientId].inGame.CharSlot;
		
			strncpy_s(packet.Name, pMob[clientId].Mobs.Player.Name, 12);

			packet.PosID = slot;

			AddMessageDB((BYTE*)&packet, sizeof packet);
			
			memset(&pMob[clientId].Mobs.Player.Equip[10], 0, sizeof STRUCT_ITEM);
			memset(&pMob[clientId].Mobs.Player.Equip[11], 0, sizeof STRUCT_ITEM);

			CharLogOut(clientId);
			SendSignalParm(clientId, clientId, 0x3B4, slot);

			return true;
		}

		if (LOCAL_800 == 2 && pMob[clientId].Mobs.Player.Equip[0].EFV2 >= ARCH && pMob[clientId].Mobs.Player.Equip[10].Index == 1742 && pMob[clientId].Mobs.Player.Equip[11].Index >= 1760 && pMob[clientId].Mobs.Player.Equip[11].Index <= 1763)
		{
			if (pMob[clientId].Mobs.Player.Equip[10].Index != 1742 || GetItemAbility(&pMob[clientId].Mobs.Player.Equip[10], EF_NOTRADE) != 0)
			{
				SendClientMessage(clientId, g_pLanguageString[_NN_My_King_Bless1]);

				return true;
			}

			if (pMob[clientId].Mobs.Player.Equip[11].Index < 1760 || pMob[clientId].Mobs.Player.Equip[11].Index > 1763 || GetItemAbility(&pMob[clientId].Mobs.Player.Equip[11], EF_NOTRADE) != 0)
			{
				SendClientMessage(clientId, g_pLanguageString[_NN_My_King_Bless1]);

				return true;
			}

			std::array<int, 4> secretSlots;
			for (int i = 0; i < 4; i++)
				secretSlots[i] = GetFirstSlot(clientId, 5334 + i);

			if (std::find(std::begin(secretSlots), std::end(secretSlots), -1) != std::end(secretSlots))
			{
				SendClientMessage(clientId, "Necessario as 4 Pedras Secretas");

				return true;
			}

			for (auto slot : secretSlots)
			{
				pMob[clientId].Mobs.Player.Inventory[slot] = STRUCT_ITEM{};

				SendItem(clientId, SlotType::Inv, slot, &pMob[clientId].Mobs.Player.Inventory[slot]);
			}

			pMob[clientId].Mobs.Player.Equip[10] = STRUCT_ITEM{};
			pMob[clientId].Mobs.Player.Equip[11] = STRUCT_ITEM{};
			SendItem(clientId, SlotType::Equip, 10, &pMob[clientId].Mobs.Player.Equip[10]);
			SendItem(clientId, SlotType::Equip, 11, &pMob[clientId].Mobs.Player.Equip[11]);

			pMob[clientId].Mobs.Player.Inventory[secretSlots[0]].Index = 5338;
			SendItem(clientId, SlotType::Inv, secretSlots[0], &pMob[clientId].Mobs.Player.Inventory[secretSlots[0]]);

			Log(clientId, LOG_INGAME, "Composiaao da Pedra Ideal realizada com sucesso");
			SendNotice("%s compas com sucesso a Pedra Ideal", pMob[clientId].Mobs.Player.Name);

			SendClientMessage(clientId, g_pLanguageString[_NN_My_King_Bless1]);
			return true;
		}

		INT32 LOCAL_804 = LOCAL_803;
		if(LOCAL_525 != 0)
		{
			if(LOCAL_800 == 2)
			{
				if (LOCAL_797 == 7)
					SendClientMessage(clientId, g_pLanguageString[_NN_My_King_Bless1]);
				else
					SendClientMessage(clientId, g_pLanguageString[_NN_My_King_Bless2]);

				return true;
			}

			if(LOCAL_799 < 219 && LOCAL_800 == 0)
			{
				SendClientMessage(clientId, g_pLanguageString[_NN_Need_Level]);

				return true;
			}

			if(pMob[clientId].Mobs.Player.GuildIndex != 0 && pMob[clientId].Mobs.Player.CapeInfo == 0) // membro de guild com capa verde
			{
				if(LOCAL_797 != g_pGuild[pMob[clientId].Mobs.Player.GuildIndex].Kingdom)
				{
					SendSay(npcId, "Voca nao pode ser recrutado aqui porque sua guild a de outro reino");

					return true;
				}
			}

			// 0042B80A
			if(LOCAL_800 == 1 && LOCAL_799 < 255)
			{
				SendClientMessage(clientId, g_pLanguageString[_NN_Need_Level]);

				return true;
			}

			INT32 LOCAL_805 = GetInventoryAmount(clientId, 697),
				  LOCAL_806 = 0;
			
			LOCAL_805 += (GetInventoryAmount (clientId, 4131) * 10);
			if(LOCAL_805 < LOCAL_803)
			{
				SendClientMessage(clientId, g_pLanguageString[_DN_Need_D_Sapphire], LOCAL_803);

				return true;
			}

			// Atualiza a quantidade de safiras entre os canais e a dbsrv
			//0042B8E2
			pMsgSignal LOCAL_810;
			LOCAL_810.Header.PacketId = 0x80E;
			LOCAL_810.Header.Size = sizeof pMsgSignal;
			LOCAL_810.Header.ClientId = 0;

			if(LOCAL_797 == 7)
				LOCAL_810.Value = 1;
			else
				LOCAL_810.Value = 0;

			AddMessageDB((BYTE*)&LOCAL_810, sizeof pMsgSignal);

			int sapphire = LOCAL_803;
			for(LOCAL_806 = 0; LOCAL_806 < 60 ; LOCAL_806++)
			{
				if(pMob[clientId].Mobs.Player.Inventory[LOCAL_806].Index == 697)
				{
					while(pMob[clientId].Mobs.Player.Inventory[LOCAL_806].Index == 697)
					{
						AmountMinus(&pMob[clientId].Mobs.Player.Inventory[LOCAL_806]);

						LOCAL_803 --;
						if(LOCAL_803 <= 0)
							break;
					}

					SendItem(clientId, SlotType::Inv, LOCAL_806, &pMob[clientId].Mobs.Player.Inventory[LOCAL_806]);
				}
				
				if(pMob[clientId].Mobs.Player.Inventory[LOCAL_806].Index == 4131)
				{
					AmountMinus(&pMob[clientId].Mobs.Player.Inventory[LOCAL_806]);
					SendItem(clientId, SlotType::Inv, LOCAL_806, &pMob[clientId].Mobs.Player.Inventory[LOCAL_806]);

					LOCAL_803 -= 10;
					if(LOCAL_803 <= 0)
						break;
				}

				if(LOCAL_803 <= 0)
					break;
			}

			Log(clientId, LOG_INGAME, "Consumido %d safiras para pegar capa", sapphire);
			if(LOCAL_800 == 1)
			{
				if(LOCAL_797 == 7)
					pMob[clientId].Mobs.Player.Equip[15].Index = 543;
				else
					pMob[clientId].Mobs.Player.Equip[15].Index = 544;
			}
			else if(LOCAL_800 == 3)
			{
				int capeId = pMob[clientId].Mobs.Player.Equip[15].Index;
				auto newCapeId = std::find(g_pCapesID[2].begin(), g_pCapesID[2].end(), capeId);

				if (newCapeId == g_pCapesID[2].end())
				{
					Log(clientId, LOG_INGAME, "Um erro grave aconteceu. Capa %d WHITE nao encontrada", capeId);

					SendClientMessage(clientId, "Contate a administraaao");
					return true;
				}

				int capeIndex = std::distance(g_pCapesID[2].begin(), newCapeId);
				if (LOCAL_797 == CAPE_BLUE)
					pMob[clientId].Mobs.Player.Equip[15].Index = g_pCapesID[0][capeIndex];
				else
					pMob[clientId].Mobs.Player.Equip[15].Index = g_pCapesID[1][capeIndex];
			}
			else 
			{
				if (LOCAL_797 == 7)
					pMob[clientId].Mobs.Player.Equip[15].Index = 545;
				else
					pMob[clientId].Mobs.Player.Equip[15].Index = 546;
			}

			SendItem(clientId, SlotType::Equip, 15, &pMob[clientId].Mobs.Player.Equip[15]);

			if(LOCAL_797 == 7)
				SendClientMessage(clientId, g_pLanguageString[_NN_My_King_Bless1]);
			else
				SendClientMessage(clientId, g_pLanguageString[_NN_My_King_Bless2]);

			pMob[clientId].GetCurrentScore(clientId);

			p364 packet{};
			GetCreateMob(clientId, reinterpret_cast<BYTE*>(&packet));

			GridMulticast_2(pMob[clientId].Target.X, pMob[clientId].Target.Y, reinterpret_cast<BYTE*>(&packet), 0);
		}
		else
		{
			SendClientMessage(clientId, g_pLanguageString[_DN_Need_D_Sapphire], LOCAL_803);

			return true;
		}
	}
#pragma endregion
#pragma region MEDALHA DO REINO
	else if(LOCAL_526 == 8)
	{//0042BB69
		INT32 LOCAL_811 = pMob[clientId].Leader;
		INT32 LOCAL_812 = pMob[clientId].Mobs.Player.Equip[12].Index;

		if(LOCAL_812 != 508 && (LOCAL_812 < 526 || LOCAL_812 > 528) && (LOCAL_812 < 532 || LOCAL_812 > 534))
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_Need_Guild_Medal]);

			return true;
		}

		//0042BBE6
		if(LOCAL_811 <= 0 || LOCAL_811 >= MAX_PLAYER)
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_Need_Master]);

			return true;
		}

		if(pUser[LOCAL_811].Status != USER_PLAY)
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_Need_Master]);

			return true;
		}

		if(pMob[LOCAL_811].Mobs.Player.GuildIndex != pMob[clientId].Mobs.Player.GuildIndex)
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_Need_Master]);

			return true;
		}

		if(pMob[LOCAL_811].Mobs.Player.GuildMemberType == 0)
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_Need_Master]);

			return true;
		}
		
		if (pUser[clientId].Trade.ClientId)
		{
			RemoveTrade(clientId);
			AddCrackError(clientId, 1, CRACK_TRADE_NOTEMPTY);

			return true;
		}

		INT32 LOCAL_813 = pMob[clientId].Target.X - pMob[LOCAL_811].Target.X;
		INT32 LOCAL_814 = pMob[clientId].Target.Y - pMob[LOCAL_811].Target.Y;

		if(LOCAL_813 < -3 || LOCAL_814 < -1 || LOCAL_813 > 3 || LOCAL_814 > 3)
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_Need_Master]);

			return true;
		}

		INT32 LOCAL_815 = 10;
		INT32 LOCAL_816 = GetInventoryAmount(clientId, 697);
		INT32 LOCAL_817 = 0;

		if(LOCAL_816 < LOCAL_815)
		{
			SendClientMessage(clientId, g_pLanguageString[_DN_Need_D_Sapphire2], LOCAL_815);

			return true;
		}

		for(LOCAL_817 = 0; LOCAL_817 < 60; LOCAL_817 ++)
		{
			if(pMob[clientId].Mobs.Player.Inventory[LOCAL_817].Index == 697)
			{
				while(pMob[clientId].Mobs.Player.Inventory[LOCAL_817].Index == 697)
				{
					AmountMinus(&pMob[clientId].Mobs.Player.Inventory[LOCAL_817]);

					LOCAL_815 --;
					if(LOCAL_815 <= 0)
						break;
				}

				SendItem(clientId, SlotType::Inv, LOCAL_817, &pMob[clientId].Mobs.Player.Inventory[LOCAL_817]);
			}

			if(LOCAL_815 <= 0)
				break;
		}

/*		if(pMob[clientId].Mobs.MedalId == 508)
			pMob[clientId].Mobs.MedalId = 522;
		else
			pMob[clientId].Mobs.MedalId += 3;
			*/
		INT32 LOCAL_818 = pMob[LOCAL_811].Mobs.Player.CapeInfo;
		if(LOCAL_818 == 7)
			SendClientMessage(clientId, g_pLanguageString[_NN_My_King_Bless1]);
		else
			SendClientMessage(clientId, g_pLanguageString[_NN_My_King_Bless2]);

		SendItem(clientId, SlotType::Equip, 12, &pMob[clientId].Mobs.Player.Equip[12]);

		pMsgSignal packet;
		packet.Header.PacketId = 0x193;
		packet.Header.Size = sizeof pMsgSignal;
		packet.Header.ClientId = clientId;

		packet.Value = pMob[clientId].Mobs.Player.CapeInfo;

		GridMulticast_2(pMob[clientId].Target.X, pMob[clientId].Target.Y, (BYTE*)&packet, 0);

		
	}
#pragma endregion
#pragma region CRIAR SEPHIROT
	else if(LOCAL_526 == 9)
	{
		if(LOCAL_525 != 1)
		{
			SendSay(npcId, g_pLanguageString[_NN_Sephirot_AreUSure]);

			return true;
		}

		short itens[8]; 
		memset(itens, 0, sizeof itens);

		if (pMob[clientId].Mobs.Player.Equip[10].Index == 1742)
		{
			for (int i = 0; i < 8; i++)
			{
				int item = GetFirstSlot(clientId, 1744 + i);
				if (item == -1)
				{
					SendSay(npcId, g_pLanguageString[_NN_Sephirot_EightStones]);

					return true;
				}

				itens[i] = item;
			}

			if (pMob[clientId].Mobs.Player.Gold < 30000000)
			{
				SendSay(npcId, g_pLanguageString[_NN_Sephirot_Need30MGold]);

				return true;
			}

			pMob[clientId].Mobs.Player.Gold -= 30000000;
			pMob[clientId].Mobs.Player.Inventory[itens[0]].Index = 1760 + static_cast<short>(pMob[npcId].Mobs.Player.Exp);

			Log(clientId, LOG_INGAME, "Sephirot %s criada.", ItemList[1760 + pMob[npcId].Mobs.Player.Exp].Name);

			for (int i = 1; i < 8; i++)
			{
				memset(&pMob[clientId].Mobs.Player.Inventory[itens[i]], 0, 8);

				SendItem(clientId, SlotType::Inv, itens[i], &pMob[clientId].Mobs.Player.Inventory[itens[i]]);
			}

			SendItem(clientId, SlotType::Inv, itens[0], &pMob[clientId].Mobs.Player.Inventory[itens[0]]);

			SendSignalParm(clientId, clientId, 0x3AF, pMob[clientId].Mobs.Player.Gold);
			SendSay(npcId, g_pLanguageString[_NN_Sephirot_Compose]);
		}
		else if (pMob[clientId].Mobs.Player.Equip[10].Index == 4646)
		{
			int slotId = GetFirstSlot(clientId, 0);
			if (slotId == -1)
			{
				SendClientMessage(clientId, "Sem espaao no inventario");

				return true;
			}

			pMob[clientId].Mobs.Player.Inventory[slotId] = STRUCT_ITEM{};
			pMob[clientId].Mobs.Player.Inventory[slotId].Index = 1760 + static_cast<short>(pMob[npcId].Mobs.Player.Exp);

			SendItem(clientId, SlotType::Inv, slotId, &pMob[clientId].Mobs.Player.Inventory[slotId]);

			AmountMinus(&pMob[clientId].Mobs.Player.Equip[10]);

			SendItem(clientId, SlotType::Equip, 10, &pMob[clientId].Mobs.Player.Equip[10]);
			Log(clientId, LOG_INGAME, "Sephirot %s criada usando Sephirot Vazia.", ItemList[1760 + pMob[npcId].Mobs.Player.Exp].Name);

			SendSay(npcId, g_pLanguageString[_NN_Sephirot_Compose]);
		}
	}
#pragma endregion
#pragma region MESTRE DAS HABILIDADES
	else if(LOCAL_526 == 13)
	{
		UINT32 LOCAL_831 = 5;
		if(pMob[clientId].Mobs.Player.QuestInfo.MestreHab && sServer.StatSapphire < LOCAL_831)
		{
			SendSay(npcId, g_pLanguageString[_NN_Youve_Done_It_Already]);

			return true;
		}

		if(LOCAL_525 == 0)
		{
			SendSay(npcId, g_pLanguageString[_DN_Want_Stat_Init], sServer.StatSapphire);

			return true;
		}
		
		INT32 LOCAL_832 = 1;
		for(; LOCAL_832 < 8; LOCAL_832 ++)
		{
			if(pMob[clientId].Mobs.Player.Equip[LOCAL_832].Index != 0)
			{
				SendSay(npcId, g_pLanguageString[_NN_Cant_with_armor]);

				return true;
			}
		}

		INT32 LOCAL_833 = sServer.StatSapphire,
			  LOCAL_834 = GetInventoryAmount(clientId, 697);

		int num = 0;
		INT32 retorno   = GetFirstSlot(clientId, 3336);
		if(LOCAL_834 < LOCAL_833 && retorno == -1)
		{
			int packSapph = GetInventoryAmount(clientId, 4131);
			if (packSapph != -1)
				num += (10 * packSapph);

			num += LOCAL_834;
			if (num < LOCAL_833)
			{
				SendClientMessage(clientId, g_pLanguageString[_DN_Need_D_Sapphire2], LOCAL_833);

				return true;
			}

			if(packSapph > 3)
				packSapph = 3;

			LOCAL_833 -= (RemoveAmount(clientId, 4131, packSapph) * 10);
			Log(clientId, LOG_INGAME, "Mestre das Habilidades - Removido %d pacs de 10 safiras", packSapph);
		}

		int iterator = 0;
		if(retorno == -1)
		{
			iterator = RemoveAmount(clientId, 697, LOCAL_833);
			
			Log(clientId, LOG_INGAME, "Mestre das Habilidades - Removido %d safiras", iterator);
			LOCAL_833 -= iterator;
		}

		INT32 LOCAL_835 = pMob[clientId].Mobs.Player.ClassInfo;
		if(LOCAL_835 < 0 || LOCAL_835 > 3)
			return true;

		INT32 LOCAL_836 = 100,
			  LOCAL_837 = pMob[clientId].Mobs.Player.StatusPoint,
			  LOCAL_838 = pMob[clientId].Mobs.Player.bStatus.STR - BaseSIDCHM[LOCAL_835][0],
			  LOCAL_839 = pMob[clientId].Mobs.Player.bStatus.INT - BaseSIDCHM[LOCAL_835][1],
			  LOCAL_840 = pMob[clientId].Mobs.Player.bStatus.DEX - BaseSIDCHM[LOCAL_835][2],
			  LOCAL_841 = pMob[clientId].Mobs.Player.bStatus.CON - BaseSIDCHM[LOCAL_835][3];
		
		if(retorno != -1)
			LOCAL_836 = 2000;

		if(LOCAL_838 > LOCAL_836)
		{
			pMob[clientId].Mobs.Player.bStatus.STR -= LOCAL_836;
			LOCAL_837 += LOCAL_836;
		}
		else
		{
			pMob[clientId].Mobs.Player.bStatus.STR -= LOCAL_838;
			LOCAL_837 += LOCAL_838;
		}

		if(LOCAL_839 > LOCAL_836)
		{
			pMob[clientId].Mobs.Player.bStatus.INT -= LOCAL_836;
			LOCAL_837 += LOCAL_836;
		}
		else
		{
			pMob[clientId].Mobs.Player.bStatus.INT -= LOCAL_839;
			LOCAL_837 += LOCAL_839;
		}
		
		if(LOCAL_840> LOCAL_836)
		{
			pMob[clientId].Mobs.Player.bStatus.DEX -= LOCAL_836;
			LOCAL_837 += LOCAL_836;
		}
		else
		{
			pMob[clientId].Mobs.Player.bStatus.DEX -= LOCAL_840;
			LOCAL_837 += LOCAL_840;
		}

		if(LOCAL_841 > LOCAL_836)
		{
			pMob[clientId].Mobs.Player.bStatus.CON -= LOCAL_836;
			LOCAL_837 += LOCAL_836;
		}
		else
		{
			pMob[clientId].Mobs.Player.bStatus.CON -= LOCAL_841;
			LOCAL_837 += LOCAL_841;
		}

		if(retorno != -1)
		{
			AmountMinus(&pMob[clientId].Mobs.Player.Inventory[retorno]);

			SendItem(clientId, SlotType::Inv, retorno, &pMob[clientId].Mobs.Player.Inventory[retorno]);
		}

		pMob[clientId].GetCurrentScore(clientId);

		SetAffect(clientId, 0x2C, 20, 20);

		SendScore(clientId);
		SendEtc(clientId);

		p364 packet;
		GetCreateMob(clientId, (BYTE*)&packet);

		GridMulticast_2(pMob[clientId].Target.X, pMob[clientId].Target.Y, (BYTE*)&packet, 0);
		return true;
	}
#pragma endregion
	// NPCs configurados pelo Level 
	// TODO : Alterar para merchant + race
	else if(LOCAL_526 == 100)
	{ 
		INT32 npcType = pMob[npcId].Mobs.Player.Status.Level;
#pragma region NPCS ENTRADA QUEST INICIANTE (COVEIRO, ...)
		// NPCs de entradas de quest
		if(npcType >= 5 && npcType <= 9)
		{
			INT32 questId  = npcType - 5;
			UINT32 reqMinLevel = g_pQuestLevel[questId][0];
			UINT32 reqMaxLevel = g_pQuestLevel[questId][1];
			
			if(pMob[clientId].Mobs.Player.Equip[0].EFV2 >= CELESTIAL)
			{
				SendSay(npcId, g_pLanguageString[_NN_Only_MortalArch]);

				return true;
			}

			if(pMob[clientId].Mobs.Player.bStatus.Level >= reqMinLevel && pMob[clientId].Mobs.Player.bStatus.Level <= reqMaxLevel)
			{
				if (pMob[clientId].Target.X >= MaxMinCoordsQuest[questId][0] && pMob[clientId].Target.Y >= MaxMinCoordsQuest[questId][1] &&
					pMob[clientId].Target.X <= MaxMinCoordsQuest[questId][2] && pMob[clientId].Target.Y <= MaxMinCoordsQuest[questId][3])
				{
					SendClientMessage(clientId, "Ja esta dentro da quest!");

					return true;						
				}

				for (int i = 1; i < MAX_PLAYER; i++)
				{
					if (pUser[i].Status != USER_PLAY || memcmp(MacAddress, pUser[i].MacAddress, 8) != 0)
						continue;

					if (pMob[i].Target.X >= MaxMinCoordsQuest[questId][0] && pMob[i].Target.Y >= MaxMinCoordsQuest[questId][1] &&
						pMob[i].Target.X <= MaxMinCoordsQuest[questId][2] && pMob[i].Target.Y <= MaxMinCoordsQuest[questId][3])
					{
						SendClientMessage(clientId, "Somente uma conta por computador na mesma quest.");

						return true;
					}
				}

				Teleportar(clientId, g_pQuestTele[questId][0], g_pQuestTele[questId][1]);

				SendSay(npcId, g_pLanguageString[_NN_Player_QuestEnter], pMob[clientId].Mobs.Player.Name);

				static const char QuestsNames[][16]  = {"Coveiro", "Jardim", "Kaizen", "Hidra", "Elfo"};

				Log(clientId, LOG_INGAME, "%s entrou na quest [%s].", pMob[clientId].Mobs.Player.Name, QuestsNames[questId]);
				QuestAccess = questId + 1;
			}
			else
				SendSay(npcId, g_pLanguageString[_NN_Level_NotAllowed], reqMinLevel + 1, reqMaxLevel + 1);
		}
#pragma endregion
#pragma region NPC PERZEN
		else if (npcType >= 11 && npcType <= 13)
		{
			INT32 type = npcType - 11,
				searched = (4128 + type);

			//Procura o item especafico no inventario do personagem
			INT32 slot = GetFirstSlot(clientId, searched);

			if (slot == -1)
			{
				SendSay(npcId, g_pLanguageString[_NN_GiveMe_Item], ItemList[searched].Name);

				return true;
			}

			// Apaga o item totalmente para nao restar adicionais
			memset(&pMob[clientId].Mobs.Player.Inventory[slot], 0, sizeof STRUCT_ITEM);

			// Entrega o item
			pMob[clientId].Mobs.Player.Inventory[slot].Index = 3986 + type;

			// Atualiza o inventario
			SendItem(clientId, SlotType::Inv, slot, &pMob[clientId].Mobs.Player.Inventory[slot]);

			// Envia a mensagem
			SendSay(npcId, g_pLanguageString[_NN_Received_Mount_Perzen], ItemList[3986 + type].Name);
		}
#pragma endregion
#pragma region JULI
		else if (npcType == 14)
		{
			INT32 village = GetVillage(pMob[clientId].Target.X, pMob[clientId].Target.Y);

			if (village == 3)
				Teleportar(clientId, 2482, 1652);
			else
			{
				INT32 level = pMob[clientId].Mobs.Player.Status.Level,
					ev = pMob[clientId].Mobs.Player.Equip[0].EFV2;

				if (ev == MORTAL && level < 255)
				{
					SendSay(npcId, g_pLanguageString[_NN_CantTele_Nip]);

					return true;
				}

				SendSay(npcId, g_pLanguageString[_NN_Welcome_Nipp]);

				Teleportar(clientId, 3649, 3140);
			}
		}
#pragma endregion
#pragma region QUEST CAPA VERDE - TELEPORTADOR
		else if (npcType == 20)
		{
			if (pMob[clientId].Mobs.Player.bStatus.Level < 99 || pMob[clientId].Mobs.Player.bStatus.Level > 149)
			{
				SendSay(npcId, g_pLanguageString[_NN_Level_NotAllowed], 100, 150);

				return true;
			}

			if (pMob[clientId].Mobs.Player.Equip[0].EFV2 != MORTAL)
			{
				SendSay(npcId, "Somente para personagens mortais");

				return true;
			}

			Teleportar(clientId, 2242, 1577);

			static const char* g_pMessageLearner[4] =
			{
				"Tenha cuidado, futuro aprendiz",
				"Voca a corajoso por querer entrar aa.",
				"Sua coragem sera recompensada!",
				"Voca a um dos grandes guerreiros de Midgard?" // Asgard
			};

			INT32 rand = Rand() % 4;
			if(rand < 0 || rand >= 4)
				rand = 2;

			SendSay(npcId, g_pMessageLearner[rand]);
			QuestAccess = 5;
		}
#pragma endregion
#pragma region QUEST CAPA VERDE - ENTREGAR CAPA
		else if(npcType == 21 && LOCAL_525 == 0)
		{
			if(pMob[clientId].Mobs.Player.bStatus.Level < 99 || pMob[clientId].Mobs.Player.bStatus.Level > 149)
			{
				SendSay(npcId, g_pLanguageString[_NN_Level_NotAllowed], 100, 150);

				return true;
			}

			if (pMob[clientId].Mobs.Player.Equip[0].EFV2 != MORTAL)
			{
				SendSay(npcId, "Somente para personagens mortais");

				return true;
			}

			if(pMob[clientId].Mobs.Player.Equip[15].Index == 4006)
			{
				SendSay(npcId, g_pLanguageString[_NN_Already_A_Learner]);

				return true;
			}

			if(pMob[clientId].Mobs.Player.Equip[13].Index != 4080)
			{
				SendSay(npcId, g_pLanguageString[_NN_BringMe_ToLearner]);

				return true;
			}
			
			memset(&pMob[clientId].Mobs.Player.Equip[15], 0, sizeof STRUCT_ITEM);
			memset(&pMob[clientId].Mobs.Player.Equip[13], 0, sizeof STRUCT_ITEM);

			pMob[clientId].Mobs.Player.Equip[15].Index = 4006;
			
			SendItem(clientId, SlotType::Equip, 13, &pMob[clientId].Mobs.Player.Equip[13]);
			SendItem(clientId, SlotType::Equip, 15, &pMob[clientId].Mobs.Player.Equip[15]);

			SendSay(npcId, g_pLanguageString[_NN_Welcome_Learner], pMob[clientId].Mobs.Player.Name);

			Log(clientId, LOG_INGAME, "%s finalizou a quest da capa verde.", pMob[clientId].Mobs.Player.Name);
			pMob[clientId].GetCurrentScore(clientId);
			SendScore(clientId);
		}
#pragma endregion
#pragma region SOBREVIVENTE
		else if (npcType == 22)
		{
			INT32 slotId = GetFirstSlot(clientId, 4127);
			if (slotId == -1)
			{
				SendSay(npcId, g_pLanguageString[_NN_BringMe_Selado]);

				return true;
			}

			// Da as entradas ao usuario
			pMob[clientId].Mobs.HallEnter += 25;

			// Envia a mensagem
			SendSay(npcId, g_pLanguageString[_NN_HallEnter], pMob[clientId].Mobs.HallEnter);

			// Atualiza o inventario
			memset(&pMob[clientId].Mobs.Player.Inventory[slotId], 0, sizeof STRUCT_ITEM);
			SendItem(clientId, SlotType::Inv, slotId, &pMob[clientId].Mobs.Player.Inventory[slotId]);

			INT32 _rand = Rand() % 100;
			if (_rand < 20)
				SendSay(npcId, "Boa sorte, meu jovem!");
			else if (_rand < 40)
				SendSay(npcId, "Que os Deuses te ajude, guerreiro!");
			else if (_rand < 60)
				SendSay(npcId, "Voca vai precisar de muita sorte, %s", pMob[clientId].Mobs.Player.Name);
			else
				SendSay(npcId, "Vai precisar de uma equipe aa dentro!");

			Log(clientId, LOG_INGAME, "Nova Entrada Hall Kefra. Total: %d", pMob[clientId].Mobs.HallEnter);
		}
#pragma endregion
#pragma region NPC MOLAR DE GaRGULA (TELEPORTADOR)
		else if (npcType == 30)
		{
			if (pMob[clientId].Mobs.Player.bStatus.Level < 199 || pMob[clientId].Mobs.Player.bStatus.Level > 254)
			{
				SendSay(npcId, g_pLanguageString[_NN_Level_NotAllowed], 200, 255);

				return true;
			}

			for (const auto& user : pUser)
			{
				if (user.Status != USER_PLAY || memcmp(user.MacAddress, MacAddress, 8) != 0)
					continue;

				if (pMob[user.clientId].Target.X >= 793 && pMob[user.clientId].Target.X <= 828 && pMob[user.clientId].Target.Y >= 4046 && pMob[user.clientId].Target.Y <= 4080)
				{
					SendClientMessage(clientId, "Somente uma conta por computador nesta area");
					Log(clientId, LOG_INGAME, "O usuario %s ja esta na quest do Molar de Gargula", user.User.Username);
					return true;
				}
			}

			Teleportar(clientId, 811, 4055);
		}
#pragma endregion
#pragma region UXMAL
		else if (npcType == 33)
		{
			time_t rawnow = time(NULL);
			struct tm now; localtime_s(&now, &rawnow);

			if(!sServer.FirstKefra)
			{
				SendSay(npcId, g_pLanguageString[_NN_Sorry]);

				Log(SERVER_SIDE, LOG_HACK, "Clicou no Uxmal sem ser no canal que o Kefra morreu primeiro %s [%s] [%dx %dy]", pMob[clientId].Mobs.Player.Name,
					User.Username, pMob[clientId].Target.X, pMob[clientId].Target.Y);
				return true;
			}

			if ((now.tm_min >= 16 && now.tm_min <= 19) || (now.tm_min >= 36 && now.tm_min <= 39) || (now.tm_min >= 56 && now.tm_min <= 59))
			{
				if (pMob[clientId].Leader != -1 && pMob[clientId].Leader != 0)
				{
					SendSay(npcId, "O registro da quest pode ser usado apenas pelos laderes do grupo");

					return true;
				}

				int slotId = GetFirstSlot(clientId, 5134);
				if (slotId == -1)
				{
					SendSay(npcId, "Para registrar a necessario uma Pista Runas");

					return true;
				}

				int ref = GetItemSanc(&pMob[clientId].Mobs.Player.Inventory[slotId]);
				if (ref > 6)
				{
					SendSay(npcId, "Sa estao disponaveis ata a sala +6.");

					return true;
				}

				int maxParty = -1;
				switch (ref)
				{
				case 0:
					maxParty = 2;
					break;
				case 1:
					maxParty = 3;
					break;
				case 2:
					maxParty = 3;
					break;
				case 3:
					maxParty = 2;
					break;
				case 4:
					maxParty = 2;
					break;
				case 5:
					maxParty = 2;
					break;
				case 6:
					maxParty = 2;
					break;
				}

				if (!maxParty)
				{
					SendSay(npcId, "Maximo de grupos incorreto ... Contate a administraaao");

					return true;
				}

				for (int i = 0; i < 10; ++i)
				{
					for (int iParty = 0; iParty < MAX_PARTYPISTA; ++iParty)
					{
						if (pPista[i].Clients[iParty][12] == clientId)
						{
							SendSay(npcId, "Voca ja tem uma pista registrada");

							return true;
						}
					}
				}

				STRUCT_PISTA_DE_RUNAS *pista = &pPista[ref];

				int i = 0;
				for (i = 0; i < maxParty; i++)
				{
					if (!(pista->Clients[i][12]))
						break;
				}

				if (i == maxParty)
				{
					SendSay(npcId, "Maximo de grupo atingido...");

					return true;
				}

				// Registra o lader para o grupo estar como usado
				pista->Clients[i][12] = clientId;

				Log(clientId, LOG_INGAME, "Pista de Runas %d registrada. %s", ref, pMob[clientId].Mobs.Player.Name);

				// Pega todos os membros do grupo
				for (int x = 0; x < 12; x++)
				{
					int memberId = pMob[clientId].PartyList[x];
					if (memberId <= 0 || memberId >= MAX_PLAYER)
						continue;

					if (pUser[memberId].Status != USER_PLAY)
						continue;

					pista->Clients[i][x] = memberId;

					Log(clientId, LOG_INGAME, "Pista de Runas +%d - %d - %s", ref, x, pMob[memberId].Mobs.Player.Name);
					Log(memberId, LOG_INGAME, "Pista de Runas +%d grupo de %s", ref, pMob[clientId].Mobs.Player.Name);
				}

				SendSay(npcId, "Pista +%d registrada por %s", ref, pMob[clientId].Mobs.Player.Name);

				pMob[clientId].Mobs.Player.Inventory[slotId] = STRUCT_ITEM{};
				SendItem(clientId, SlotType::Inv, slotId, &pMob[clientId].Mobs.Player.Inventory[slotId]);
			}
			else
				SendSay(npcId, "Nao a possavel registrar agora ...");
		}
#pragma endregion
#pragma region GUARDA REAL - CAPAS (TELEPORTAR QUEST REINOS)
		else if(npcType == 35)
		{
			if(pMob[clientId].Mobs.Player.Equip[0].EFV2 != MORTAL)
			{
				SendSay(npcId, g_pLanguageString[_NN_OnlyMortal]);

				return true;
			}

			if(pMob[clientId].Mobs.Player.bStatus.Level < 219 || pMob[clientId].Mobs.Player.bStatus.Level > 250)
			{
				SendSay(npcId, g_pLanguageString[_NN_Level_NotAllowed], 220, 250);

				return true;
			}	

			SendSay(npcId, g_pLanguageString[_NN_Initialized_Quest], "Cavaleiro do Reino");
			Teleportar(clientId, 1727, 1727);
		}
#pragma endregion
#pragma region NPCS AREA TREINO
		else if (npcType >= 40 && npcType <= 43)
		{
			INT32 LOCAL_535 = npcType - 40;
			if(pMob[clientId].Mobs.Player.bStatus.Level > 40 && pMob[clientId].Mobs.Player.bStatus.Level < 1000)
				return true;

			INT32 questId = 1 << (6 + LOCAL_535);
			if(pMob[clientId].Mobs.Player.QuestInfo.Value & questId)
			{
				SendSay(npcId, g_pLanguageString[_NN_NewbieQuest_Already1 + (LOCAL_535 * 4)]);
			
				return true;
			}

			INT32 LOCAL_536 = LOCAL_535 + 451;
			if(LOCAL_536 == 454)
				LOCAL_536 = 524;

			INT32 LOCAL_537 = 0;
			for(; LOCAL_537 < 60; LOCAL_537 ++)
			{
				if(pMob[clientId].Mobs.Player.Inventory[LOCAL_537].Index == LOCAL_536)
					break;
			}

			if(LOCAL_537 == 60)
			{
				SendSay(npcId, g_pLanguageString[_NN_NewbieQuest_Already1 + (LOCAL_535 * 4)]);

				return true;
			}

			SendSay(npcId, g_pLanguageString[_NN_NewbieQuest_Complete1 + (LOCAL_535 * 4)]);
			SendClientMessage(clientId, g_pLanguageString[_NN_NewbieQuest_Reward1 + (LOCAL_535 * 4)]);

			pMob[clientId].Mobs.Player.QuestInfo.Value |= questId;

			if(LOCAL_535 == 0)
			{
				STRUCT_ITEM LOCAL_539;
				memset(&LOCAL_539, 0, sizeof STRUCT_ITEM);

				LOCAL_539.Index = 682;
				LOCAL_539.Effect[0].Index = EF_AMOUNT;
				LOCAL_539.Effect[0].Value = 20;

				PutItem(clientId, &LOCAL_539);
			}
			else if(LOCAL_535 == 1)
			{
				INT32 LOCAL_540 = pMob[clientId].Mobs.Player.Equip[6].Index;

				if(LOCAL_540 > 0 && LOCAL_540 <= MAX_ITEMLIST)
				{
					INT32 LOCAL_541 = ItemList[LOCAL_540].Level;

					if(LOCAL_541 > 32 && LOCAL_541 < 1000)
						return true;

					INT32 t = 0;
					for( ; t < 3; t++)
					{
						if(pMob[clientId].Mobs.Player.Equip[6].Effect[t].Index == 43)
							break;
					}

					if(t == 3)
						t = 0;

					INT32 LOCAL_542 = 50;
					INT32 LOCAL_543 = *(WORD*)&pMob[clientId].Mobs.Player.Equip[6].Effect[t].Index;
					
					pMob[clientId].Mobs.Player.Equip[6].Effect[0].Index = 0;
					pMob[clientId].Mobs.Player.Equip[6].Effect[1].Index = 0;
					pMob[clientId].Mobs.Player.Equip[6].Effect[2].Index = 0;
					pMob[clientId].Mobs.Player.Equip[6].Effect[0].Value = 0;
					pMob[clientId].Mobs.Player.Equip[6].Effect[1].Value = 0;
					pMob[clientId].Mobs.Player.Equip[6].Effect[2].Value = 0;

					SetItemBonus(&pMob[clientId].Mobs.Player.Equip[6], LOCAL_541 + LOCAL_542, 1, 0);

					for(t = 0; t < 3; t++)
					{
						if(pMob[clientId].Mobs.Player.Equip[6].Effect[t].Index == 43)
						{
							*(WORD*)&pMob[clientId].Mobs.Player.Equip[6].Effect[t].Index = LOCAL_543;

							break;
						}
					}

					if(t == 3)
					{
						for(t = 0; t < 3; t++)
						{
							if(pMob[clientId].Mobs.Player.Equip[6].Effect[t].Index == 0)
							{
								*(WORD*)&pMob[clientId].Mobs.Player.Equip[6].Effect[t].Index = LOCAL_543;

								break;
							}
						}
					}
					SendItem(clientId, SlotType::Equip, 6, &pMob[clientId].Mobs.Player.Equip[6]);
				}
			}
			else if(LOCAL_535 == 2)
			{
				for(INT32 LOCAL_544 = 1; LOCAL_544 < 8; LOCAL_544++)
				{
					INT32 LOCAL_545 = pMob[clientId].Mobs.Player.Equip[LOCAL_544].Index;

					if(LOCAL_545 < 500 || LOCAL_545 > MAX_ITEMLIST)
						continue;

					INT32 LOCAL_546 = GetItemSanc(&pMob[clientId].Mobs.Player.Equip[LOCAL_544]);
					if(LOCAL_546 > 6)
						continue;

					if(LOCAL_544 < 6)
						LOCAL_546 = LOCAL_546 + Rand() % 4 + 1;
					else
						LOCAL_546 = LOCAL_546 + Rand() % 3 + 1;

					if(LOCAL_546 > 6)
						LOCAL_546 = 6;

					SetItemSanc(&pMob[clientId].Mobs.Player.Equip[LOCAL_544], LOCAL_546, 0);

					SendItem(clientId, SlotType::Equip, LOCAL_544, &pMob[clientId].Mobs.Player.Equip[LOCAL_544]);
				}

				int slotId = GetFirstSlot(clientId, 0);
				if (slotId == -1)
					SendClientMessage(clientId, "Sem espaao no inventario");
				else
				{
					STRUCT_ITEM& item = pMob[clientId].Mobs.Player.Inventory[slotId];
					memset(&item, 0, sizeof STRUCT_ITEM);

					item.Index = 4016;
					item.Effect[0].Index = EF_AMOUNT;
					item.Effect[0].Value = 5;

					SendItem(clientId, SlotType::Inv, slotId, &item);
				}
			}
			else if(LOCAL_535 == 3)
			{
				INT32 LOCAL_547 = Rand() % 3;
				STRUCT_ITEM LOCAL_549;
				memset(&LOCAL_549, 0, sizeof STRUCT_ITEM);

				if(LOCAL_547 == 0)
				{
					LOCAL_549.Index = 682;
					LOCAL_549.Effect[0].Index = EF_AMOUNT;
					LOCAL_549.Effect[0].Value = 20;

					PutItem(clientId, &LOCAL_549);
				}
				else if(LOCAL_547 == 1)
				{
					LOCAL_549.Index = 481;

					PutItem(clientId, &LOCAL_549);
				}
				else if(LOCAL_547 == 2)
				{
					LOCAL_549.Index = 652;

					PutItem(clientId, &LOCAL_549);
				}
			}
		
			SetAffect(clientId, 0x2C, 200, 200);

			SendAffect(clientId);

			p364 create;
			GetCreateMob(clientId, (BYTE*)&create);

			GridMulticast_2(pMob[clientId].Target.X, pMob[clientId].Target.Y, (BYTE*)&create, 0);		

			pMob[clientId].GetCurrentScore(clientId);
			SendScore(clientId);

			// Nao deve remover a chave

			if(LOCAL_535 == 3)
			{
				memset(&pMob[clientId].Mobs.Player.Inventory[LOCAL_537], 0, sizeof STRUCT_ITEM);
				SendItem(clientId, SlotType::Inv, LOCAL_537, &pMob[clientId].Mobs.Player.Inventory[LOCAL_537]);
			}
		}
#pragma endregion
#pragma region CARBUNCLE
		else if (npcType >= 44 && npcType <= 48)
		{
			if (pMob[clientId].Mobs.Player.Equip[0].EFV2 != MORTAL)
			{
				SendSay(npcId, g_pLanguageString[_NN_OnlyMortal]);

				return true;
			}
			if (pMob[clientId].Mobs.Player.bStatus.Level >= 255)
			{
				SendSay(npcId, "Voca ja a forte! Nao precisa mais de ajuda.");

				return true;
			}

			switch (npcType - 44)
			{
				case 0: // Velocidade
				{
					SetAffect(clientId, 41, 50);
					break;
				}
				case 1: // Defesa
				{
					SetAffect(clientId, 43, 50);
					break;
				}
				case 2: // Dano
				{
					SetAffect(clientId, 44, 50);
					break;
				}
				case 3: // Skill
				{
					SetAffect(clientId, 45, 50);
					break;
				}
				case 4: // Todas
				{
					SetAffect(clientId, 41, 25);
					SetAffect(clientId, 43, 25);
					SetAffect(clientId, 44, 25);
					SetAffect(clientId, 45, 25);
					break;
				}
				default:
					break;
			}
			pMob[clientId].GetCurrentScore(clientId);

			SendScore(clientId);

			SendSay(npcId, "Sente-se mais forte agora, %s?", pMob[clientId].Mobs.Player.Name);
			return true;
		}
#pragma endregion
	#pragma region URNAMMU
		else if (npcType == 49)
		{
			//TROCA DE CLASSE SUB
			if (pMob[clientId].Mobs.Player.Equip[11].Index >= 1760 && pMob[clientId].Mobs.Player.Equip[11].Index <= 1763)
			{
				if (pMob[clientId].Mobs.Sub.Status == 0)
				{
					SendClientMessage(clientId, g_pLanguageString[_NN_Sorry]);
					return true;
				}

				if (pMob[clientId].Mobs.Player.Equip[0].EFV2 == SUBCELESTIAL)
				{
					SendClientMessage(clientId, "a necessario estar no personagem celestial.");
					return true;
				}

				if (pMob[clientId].Mobs.Fame < 2000)
				{
					SendClientMessage(clientId, g_pLanguageString[_NN_Need_XX_Fame], 2000);
					return true;
				}

				if((pMob[clientId].Mobs.Player.Equip[0].Index >= 22 && pMob[clientId].Mobs.Player.Equip[0].Index <= 25) || pMob[clientId].Mobs.Player.Equip[0].Index == 32)
				{
					SendClientMessage(clientId, "Nao a possavel trocar de classe transformado.");
					return true;
				}

				pMob[clientId].Mobs.Fame -= 2000;

				INT32 classInfo = (pMob[clientId].Mobs.Player.Equip[11].Index - 1760);

				INT32 baseFace = GetInfoClass(pMob[clientId].Mobs.Player.Equip[0].Index);
				if(baseFace == 4)
					return true;

				baseFace = (baseFace * 10) + 6;
				Log(clientId, LOG_INGAME, "Trocou a classe do SubCelestial. Antiga:%d Nova:%d. Level: %d", pMob[clientId].Mobs.Sub.Equip[0].Index - baseFace, classInfo,
					pMob[clientId].Mobs.Sub.SubStatus.Level);

				pMob[clientId].Mobs.Sub.Equip[0].Index = baseFace + classInfo;
				pMob[clientId].Mobs.Sub.Equip[0].EF2 = baseFace + classInfo;

				memset(pMob[clientId].Mobs.Sub.Affect, 0, 32);

				memset(&pMob[clientId].Mobs.Player.Equip[11], 0, sizeof STRUCT_ITEM);

				SendItem(clientId, SlotType::Equip, 11, &pMob[clientId].Mobs.Player.Equip[11]);

				SendClientMessage(clientId, g_pLanguageString[_NN_God_Continue_Blessing]);
				return true;
			}
		}
#pragma endregion
#pragma region SACERDOTIZA AMELIA
		else if (npcType == 51)
		{		
			int slot = GetFirstSlot(clientId, 4125);

			if (pMob[clientId].Mobs.Player.bStatus.Level < 119 ||
				pMob[clientId].Mobs.Player.bStatus.Level > 124)
			{
				SendClientMessage(clientId, "Level inadequado.");

				return true;
			}

			if (pMob[clientId].Mobs.Player.Equip[0].EFV2 != MORTAL)
			{
				SendClientMessage(clientId, "Somente para mortais.");

				return true;
			}

			if (slot == -1)
			{
				SendClientMessage(clientId, "Onde esta o Pedaao do Equilabrio?.");

				return true;
			}

			AmountMinus(&pMob[clientId].Mobs.Player.Inventory[slot]);
			SendItem(clientId, SlotType::Inv, slot, &pMob[clientId].Mobs.Player.Inventory[slot]);

			STRUCT_ITEM item;
			memset(&item, 0, sizeof STRUCT_ITEM);

			item.Index = 4126;

			PutItem(clientId, &item);

			SendClientMessage(clientId, "Recebeu sua recompensa.");

			return true;
		}
#pragma endregion
#pragma region GUARDA EQUILIBRIO DA FORaA
		else if (npcType == 52)
		{
			if (pMob[clientId].Mobs.Player.bStatus.Level < 119 ||
				pMob[clientId].Mobs.Player.bStatus.Level > 124)
			{
				SendClientMessage(clientId, "Level inadequado.");

				return true;
			}

			if (pMob[clientId].Mobs.Player.Equip[0].EFV2 != MORTAL)
			{
				SendClientMessage(clientId, "Somente para mortais.");

				return true;
			}

			Teleportar(clientId, 1962, 1598);

			return true;
		}
#pragma endregion
#pragma region KINGDOM BROKER
		else if(npcType == 374)
		{
			if(pMob[clientId].Mobs.Player.GuildIndex != 0)
			{
				SendClientMessage(clientId, "Membros de guild nao podem alterar a capa");

				return true;
			}
			
			INT32 capeInfo = pMob[clientId].Mobs.Player.CapeInfo;
			if(capeInfo != CAPE_BLUE && capeInfo != CAPE_RED)
			{
				SendClientMessage(clientId, "Necessario ter um reino!");

				return true;
			}
			
			int capeId = pMob[clientId].Mobs.Player.Equip[15].Index;
			if (capeId == 0 || capeId == 4006)
			{
				SendClientMessage(clientId, "Necessario ter um reino!");

				return true;
			}

			INT32 LOCAL_805 = GetInventoryAmount(clientId, 697),
				  LOCAL_806 = 0,
				  need      = 30;

			LOCAL_805 += (GetInventoryAmount (clientId, 4131) * 10);
			if(LOCAL_805 < 30)
			{
				SendClientMessage(clientId, g_pLanguageString[_DN_Need_D_Sapphire], need);

				return true;
			}

			for(LOCAL_806 = 0; LOCAL_806 < 60 ; LOCAL_806++)
			{
				if(pMob[clientId].Mobs.Player.Inventory[LOCAL_806].Index == 697)
				{
					while(pMob[clientId].Mobs.Player.Inventory[LOCAL_806].Index == 697)
					{
						AmountMinus(&pMob[clientId].Mobs.Player.Inventory[LOCAL_806]);

						need --;
						if(need <= 0)
							break;
					}

					SendItem(clientId, SlotType::Inv, LOCAL_806, &pMob[clientId].Mobs.Player.Inventory[LOCAL_806]);
				}
				
				if(pMob[clientId].Mobs.Player.Inventory[LOCAL_806].Index == 4131)
				{
					AmountMinus(&pMob[clientId].Mobs.Player.Inventory[LOCAL_806]);

					SendItem(clientId, SlotType::Inv, LOCAL_806, &pMob[clientId].Mobs.Player.Inventory[LOCAL_806]);
					need -= 10;
					if(need <= 0)
						break;
				}

				if(need <= 0)
					break;
			}

			Log(clientId, LOG_INGAME, "Consumido 30 safiras do usuario");

			INT32 _index = capeInfo - CAPE_BLUE;
			for(INT32 i = 0; i < 10; i++)
			{
				if(pMob[clientId].Mobs.Player.Equip[15].Index == g_pCapesID[_index][i])
				{
					pMob[clientId].Mobs.Player.Equip[15].Index = g_pCapesID[2][i];

					SendItem(clientId, SlotType::Equip, 15, &pMob[clientId].Mobs.Player.Equip[15]);
					Log(clientId, LOG_INGAME, "Realizou a troca de capa. %d nova capa", pMob[clientId].Mobs.Player.Equip[15].Index);
					break;
				}
			}

			p364 packet{};
			GetCreateMob(clientId, reinterpret_cast<BYTE*>(&packet));
			GridMulticast_2(pMob[clientId].Target.X, pMob[clientId].Target.Y, reinterpret_cast<BYTE*>(&packet), 0);

			pMob[clientId].GetCurrentScore(clientId);

			SendScore(clientId);
			SendSay(npcId, "Troca realizada com sucesso.");
		}
#pragma endregion
#pragma region SARCEDOTE JESTER
		else if (npcType == 53)
		{
			if (pMob[clientId].Mobs.Player.bStatus.Level < 69 ||
				pMob[clientId].Mobs.Player.bStatus.Level > 74)
			{
				SendClientMessage(clientId, "Level inadequado.");

				return true;
			}

			if (pMob[clientId].Mobs.Player.Equip[0].EFV2 != MORTAL)
			{
				SendClientMessage(clientId, "Somente para mortais.");

				return true;
			}

			Teleportar(clientId, 2655, 1981);

			return true;
		}
#pragma endregion
#pragma region KRUNO
		else if (npcType == 54)
		{
			if (pMob[clientId].Mobs.Player.bStatus.Level < 69 ||
				pMob[clientId].Mobs.Player.bStatus.Level > 74)
			{
				SendClientMessage(clientId, "Level inadequado.");

				return true;
			}

			if (pMob[clientId].Mobs.Player.Equip[0].EFV2 != MORTAL)
			{
				SendClientMessage(clientId, "Somente para mortais.");

				return true;
			}

			int slot = GetFirstSlot(clientId, 4123);

			if (slot == -1)
			{
				SendClientMessage(clientId, "Onde esta o Pedaao de Chance?.");

				return true;
			}

			STRUCT_ITEM item;
			memset(&item, 0, sizeof STRUCT_ITEM);

			item.Index = 4124;

			PutItem(clientId, &item);

			SendClientMessage(clientId, "Recebeu sua recompensa.");
			return true;
		}
#pragma endregion
#pragma region UNICORNIO
		else if(npcType >= 55 && npcType <= 58)
		{  
			static const INT16 dwUniWeapon[] =   {917, 923, 918, 917};
			static const INT16 dwUniWeaponW [] = {939, 943, 940, 941};

			STRUCT_ITEM *item = &pMob[clientId].Mobs.Player.Equip[6];
			INT32    sanc = GetItemSanc(item); 
			
			INT32 index = npcType - 55;
			if(item->Index != dwUniWeapon[index])
			{
				SendSay(npcId, "Traga-me o %s para que eu possa recompensa-lo", ItemList[dwUniWeapon[index]].Name);

				return true;
			}

			if(sanc != 6)
			{
				SendSay(npcId, "O item deve estar +6 para efetuar a troca");

				return true;
			}

			if(pMob[clientId].Mobs.Info.Unicornio)
			{
				SendSay(npcId, "Sa posso ajuda-lo uma vez :(");

				return true;
			}

			memset(item, 0, sizeof STRUCT_ITEM);

			item->Index = dwUniWeaponW[index];

			item->Effect[0].Index = EF_SANC;
			item->Effect[0].Value = 3;

			SendItem(clientId, SlotType::Equip, 6, item);

			SendSay(npcId, "Agora sua jornada vai comeaar de verdade!");
			
			pMob[clientId].Mobs.Info.Unicornio = 1;
		}
#pragma endregion
#pragma region ORACULO PRECTO
		else if (npcType == 59)
		{
			int slotId = GetFirstSlot(clientId, 1740);
			if (slotId == -1)
			{
				INT32 amountItem = GetInventoryAmount(clientId, 4522);
				if(amountItem <= 0)
				{
					SendSay(npcId, "Traga-me as duas almas para fazer a Pedra da Imortalidade");

					return true;
				}

				static INT32 rateSoul[11] = {0, 5, 10, 15, 25, 30, 40, 50, 60, 75, 100};
				if(amountItem > 10)
					amountItem = 10;
				
				INT32 totalPiece = amountItem;
				for(INT32 LOCAL_832 = 0; LOCAL_832 < 60 ; LOCAL_832++)
				{
					if(pMob[clientId].Mobs.Player.Inventory[LOCAL_832].Index == 4522)
					{
						while(pMob[clientId].Mobs.Player.Inventory[LOCAL_832].Index == 4522)
						{
							AmountMinus(&pMob[clientId].Mobs.Player.Inventory[LOCAL_832]);
							Log(clientId, LOG_INGAME, "Removido Pedaao da Alma do slot %d", LOCAL_832);

							amountItem --;

							if (amountItem <= 0)
								break;
						}

						SendItem(clientId, SlotType::Inv, LOCAL_832, &pMob[clientId].Mobs.Player.Inventory[LOCAL_832]);
					}

					if(amountItem <= 0)
						break;
				}

				INT32 rate = rateSoul[totalPiece],
					 _rate = Rand () % 100;

				if(_rate <= rate) 
				{ // sucesso
					INT32 soul = 1740;
					if((Rand() % 100) >= 50)
						soul = 1741;

					Log(SERVER_SIDE, LOG_INGAME, "%s compos %s com Pedaao da Alma - Rate: %d/%d", User.Username, ItemList[soul].Name, _rate, rate);

					STRUCT_ITEM item{};
					item.Index = soul;

					PutItem(clientId, &item);
					Log(clientId, LOG_INGAME, "Composto com sucesso ALMA com PEDAaO DE ALMA - %s - Rate: %d/%d", ItemList[item.Index].Name, _rate, rate);

					SendNotice("%s compas com sucesso a %s usando Pedaao da Alma", pMob[clientId].Mobs.Player.Name, ItemList[soul].Name);
				}
				else
				{
					SendNotice("%s falhou na composiaao usando Pedaao da Alma", pMob[clientId].Mobs.Player.Name);

					Log(SERVER_SIDE, LOG_INGAME, "%s falhou na composiaaa com Pedaao da Alma - Rate: %d/%d", User.Username, _rate, rate);
					Log(clientId, LOG_INGAME, "Composto com FALHA ALMA com PEDAaO DE ALMA - Rate: %d/%d", _rate, rate);
				}

				return true;
			}

			if (pMob[clientId].Mobs.Player.Inventory[slotId + 1].Index != 1741)
			{
				SendSay(npcId, "Deixe as duas almas juntas para a composiaao.");

				return true;
			}

			int amount = GetInventoryAmount(clientId, 697);
			// Procura por 10 safiras soltas
			if (amount >= 10)
			{
				int iterator = 0;
				// Se tiver consome as 10
				for (int i = 0; i < 60; i++)
				{
					INT32 itemId = pMob[clientId].Mobs.Player.Inventory[i].Index;
					if (itemId != 697)
						continue;

					while (pMob[clientId].Mobs.Player.Inventory[i].Index == 697)
					{
						AmountMinus(&pMob[clientId].Mobs.Player.Inventory[i]);

						iterator++;

						if (iterator >= 10)
							break;
					}

					if (iterator >= 10)
						break;
				}
			}			
			else
			{
				// Caso nao tenha 10 soltas, ele procura pelo pacote
				int slotSapphPack = GetFirstSlot(clientId, 4131);
				if (slotSapphPack == -1)
				{
					// Caso ele nao tenha o pacote e nem as 10 soltas.
					SendSay(npcId, "a necessario 10 safiras para continuar.");

					return true;
				}

				AmountMinus(&pMob[clientId].Mobs.Player.Inventory[slotSapphPack]);
			}
			
			AmountMinus(&pMob[clientId].Mobs.Player.Inventory[slotId]);
			AmountMinus(&pMob[clientId].Mobs.Player.Inventory[slotId + 1]);
			
			pMob[clientId].Mobs.Player.Inventory[slotId].Index = 1742;
			
			SendCarry(clientId);

			SendSay(npcId, "Pedra Eterna foi produzida. Equipe-a e procure seu rei.");

			Log(clientId, LOG_INGAME, "Pedra da Imortalidade produzida.");
		}
#pragma endregion
#pragma region REGISTRO CALABOUaO ZUMBI
		else if (npcType == 60)
		{
			time_t rawnow = time(NULL);
			struct tm now; localtime_s(&now, &rawnow);
			// Horarios impar
			if ((now.tm_hour % 2))
			{
				if (now.tm_min >= 56 && now.tm_min <= 59)
				{
					int itemId = GetFirstSlot(clientId, TICKET_ITEMID);
					if (itemId == -1)
					{
						SendClientMessage(clientId, "Necessario ter a Entrada do Calabouao (Zumbi) para se registrar.");

						return true;
					}

					INT32 leaderId = pMob[clientId].Leader;
					if(leaderId != 0) 
					{
						SendClientMessage(clientId, "Disponavel apenas para o lader do grupo");

						return true;
					}

					INT32 total = 1;
					for(INT32 i = 0; i < 12; i++ )
					{
						if(pMob[clientId].PartyList[i] > 0 && pMob[clientId].PartyList[i] < MAX_PLAYER)
							total ++;
					}

					if(total < 6) 
					{
						SendClientMessage(clientId, "Manimo de 6 pessoas no grupo.");

						return true;
					}
					
					for (INT32 i = 0; i < MAX_PLAYER; i++)
					{
						if (sServer.Zombie.Registered[i] == clientId)
						{
							SendClientMessage(clientId, "Voca ja se registrou.");

							return true;
						}
					}
					
					for(INT32 i = 0; i < 13; i++ )
					{
						INT32 memberId = clientId;
						if(i != 12)
							memberId = pMob[clientId].PartyList[i];

						if(memberId <= 0 || memberId >= MAX_PLAYER)
							continue;
						
						for(INT32 t = 0; t < MAX_PLAYER;t ++)
						{
							if(sServer.Zombie.Registered[t] == 0)
							{
								sServer.Zombie.Registered[t] = memberId;

								break;
							}
						}

						Log(memberId, LOG_INGAME, "Registrado no Calabouao Zumbi - Grupo de %s", pMob[clientId].Mobs.Player.Name);
						Log(clientId, LOG_INGAME, "Registrou no grupo: %s", pMob[clientId].Mobs.Player.Name);
					}

					SendClientMessage(clientId, "Registrado com sucesso!");
					Log(clientId, LOG_INGAME, "Se registrou no calabouao zumbi.");

					Log(SERVER_SIDE, LOG_INGAME, "%s registrou o grupo para o Calabouao Zumbi", pMob[clientId].Mobs.Player.Name);

					AmountMinus(&pMob[clientId].Mobs.Player.Inventory[itemId]);

					SendItem(clientId, SlotType::Inv, itemId, &pMob[clientId].Mobs.Player.Inventory[itemId]);
					return true;
				}				
			}
			
			SendClientMessage(clientId, "Somente nos horarios impares nos minutos 56 a 59.");
		}
#pragma endregion
 
#pragma region YUGI
		else if (npcType == 62)
		{
			std::vector<int> items;

			auto func = [&](int searched) {
				return std::find_if(items.begin(), items.end(), [&](int slotId) {
					auto itemId = pMob[clientId].Mobs.Player.Inventory[slotId].Index;

					return itemId == searched;
				}) != std::end(items);
			};

			std::array<int, 3> scrolls = { GetFirstSlot(clientId, 4600), GetFirstSlot(clientId, 4602), GetFirstSlot(clientId, 4604) };

			auto total = std::count_if(std::begin(scrolls), std::end(scrolls), [](int slot) {
				return slot != -1;
			});

			if (total == scrolls.size())
			{
				SendClientMessage(clientId, "Traga o Pergaminho do Duelo do tipo desejado");

				return true;
			}

			if (total >= 2)
			{
				SendClientMessage(clientId, "Possua apenas um tipo de Pergaminho de Duelo");

				return true;
			}

			auto slotIt = std::find_if(std::begin(scrolls), std::end(scrolls), [](int slot) {
				return slot != -1;
			});
			
			if (slotIt == std::end(scrolls))
			{
				SendClientMessage(clientId, "Traga o Pergaminho do Duelo do tipo desejado");

				return true;
			}

			int slot = *slotIt;
			STRUCT_ITEM* scrollItem = &pMob[clientId].Mobs.Player.Inventory[slot];

			int duelId = 1731;
			int daggerId = 4603;
			int powder = 413;
			int totalPowder = 10;
			if (scrollItem->Index == 4600)
			{
				duelId = 3172;
				powder = 412;
				totalPowder = 5;
				daggerId = 4599;
			}
			else if (scrollItem->Index == 4602)
			{
				duelId = 3171;
				daggerId = 4601;
			}

			bool bag1 = TimeRemaining(pMob[clientId].Mobs.Player.Inventory[60].EFV1, pMob[clientId].Mobs.Player.Inventory[60].EFV2, pMob[clientId].Mobs.Player.Inventory[60].EFV3 + 1900) > 0.0f;
			bool bag2 = TimeRemaining(pMob[clientId].Mobs.Player.Inventory[61].EFV1, pMob[clientId].Mobs.Player.Inventory[61].EFV2, pMob[clientId].Mobs.Player.Inventory[61].EFV3 + 1900) > 0.0f;
			for (int i = 0; i < 60; i++)
			{
				STRUCT_ITEM& item = pMob[clientId].Mobs.Player.Inventory[i];
				if (item.Index <= 0 || item.Index >= 6500)
					continue;

				if (i >= 30 && i <= 44 && !bag1)
					continue;
				if (i >= 45 && i <= 59 && !bag2)
					continue;

				if (item.Index == powder && GetItemAmount(&item) == totalPowder && !func(powder))
					items.push_back(i);
				else if (item.Index >= 2441 && item.Index <= 2444 && !func(2441) && !func(2442) && !func(2443) && !func(2444))
					items.push_back(i);
				else if (item.Index == daggerId && GetItemAmount(&item) == 8 && !func(daggerId))
					items.push_back(i);
				else if (item.Index == scrollItem->Index && !func(scrollItem->Index))
					items.push_back(i);
				else if (item.Index == 697 && !func(697))
					items.push_back(i);

				if (items.size() == 5)
					break;
			}

			if (items.size() != 5)
			{
				SendSay(npcId, "Itens insuficientes");

				return true;
			}

			for (auto slot : items)
			{
				STRUCT_ITEM* item = &pMob[clientId].Mobs.Player.Inventory[slot];

				Log(clientId, LOG_INGAME, "Excluado item %s %s do slot %d", ItemList[item->Index].Name, item->toString().c_str(), slot);

				*item = STRUCT_ITEM{};
				SendItem(clientId, SlotType::Inv, slot, item);
			}

			int slotId = GetFirstSlot(clientId, 0);

			memset(&pMob[clientId].Mobs.Player.Inventory[slotId], 0, sizeof STRUCT_ITEM);
			pMob[clientId].Mobs.Player.Inventory[slotId].Index = duelId;

			SendItem(clientId, SlotType::Inv, slotId, &pMob[clientId].Mobs.Player.Inventory[slotId]);
			SendSay(npcId, "Composiaao concluada com sucesso");
			Log(clientId, LOG_INGAME, "%s composta com sucesso", ItemList[duelId].Name);
		}
#pragma endregion
 
#pragma region NPC BIGCUBO
		else if (npcType == 64)
		{
			for (const auto& user : pUser)
			{
				if (user.Status != USER_PLAY || memcmp(user.MacAddress, MacAddress, 8) != 0)
					continue;

				const CMob* mob = &pMob[user.clientId];
				if (mob->Target.X >= 1292 && mob->Target.X <= 1392 && mob->Target.Y >= 1475 && mob->Target.Y <= 1525)
				{
					SendClientMessage(clientId, "Somente uma conta por computador");

					Log(clientId, LOG_INGAME, "A conta %s ja esta na area do BigCubo", user.User.Username);
					return true;
				}
			}

			if (pMob[clientId].Mobs.Player.Equip[0].EFV2 >= CELESTIAL || (pMob[clientId].Mobs.Player.Equip[0].EFV2 <= ARCH && pMob[clientId].Mobs.Player.bStatus.Level >= 20))
			{
				SendClientMessage(clientId, "Somente mortais ata navel 20");

				return true;
			}

			Teleportar(clientId, 1340, 1507);
			SendClientMessage(clientId, "Bem vindo ao BigCubo");

			Log(clientId, LOG_INGAME, "Entrou na area do BigCubo");
			return true;
		}
#pragma endregion
 
	}
	return true;
}