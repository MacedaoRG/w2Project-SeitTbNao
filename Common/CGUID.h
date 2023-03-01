//---------------------------------------------------------------------------
#ifndef UOD_GuidH
#define UOD_GuidH
//---------------------------------------------------------------------------
#include <guiddef.h>
#include <string>
//---------------------------------------------------------------------------

class CGuid
{
public:

	// Create
	CGuid();
	CGuid(const CGuid&);
	CGuid(CGuid&&);
	CGuid(const GUID& src);

	// Compare
	bool operator==(const CGuid& right) const;
	bool operator!=(const CGuid& right) const;
	bool operator < (const CGuid &) const; // Para pode ser usado como chave de std::map.

	// Assign
	CGuid& operator=(const CGuid& src);
	CGuid& operator=(CGuid&& src);

	// Cast
	operator GUID() const;
	operator std::string() const;

	bool IsEmpty();

	static CGuid Empty;
	static CGuid CreateNew();

private:
	unsigned long  Data1;
	unsigned short Data2;
	unsigned short Data3;
	unsigned char  Data4[8];

};

#endif
