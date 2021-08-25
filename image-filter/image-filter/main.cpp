#include "ImageFilter.h"
#include "util/ImageParser.h"
#include "util/Visualizer.h"
#include "indicator/SplitIndicator.h"
#include <iostream>

using namespace ar;
using namespace std;

int main() {

	//载入质量指标计算器
	vector<shared_ptr<Indicator> > indiVec;

	indiVec.push_back(make_shared<SplitIndicator>("split-indicator: thres = 20", 20));
	indiVec.push_back(make_shared<SplitIndicator>("split-indicator: thres = 50", 50));
	indiVec.push_back(make_shared<SplitIndicator>("split-indicator: thres = 80", 80));
	indiVec.push_back(make_shared<SplitIndicator>("split-indicator: thres = 110", 110));

	ImageFilter filter("Split Filter v1.0");

	filter.addIndicator(indiVec);

	filter.setFilterCondition(
		[](const vector<double>& indices, double& finalIndex) {
			finalIndex = indices[0] * 0.2 + indices[1] * 0.2 + indices[2] * 0.2 + indices[3] * 0.4;
			cout << "Final: " << finalIndex << '\n';
			if (finalIndex < 0.05)
				return false;
			return true;
		});
	
	//读入图像列表,过滤
	auto outputs = filter.filter(util::ImageParser::fromMetaFile("./filelist.txt"));

	//可视化
	util::Visualizer::show(outputs);

	return 0;
}