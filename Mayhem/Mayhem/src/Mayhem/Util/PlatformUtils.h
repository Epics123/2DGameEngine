#pragma once

#include <string>

namespace Mayhem
{
	class FileDialogs
	{
	public:
		//These return an empty string if canceled
		static std::string openFile(const char* filter);
		static std::string saveFile(const char* filter);
	};
}
