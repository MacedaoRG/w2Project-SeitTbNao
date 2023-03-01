#include "CThreadTranslator.h"
#include <string>
#include <sstream>

// --------------------------------------------------------------------------
void trans_func(unsigned int u, EXCEPTION_POINTERS* pExp)
{
	std::stringstream msg;
	msg << "Structured Exception." << std::endl;
	msg << "Exception Address: 0x" << std::hex << reinterpret_cast<INT_PTR>(pExp->ExceptionRecord->ExceptionAddress) << std::endl;
	msg << "Exception Code: 0x" << std::hex << pExp->ExceptionRecord->ExceptionCode << std::endl;
	msg << "Exception Flags: 0x" << std::hex << pExp->ExceptionRecord->ExceptionFlags << std::endl;

	for (DWORD i = 0; i < pExp->ExceptionRecord->NumberParameters; i++)
	{
		msg << "Exception parameter " << i << ": " << std::hex << pExp->ExceptionRecord->ExceptionInformation[i] << std::endl;
	}

	HANDLE hThread = GetCurrentThread();
	DWORD threadId = GetThreadId(hThread);
	msg << "Thread id: " << threadId << std::endl;

	throw std::runtime_error(msg.str().c_str());
}

// --------------------------------------------------------------------------
CThreadTranslator::CThreadTranslator()
{
	oldFunction = _set_se_translator(trans_func);
}

// --------------------------------------------------------------------------
CThreadTranslator::~CThreadTranslator()
{
	_set_se_translator(oldFunction);
}