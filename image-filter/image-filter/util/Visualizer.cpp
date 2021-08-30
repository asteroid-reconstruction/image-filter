#include "Visualizer.h"
#include "JSONParser.h"
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <direct.h>

void ar::util::Visualizer::show(std::vector<FilterOutput> foVec)
{
	//��ȡ����Ŀ¼
	char* cwd = new char[256]{};
	cwd = _getcwd(cwd, 256);
	std::string outPath(cwd);
	assert(cwd);

	//CORS���ƣ�ֱ������һ��JS Object
	outPath += "\\util\\visualizer-tool\\javascript\\result.js";

	std::ofstream ofs(outPath, std::ios::out);

	if (ofs.is_open()) {
		ofs <<"var filterOutput = "<< JSONParser::parse(foVec);
		ofs.close();
	}
	else
		assert(0);

	std::string vistoolPath = cwd;
	vistoolPath += "\\util\\visualizer-tool\\index.html";

	std::cout << vistoolPath;
	std::cout << system(('\"' + vistoolPath + '\"').c_str());

	delete[] cwd;
}
