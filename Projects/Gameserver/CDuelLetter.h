#ifndef CDuelLetterH
#define CDuelLetterH

#include <vector>
#include <map>
#include <tuple>
#include "CEvent.h"

class CUser;

enum class eDuelLetter_Room
{
	FirstRoom,
	SecondRoom,
	ThirdRoom,
	FourthRoom,
	BossRoom,
	InvalidRoom
};

enum class eDuelLetterType
{
	Normal,
	Mystical,
	Arcane
};

class CDuelLetter : public CEventItem
{
public:
	CDuelLetter(std::chrono::milliseconds interval)
		: CEventItem(interval)
	{
	}
	virtual bool Register(CUser&, STRUCT_ITEM*);
	virtual bool CanRegister(CUser&);
	virtual void Unregister(CUser& user)
	{
	}

protected:
	virtual void Work();

private:
	void Finish(bool outOfTime);
	eDuelLetterType GetType(STRUCT_ITEM* item) const;

	void GenerateRoom();
	void GenerateRune();

	bool CanGenerateBoss() const;
	int GetMobCountOnRoom() const;
	int GetInitialIndex() const;
	void CheckUsers();
	void LogGroup(const char* message, ...);
	eDuelLetter_Room GetNextRoom() const;
	eDuelLetter_Room _room{ 0 };

	int _timer{ 0 };
	eDuelLetterType _type;
	bool _status{ false };
	bool _haveCourageSymbol{ false };

	std::map<eDuelLetter_Room, int> _runesId;
	std::map<eDuelLetter_Room, std::vector<int>> _initRunes;

	std::vector<CUser*> _users;

	std::tuple<int, int> GetGenerIndexes() const;
};

constexpr int DuelLetter_Normal_Index = 46;
constexpr int DuelLetter_Mystical_Index = 58;
constexpr int DuelLetter_Arcane_Index = 71;
#endif
