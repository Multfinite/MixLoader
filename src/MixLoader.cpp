#include "MixLoader.hpp"
#include <fstream>
#include <string>

std::vector<MixFileClass*> MixLoader::Mixes;
std::vector<std::string> MixLoader::MixFileList;
std::string MixLoader::ConfigPath;

inline bool IsQuote(const char ch)
{
	if (ch == '"') return true;
	else if (ch == '\'') return true;
	else return false;
}

void  MixLoader::LoadConfig(char** ppArgs, int nNumArgs)
{
	Debug::Log("[MixLoader] Config is loading.\n");

	{
		std::string cfgPath;
		bool markerDetermined = false;
		bool isSingleLine = false;
		bool isOk = false;
		bool isQuote = false;
		int markerArgIndex = -1;

		for (int i = 0; i < nNumArgs; i++)
		{
			if (isOk) break;
			const int pathIndex = (i - markerArgIndex);

			std::string_view arg = std::string_view(ppArgs[i]);
			if (arg == "--mix-list")
			{
				markerDetermined = true;
				markerArgIndex = i;
			}
			if (markerDetermined && pathIndex == 1)
			{
				isSingleLine = !IsQuote(arg[0]);
				if (isSingleLine)
				{
					cfgPath = arg;
					isOk = true;
				}
			}
			if (markerDetermined && !isSingleLine && pathIndex > 0)
			{
				for (char sym : arg)
				{					
					if (IsQuote(sym))
					{
						if (isQuote)
						{
							isQuote = false;
							isOk = true;
							break;
						}
						else isQuote = true;						
					}
					else if (isQuote) cfgPath.push_back(sym);					
				}
			}
		}
		if (cfgPath.empty()) return;
		else ConfigPath = cfgPath;
	}

	if (IsQuote(ConfigPath[0])) ConfigPath.erase(0, 1);
	if (IsQuote(ConfigPath[ConfigPath.length() - 1])) ConfigPath.pop_back();
	Debug::Log(("[MixLoader] Config: " + ConfigPath + "\n").c_str());

	std::string buffer;
	if (std::fstream stream{ ConfigPath })
	{ while (stream >> buffer) { MixFileList.push_back(buffer); } }
	//constexpr auto size = sizeof(DynamicVectorClass<int>);
}

void MixLoader::InitOwnResources()
{
	std::string log = "\n[MixLoader] File list contains " + std::to_string(MixFileList.size()) + " files\n";
	Debug::Log(log.c_str());
	for (const auto maxName : MixFileList)
	{
		Debug::Log(("[MixLoader] Try to load " + maxName + "\n").c_str());
		MixFileClass* mixFile = GameCreate<MixFileClass>(maxName.c_str());
		if(mixFile != nullptr)
		{
			Mixes.push_back(mixFile);
			Debug::Log(("[MixLoader] " + std::to_string(Mixes.back()->CountFiles) + " files was loaded from " + maxName + "\n").c_str());
		}
	}
}