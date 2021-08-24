#include "Visualizer.h"
#include "JSONParser.h"
#include <Windows.h>
#include <fstream>
#include <direct.h>

void ar::util::Visualizer::show(std::vector<FilterOutput> foVec)
{
	//获取工作目录
	char* cwd = new char[256]{};
	cwd = getcwd(cwd, 256);
	std::string outPath(cwd);
	assert(cwd);
	delete[] cwd;

	outPath += "util/visualizer-tool/filteroutput/result.json";

	std::ofstream ofs(outPath);

	if (ofs.is_open()) {
		ofs << JSONParser::parse(foVec);
		ofs.close();
	}
	else
		assert(0);

	//@todo
	system("");
}
