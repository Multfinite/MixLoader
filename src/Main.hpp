#pragma once
#define SYR_VER 2
#include <Syringe.h>
//#include <apiquery2.h>

struct Debug
{
	static void(_cdecl* Log)(const char* pFormat, ...);
};