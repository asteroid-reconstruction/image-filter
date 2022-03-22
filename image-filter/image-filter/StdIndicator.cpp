#include "StdIndicator.h"

double ar::StdIndicator::calc(const cv::Mat& img)
{
	int pixCount = img.rows * img.cols;

	uchar* pData = img.data;

	double pixSum = 0;
	double pixStd = 0;

	for (int i = 0; i < pixCount; ++i) {
		pixSum += pData[i];
	}

	double u = pixSum / static_cast<double>(pixCount);

	for (int i = 0; i < pixCount; ++i) {
		pixStd += pow((pData[i] - u), 2);
	}

	return sqrt(pixStd / static_cast<double>(pixCount)) / 255.0;
}
