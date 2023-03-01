#ifndef CEventH
#define CEventH

#include <chrono>
#include <array>

using time_point = std::chrono::time_point<std::chrono::steady_clock>;
using namespace std::chrono_literals;

class CUser;
struct STRUCT_ITEM;

class CEvent
{
protected:
	std::chrono::milliseconds _interval;
	time_point _lastExecution;
	
	virtual void Work() = 0;

	CEvent(std::chrono::milliseconds interval);
public:
	void Fire();

	std::chrono::milliseconds GetInterval() const;
	void SetInterval(std::chrono::milliseconds interval);
	time_point GetLastExecution() const;
	void SetLastExecution(time_point time);
};

class CEventItem : public CEvent
{
public:
	CEventItem(std::chrono::milliseconds interval)
		: CEvent(interval)
	{

	}
	virtual bool CanRegister(CUser& user) = 0;
	virtual void Unregister(CUser& user) = 0;
	virtual bool Register(CUser& user, STRUCT_ITEM* item) = 0;
};

#endif