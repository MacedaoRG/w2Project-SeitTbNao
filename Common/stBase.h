#ifndef _INCLUDE_STRUCTS_H_
#define _INCLUDE_STRUCTS_H_
#include <Windows.h>

#include <iostream>
#include <array>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>

struct STRUCT_ITEM
{
	WORD Index;
	struct
	{
		BYTE Index;
		BYTE Value;
	} Effect[3];

	std::string toString() const
	{
		std::stringstream str;
		str << "[" << Index << "]" << " [";

		for (int i = 0; i < 3; i++)
		{
			str << std::to_string(Effect[i].Index) << " " << std::to_string(Effect[i].Value);

			if (i != 2)
				str << " ";
		}
		str << "]";

		return str.str();
	}

	bool hasAdd(BYTE add, BYTE& value) const 
	{
		for (int i = 0; i < 3; i++) 
		{
			if (Effect[i].Index == add)
			{
				value = Effect[i].Value;

				return true;
			}
		}

		return false;
	}
};

#define EF1 Effect[0].Index
#define EFV1 Effect[0].Value
#define EF2 Effect[1].Index
#define EFV2 Effect[1].Value
#define EF3 Effect[2].Index
#define EFV3 Effect[2].Value

struct STRUCT_POSITION 
{
	WORD X, Y;

	friend std::ostream& operator<<(std::ostream& os, const STRUCT_POSITION& pos)
	{
		os << pos.X << "x" << pos.Y << "y";

		return os;
	}

	bool operator>=(const STRUCT_POSITION& rhs)
	{
		return X >= rhs.X && Y >= rhs.Y;
	}

	bool operator<=(const STRUCT_POSITION& rhs)
	{
		return X <= rhs.X && Y <= rhs.Y;
	}

	bool operator>(const STRUCT_POSITION& rhs)
	{
		return X > rhs.X && Y > rhs.Y;
	}

	bool operator<(const STRUCT_POSITION& rhs)
	{
		return X < rhs.X && Y < rhs.Y;
	}
};

struct STRUCT_AFFECT
{
	BYTE Index;
	BYTE Master;

	WORD Value;
	DWORD Time;
} ;

struct STRUCT_STATUS
{
	DWORD Level;
	DWORD Defense;
	DWORD Attack;

	union
	{
		struct  {
			BYTE Merchant : 4;
			BYTE Direction : 4;
		};
		BYTE Value;
	} Merchant;

	union {
		struct {
			BYTE Speed : 4;
			BYTE ChaosRate : 4;
		};
		BYTE Value;
	} Move;

	INT32 maxHP, maxMP;
	INT32 curHP, curMP;

	WORD STR, INT;
	WORD DEX, CON;

	WORD Mastery[4];
};


enum eClass
{
	Mortal = 1,
	Arch,
	Celestial,
	SubCelestial,
	UnknownClass = -1
};

struct STRUCT_MOB
{
	char Name[16]; // 0 - 15
	char CapeInfo; // 16 

	union
	{
		struct
		{
			BYTE Merchant : 6;
			BYTE CityID :  2;
		};
		BYTE Value;
	} Info; // 17

	WORD GuildIndex; // 18 19
	BYTE ClassInfo; // 20

	union
	{
		struct
		{
			BYTE SlowMov : 1;
			BYTE DrainHP : 1;
			BYTE VisionDrop : 1;
			BYTE Evasion : 1;
			BYTE Snoop : 1;
			BYTE SpeedMov : 1;
			BYTE SkillDelay : 1;
			BYTE Resist : 1;
		};

		BYTE Value;
	} AffectInfo; // 21

	union 
	{
		struct
		{
			WORD Mystical_GetQuest : 1; // 1
			WORD Mystical_CanGetAmuleto : 1; // 2
			WORD Mystical_GetAmuleto : 1; // 4
			WORD Reset50 : 1; // 8
			WORD Reset100 : 1; // 16
			WORD MestreHab : 1; // primeiro reset free? 32
			WORD Treinadores : 4; // 64 128 256 512
			WORD All : 6;
		};

		WORD Value;
	} QuestInfo;

	int Gold; // 24 - 27
	long long Exp; // 32 - 39

