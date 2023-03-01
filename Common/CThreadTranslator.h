#ifndef CThreadTranslatorH
#define CThreadTranslatorH

#include <windows.h>

typedef void(__cdecl *_se_translator_function)(unsigned int, struct _EXCEPTION_POINTERS*);

// --------------------------------------------------------------------------
class CThreadTranslator
{
public:
	CThreadTranslator();
	~CThreadTranslator();

private:
	_se_translator_function oldFunction;
};

#endif