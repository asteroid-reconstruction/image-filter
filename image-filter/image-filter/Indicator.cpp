#include "Indicator.h"

double ar::Indicator::calc(const std::string& imgPath)
{
    cv::Mat img = cv::imread(imgPath,cv::IMREAD_GRAYSCALE);
    return calc(img);
}
