#pragma once

#include "Main.hpp"

#include <MixFileClass.h>
#include <vector>
#include <string>

class MixLoader
{
public:
	static void LoadConfig(char** ppArgs, int nNumArgs);
	static void InitOwnResources();

	static std::vector<MixFileClass*> Mixes;
	static std::vector<std::string> MixFileList;
	static std::string ConfigPath;
};
