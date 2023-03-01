#ifndef CEventManagerH
#define CEventManagerH

#include <map>
#include <memory>
#include "CEvent.h"
#include "Singleton.h"

enum class eEventType
{
	DuelLetter = 0,
	Quiz = 1,
};

class CEventManager
{
public:
	CEventManager();

	CEventManager(const CEventManager&) = delete;
	CEventManager& operator=(const CEventManager&) = delete;
	CEventManager(CEventManager &&) = delete;
	CEventManager& operator=(CEventManager&&) = delete;

	CEvent* GetEvent(eEventType);
	CEventItem* GetEventItem(eEventType);
	std::map<eEventType, std::unique_ptr<CEvent>>& GetEvents();

	static CEventManager& GetInstance()
	{
		static CEventManager event;

		return event;
	}

private:
	std::map<eEventType, std::unique_ptr<CEvent>> _events;
};

#endif