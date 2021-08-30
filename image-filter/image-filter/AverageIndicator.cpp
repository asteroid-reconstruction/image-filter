#include "AverageIndicator.h"

double ar::AverageIndicator::calc(const cv::Mat& img)
{
	int pixCount = img.rows * img.cols;

	uchar* pData = img.data;

	double pixSum = 0;

	for (int i = 0; i < pixCount; ++i) {
		pixSum += pData[i];
	}

	return pixSum / static_cast<double>(pixCount) / 255.0;
}