	STRUCT_POSITION Last; // 40 - 43
	STRUCT_STATUS bStatus; // 44 - 91
	STRUCT_STATUS Status; // 92 - 139

	STRUCT_ITEM Equip[16]; // 140 - 267
	STRUCT_ITEM Inventory[64]; // 268 - 779

	unsigned int Learn[2]; // 780 - 783
	WORD StatusPoint; // 788 - 789
	WORD MasterPoint; // 790 - 791
	WORD SkillPoint; //792 - 793

	BYTE Critical; // 794
	BYTE SaveMana; // 795

	unsigned char SkillBar1[4]; // 796 - 799
	char GuildMemberType; // 800

	BYTE MagicIncrement; // 801
	BYTE RegenHP; // 802 
	BYTE RegenMP; // 803

	struct
	{
		BYTE Fogo;
		BYTE Gelo;
		BYTE Sagrado;
		BYTE Trovao;
	} Resist; // 804 - 807

	eClass GetEvolution() const
	{
		int value = Equip[0].EFV2;
		if (value <= 0 || value >= 5)
			return eClass::UnknownClass;

		return (eClass)value;
	}
};

union UNION_QUESTINFO
{
	struct
	{
		// Level feito o celestial
		INT64 Level355 : 1;
		INT64 Level370 : 1;
		INT64 Level380 : 1;
		INT64 Level398 : 1;
		INT64 Level399 : 1;


		// Cristais Arch
		INT64 Elime : 1;
		INT64 Sylphed : 1;
		INT64 Thelion : 1;
		INT64 Noas : 1;

		// Arcana
		INT64 Arcana : 1;

		// Adicionais SubCele
		INT64 Add120 : 1;
		INT64 Add151 : 1;
		INT64 Add180 : 1;
		INT64 Add199 : 1;

		// Resets Subcelestial
		INT64 Reset_1 : 1;
		INT64 Reset_2 : 1;
		INT64 Reset_3 : 1;
		INT64 Reset_4 : 1;

		// Treinadores
		INT64 Treinador_1 : 1;
		INT64 Treinador_2 : 1;
		INT64 Treinador_3 : 1;

		INT64 Unicornio : 1;
		INT64 MolarGargula : 1;

		INT64 Reset_50 : 1;
		INT64 Pilula : 1;

		INT64 Conj_Iniciante : 1;

		INT64 BemVindo : 1;
		INT64 Quest_1_de_5 : 1;
		INT64 Quest_2_de_5 : 1;
		INT64 Quest_3_de_5 : 1;
		INT64 Quest_4_de_5 : 1;
		INT64 Quest_5_de_5 : 1;

		INT64 LvBlocked : 1;
		INT64 BalanceQuest : 1;
		INT64 GodBless : 1;

		INT64 Unlock354 : 1;
		INT64 Unlock369 : 1;
		INT64 Unlock39  : 1;
		INT64 Unlock89  : 1;

		INT64 QuestRune_1 : 1;
		INT64 QuestRune_2 : 1;
		INT64 QuestRune_3 : 1;

		INT64 Unlock200 : 1;
		INT64 Unlock210 : 1;
		INT64 Unlock220 : 1;
		INT64 Unlock230 : 1;
	};
	INT64 Value;
};

struct STRUCT_ITEMDATE
{
	BYTE Dia;
	BYTE Mes;
	WORD Ano;

	BYTE Hora;
	BYTE Minuto;
	BYTE Segundo;

	time_t GetTMStruct() const
	{
		struct std::tm b = { Segundo, Minuto, Hora, Dia, Mes - 1, Ano - 1900 };

		return std::mktime(&b);
	}

	auto GetDiffFromNow() const
	{
		time_t rawnow = time(NULL);
		struct tm now; localtime_s(&now, &rawnow);

		auto now_time_t = std::mktime(&now);
		auto diffTime = std::difftime(GetTMStruct(), now_time_t);
		if (diffTime <= 0.0)
			diffTime = -1.0;

		return diffTime;
	}

	std::string toString() const
	{
		std::stringstream str;
		str << Dia << "/" << Mes << "/" << Ano << " " << Hora << ":" << Minuto << ":" << Segundo;

		return str.str();
	}
};

