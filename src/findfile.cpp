#include "findfile.h"

#include <assert.h>
#include <dirent.h>
#include <sys/types.h>

#include <fstream>

namespace cirno_say
{
	FindFile::FindFile(const std::string &path, const std::string &extension, const std::string &default_value)
	{
		this->path = path;
		if(extension != "")
			this->extension = "." + extension;
		*this = default_value;
	}
	void FindFile::operator=(const std::string &value)
	{
		std::string result;
		if(value.find_first_of('/') != std::string::npos)
			result = value;
		else
			result = path + "/" + value + extension;
		if(std::ifstream (result))
		{
			this->value = value;
			filename = result;
		}
		else
			throw 0;
	}
	std::string FindFile::get_filename() const
	{
		return filename;
	}
	std::string FindFile::get_value() const
	{
		return value;
	}
	std::vector<std::string> FindFile::list() const
	{
		std::vector<std::string> result;

		DIR *dp = opendir(path.c_str());
		assert(dp);
		while(dirent *dirp = readdir(dp))
		{
			std::string i = dirp->d_name;
			int l = i.size() - extension.size();
			if(l >= 0 && i.substr(l) == extension)
				result.push_back(i.substr(0, l));
		}
		return result;
	}
}
