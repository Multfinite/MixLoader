#include "Main.hpp"
#include "MixLoader.hpp"

#include <Helpers/Macro.h>

using namespace std;

//DllMain
bool __stdcall DllMain(HANDLE hInstance, DWORD dwReason, LPVOID v)
{
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		{
			//Debug::Log("MixLoader attach\n");
		}
		break;
	case DLL_PROCESS_DETACH:
		{
			//Debug::Log("MixLoader detach\n");
		}
		break;
	}

	return true;
}

// DEBUG
void(_cdecl* Debug::Log)(const char* pFormat, ...) = (void(__cdecl *)(const char *, ...)) 0x4068E0;

DEFINE_HOOK(0x5301BA, Load_Bootstrap_Begin, 5)
{
	MixLoader::InitOwnResources();
	return 0;
}

DEFINE_HOOK(0x52F639, _YR_CmdLineParse, 5)
{
	GET(char**, ppArgs, ESI);
	GET(int, nNumArgs, EDI);
	MixLoader::LoadConfig(ppArgs, nNumArgs);
	return 0;
}