struct STRUCT_SUBINFO
{
	INT32 Status;

	STRUCT_STATUS SubStatus;
	STRUCT_ITEM Equip[2];

	unsigned char SkillBar[20];

	INT64 Exp;

	unsigned int Learn;
	unsigned int SecLearn;
	STRUCT_AFFECT Affect[32];

	UNION_QUESTINFO Info;
	
	UINT8 Soul;
}; 

struct STRUCT_CHARINFO
{
	STRUCT_MOB Player; // 0 - 807

	STRUCT_AFFECT Affects[32]; // 808 - 1063
	UNION_QUESTINFO Info; // 1064 - 1071

	UINT32 HallEnter; // Entradas para Kefra // 1072 - 1075
	UINT32 Fame; // Fama do personagem // 1076 - 1079

	INT8 PesaEnter; // Entrada Pesadelo // 1080

	UINT8 Citizen; // Cidadania // 1081
	UINT8 Soul; // Configuração da Soul // 1082

	long long Hold;
	unsigned char SkillBar[16];

	UINT32 MagicIncrement;
	INT32 MortalSlot;

	STRUCT_ITEMDATE Divina;
	STRUCT_ITEMDATE Sephira;
	STRUCT_ITEMDATE Saude;
	STRUCT_ITEMDATE Escritura;
	STRUCT_ITEMDATE Revigorante;

	STRUCT_SUBINFO Sub;
	
	// & 0x01 = Buff 18 -> 0x0040B0BA -> controle de mana
	// & 0x02 = Imunidade (skill HT)
	// & 0x04 = SlowMov
	// & 0x08 = poção ataque + samaritano 
	// & 0x10 = Buff 36 -> 0x0040BB0C -> veneno
	// & 0x20 = Buff 26 -> 0x0040B346 -> evasao
	// & 0x40 = Buff 28 -> 0x0040B393 -> invisibilidade
	// & 0x80 = SpeedMov;
	INT32 AffectInfo; // 1FDF34C (byte 1708)
	//DWORD Cash;

	STRUCT_POSITION Nightmare[3];
 

	STRUCT_ITEMDATE LastGuildKickOut;

	int RvRPoints;

	int GetTotalResets() const;
} ;

struct STRUCT_ACCOUNT
{
	char Username[16]; // Nome de usuario
	char Password[36]; // Senha da conta

	WORD Cash;

	WORD BanType;
	STRUCT_ITEMDATE Ban;
	char SecondPass[16]; // Segunda senha

	WORD AccessLevel;

	int Year;
	int YearDay;

	struct
	{
		DWORD Coin;

		STRUCT_ITEM Item[128];
	} Storage; // Banco do usuario

	STRUCT_CHARINFO Mob[4];
 
	struct
	{
		char Pass[16] = { 0 };
		WORD Blocked;
	} Block;

	// Estas são as insignias da conta e cada personagem tem uma estrutura própria
	union Insignias
	{
		struct
		{
			INT64 FirstDay : 1; // primeiro dia de servidor ficou online
			INT64 Novice   : 1;
			INT64 All	   : 62;
		};

		INT64 Value;
	} Insignias;	

	char TempKey[52] = { 0 };

	INT16 CharSlot;
	STRUCT_POSITION Position;
  
	struct
	{
		INT32 Day;
		INT32 Total;
	} Water;

	STRUCT_ITEMDATE Divina;
	STRUCT_ITEMDATE Sephira;

 

	bool AlreadyReseted;
}; 

struct stCharInfo_Old
{
	STRUCT_MOB Player; // 0 - 807

	STRUCT_AFFECT Affects[32]; // 808 - 1063
	UNION_QUESTINFO Info; // 1064 - 1071

	UINT32 HallEnter; // Entradas para Kefra // 1072 - 1075
	UINT32 Fame; // Fama do personagem // 1076 - 1079

	INT8 PesaEnter; // Entrada Pesadelo // 1080

	UINT8 Citizen; // Cidadania // 1081
	UINT8 Soul; // Configuração da Soul // 1082

	INT64 Hold;
	char SkillBar[16];

	UINT32 MagicIncrement;
	INT32 MortalSlot;

