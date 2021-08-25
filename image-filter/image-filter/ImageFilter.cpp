#include "ImageFilter.h"
#include <sstream>
using namespace ar;

FilterOutput ImageFilter::filter(const std::string& imagePath)
{
    return filter(std::vector<std::string>({ imagePath })).front();
}

std::vector<FilterOutput> ImageFilter::filter(const std::vector<std::string>& imagePaths)
{
    std::vector< std::vector<double> > indices{};
    std::vector<FilterOutput> foVec;
    std::vector<std::string> indicatorIDs{};

    //预留内存
    indices.reserve(imagePaths.size());
    foVec.reserve(imagePaths.size());
    indicatorIDs.reserve(imagePaths.size());

    //生成质量指数计算器ID序列
    for (auto& indicator : mIndicatorVec) {
        indicatorIDs.push_back(indicator->getID());
    }

    for (std::vector<std::string>::size_type i = 0; i < imagePaths.size(); ++i) {

        indices.emplace_back();
        indices[i].reserve(mIndicatorVec.size());

        cv::Mat image = cv::imread(imagePaths[i], cv::IMREAD_GRAYSCALE);

        for (auto& indicator : mIndicatorVec) {
            indices[i].push_back(indicator->calc(image));
        }

        FilterOutput fo;

        if (mpCondition)    fo.passed = mpCondition(indices[i], fo.finalIndex);
        else                fo.passed = mpDefaultCondition(indices[i], fo.finalIndex);

        fo.imagePath = imagePaths[i];
        fo.stageIndices = indices[i];
        fo.filterID = id;
        fo.indicatorIDs = indicatorIDs;

        foVec.push_back(fo);
    }

    return foVec;
}