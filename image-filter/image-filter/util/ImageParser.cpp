#include "ImageParser.h"
#include <fstream>
#include <cassert>

std::vector<std::string> ar::util::ImageParser::fromMetaFile(const std::string& metaPath)
{
	std::vector<std::string> paths;

	std::ifstream ifs(metaPath);

	if (ifs.is_open())
	{
		char* buf = new char[1024]{};
		while (!ifs.eof())
		{
			ifs.getline(buf, 1024);
			if (strnlen_s(buf, 1024) > 0)
				paths.push_back(buf);
		}
		delete[]buf;

		ifs.close();
	}
	else
		assert(0);

	return paths;
}