	STRUCT_ITEMDATE Divina;
	STRUCT_ITEMDATE Sephira;
	STRUCT_ITEMDATE Saude;
	STRUCT_ITEMDATE Escritura;
	STRUCT_ITEMDATE Revigorante;

	STRUCT_SUBINFO Sub;
	
	// & 0x01 = Buff 18 -> 0x0040B0BA -> controle de mana
	// & 0x02 = Imunidade (skill HT)
	// & 0x04 = SlowMov
	// & 0x08 = poção ataque + samaritano 
	// & 0x10 = Buff 36 -> 0x0040BB0C -> veneno
	// & 0x20 = Buff 26 -> 0x0040B346 -> evasao
	// & 0x40 = Buff 28 -> 0x0040B393 -> invisibilidade
	// & 0x80 = SpeedMov;
	INT32 AffectInfo; // 1FDF34C (byte 1708)
	//DWORD Cash;

	STRUCT_POSITION Nightmare[3];

	struct
	{
		struct
		{
			INT32 Mob;
			INT32 Death;

			INT32 Boss;
		} PvM;

		struct
		{
			INT32 Kill;
			INT32 Death;
		} PvP;

		INT32 Aux[10];
	} Counters;
	
	// Apenas variaveis temporarias para evitar adicionar depois ^^ enfim! 
	// vão ser usados futuramente simm
	union 
	{
		struct
		{
			INT64 FirstDay : 1; // primeiro dia de servidor ficou online
			INT64 All	   : 63;
		};

		INT64 Value;
	} Insignias_01;

	union
	{
		struct
		{
			INT64 All	   : 64;
		};

		INT64 Value;
	} Insignias_02;
 
	
};
 
struct STRUCT_ITEMLIST
{
    char Name[64];

    short Mesh1;
    int Mesh2;

    short Level;
    short Str;
    short Int;
    short Dex;
    short Con;

    struct
    {
        short Index;
        short Value;
    } Effect[12];

    int Price;
    short Unique;
    unsigned short Pos;
    short Extreme;
    short Grade;
};
 
struct STRUCT_SKILLDATA
{
    int Points;
    int Target;
    int Mana;
    int Delay;
    int Range;
    int InstanceType; // Affect[0].Index
    int InstanceValue; // Affect[0].Value
    int TickType; // Affect[1].Index
    int TickValue; // Affect[1].Value
    int AffectType; // Affect[2].Index
    int AffectValue; // Affect[2].Value
    int Time;
    char Act[16];
    int InstanceAttribute;
    int TickAttribute;
    int Aggressive;
    int Maxtarget;
    int PartyCheck;
    int AffectResist;
    int Passive_Check;
	int ForceDamage;
};

struct STRUCT_TELEPORT
{
	INT32 Price;
	
	STRUCT_POSITION SrcPos;
	STRUCT_POSITION DestPos;
};

struct STRUCT_GUILDINFO
{
	std::string Name;
	std::array<std::string, 3> SubGuild;

	// Reino das Guilds
	BYTE Kingdom;

	// Fame das guilds
	int Fame;

	// Cidadania da guilda
	int Citizen;

	INT32 Wins;
};

struct STRUCT_STOREDONATE
{
	UINT32 Price;
	INT32 Loop;
	INT32 Avaible;

	STRUCT_ITEM item;
};

struct STRUCT_SEALINFO
{
	INT32 Status; //B5C - 0 - 3
	INT16 Face; //B60 -  4 - 5
	INT16 Level; // B62 - 6 - 7
	INT16 STR; // B64 - 8 - 9
	INT16 INT; // B66 - 10 - 11
	INT16 DEX; // B68 - 12 - 13
	INT16 CON; // B6A - 14 - 15
	INT16 Evolution; // B6C
	INT16 CapeId; // B6E
	INT16 Unk_3; // B70
	INT16 Unk_4;
	INT16 Skills[9];
	INT16 QuestInfo; // 01 = 1 quest , 0x11 = 2 quests, 0x111 = 3 quests, 0x1111 = 4quests
};

struct STRUCT_SEALFILE
{
	STRUCT_SEALINFO Seal;
	STRUCT_CHARINFO Mob;
};

#endif