#include "ImageFilter.h"
#include "util/ImageParser.h"
#include "util/Visualizer.h"
#include "indicator/SplitIndicator.h"
#include "AverageIndicator.h"
#include "StdIndicator.h"
#include "GradientIndicator.h"
#include <iostream>

using namespace ar;
using namespace std;

int main() {

	//��������ָ�������
	vector<shared_ptr<Indicator> > indiVec;

	indiVec.push_back(make_shared<AverageIndicator>("average-indicator"));
	indiVec.push_back(make_shared<SplitIndicator>("split-indicator", 50));
	indiVec.push_back(make_shared<StdIndicator>("std-indicator"));
	indiVec.push_back(make_shared<GradientIndicator>("gradient-indicator"));



	ImageFilter filter("Mix Filter v1.0");

	filter.addIndicator(indiVec);

	filter.setFilterCondition(
		[](const vector<double>& indices, double& finalIndex) {
			finalIndex = indices[0] * 0.35 + indices[1] * 0.15 + indices[2] * 0.4 + indices[3] * 0.1;
			cout << "Final: " << finalIndex << '\n';
			if (finalIndex < 0.05 || finalIndex > 0.115 || indices[1] < 0.001)
				return false;
			return true;
		});
	
	//����ͼ���б�,����
	auto outputs = filter.filter(util::ImageParser::fromMetaFile("./filelist.txt"));

	//���ӻ�
	util::Visualizer::show(outputs);

	return 0;
}