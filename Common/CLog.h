#ifndef CLogH
#define CLogH

#include <string>
#include <stdio.h>
#include <ctime>

#include <cstdarg>

class CLog
{
private:
	FILE* _file{ nullptr };

	std::string _folder;
	std::string _username;

	int _day{ 0 };

	void Open();
	void Close();
	void BASE_GetFirstKey(const char * source, char * dest);
public:
	CLog(std::string folder, std::string username);
	CLog(std::string folder);
	~CLog();

	void Log(const char* message, va_list arglist);
};


#endif