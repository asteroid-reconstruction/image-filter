#include "SplitIndicator.h"
#include <opencv2/imgproc.hpp>
#include <iostream>

double ar::SplitIndicator::calc(const cv::Mat& img)
{
    cv::Mat binarizedImg;

    //��ֵ��
    cv::threshold(img, binarizedImg, threshold, 255, cv::THRESH_OTSU | cv::THRESH_BINARY);

    //ͳ��������
    int validPixCount = 0, totalPixCount = binarizedImg.rows * binarizedImg.cols;
    const uchar* pData = binarizedImg.data;

    for (int i = 0; i < totalPixCount; ++i) {
        if (*(pData++) == 255)
            ++validPixCount;
    }

    return static_cast<double>(validPixCount) / totalPixCount;
}
