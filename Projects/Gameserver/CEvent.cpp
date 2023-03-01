#include "Basedef.h"
#include "CEvent.h"
#include "CDuelLetter.h"
#include "CQuiz.h"
#include <memory>

CEvent::CEvent(std::chrono::milliseconds interval)
	: _interval(interval)
{

}

void CEvent::Fire()
{
	try
	{
		Work();
	}
	catch (std::exception& e)
	{
		Log(SERVER_SIDE, LOG_INGAME, "Exceaao ocorreu em \"Fire\". Mensagem: %s", e.what());
	}
}

void CEvent::SetLastExecution(time_point time)
{
	_lastExecution = time;
}

void CEvent::SetInterval(std::chrono::milliseconds time)
{
	_interval = time;
}

std::chrono::milliseconds CEvent::GetInterval() const
{
	return _interval;
}

time_point CEvent::GetLastExecution() const
{
	return _lastExecution;
}