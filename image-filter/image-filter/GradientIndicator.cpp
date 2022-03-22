#include "GradientIndicator.h"

double ar::GradientIndicator::calc(const cv::Mat& img)
{
	int pixCount = img.rows * img.cols;

	uchar* pData = img.data;

	double gradSum = 0;

	for (int i = 0; i < img.rows; ++i)
	{
		for (int j = 0; j < img.cols; ++j)
		{
			gradSum += (pData[i * img.cols + j + 1] - pData[i * img.cols + j]);
		}

	}

	return gradSum / static_cast<double>(pixCount);
}