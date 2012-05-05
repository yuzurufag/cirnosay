#pragma once

#include <string>
#include <vector>

namespace cirno_say
{
	class FindFile
	{
		std::string path;
		std::string extension;
		std::string value;
		std::string filename;
		FindFile() {}
		public:
		FindFile(const std::string &path, const std::string &extension, const std::string &default_value);
		void operator=(const std::string &value);
		std::string get_filename() const;
		std::string get_value() const;
		std::vector<std::string> list() const;
	};
}
