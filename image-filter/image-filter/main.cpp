#include "ImageFilter.h"
#include "util/ImageParser.h"
#include "util/Visualizer.h"
#include "indicator/SplitIndicator.h"
#include <iostream>

using namespace ar;
using namespace std;

int main() {

	//��������ָ�������
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
	
	//����ͼ���б�,����
	auto outputs = filter.filter(util::ImageParser::fromMetaFile("./filelist.txt"));

	//���ӻ�
	util::Visualizer::show(outputs);

	return 0;
}