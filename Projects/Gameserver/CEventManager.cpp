#include "CEventManager.h"
#include "CEvent.h"
#include "CDuelLetter.h"
#include "CQuiz.h"
#include "Basedef.h"

CEventManager::CEventManager()
{
	_events[eEventType::DuelLetter] = std::make_unique<CDuelLetter>(800ms);
	_events[eEventType::Quiz] = std::make_unique<CQuiz>(800ms);
}

std::map<eEventType, std::unique_ptr<CEvent>>& CEventManager::GetEvents() 
{
	return _events;
}

CEvent* CEventManager::GetEvent(eEventType type) 
{
	auto eventIt = _events.find(type);
	if (eventIt == std::end(_events))
		return nullptr;

	return &*eventIt->second;
}

CEventItem* CEventManager::GetEventItem(eEventType type)
{
	auto eventIt = _events.find(type);
	if (eventIt == std::end(_events))
		return nullptr;

	return static_cast<CEventItem*>(&*eventIt->second);
}