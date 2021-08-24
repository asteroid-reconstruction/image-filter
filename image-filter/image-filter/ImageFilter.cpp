#include "ImageFilter.h"
using namespace ar;

FilterOutput ImageFilter::filter(const cv::Mat& image)
{
    return filter(std::vector<cv::Mat>({ image })).front();
}

std::vector<FilterOutput> ImageFilter::filter(const std::vector<cv::Mat> images)
{
    std::vector< std::vector<double> > indices{};
    std::vector<FilterOutput> foVec;

    indices.reserve(images.size());
    foVec.reserve(images.size());

    for (std::vector<const cv::Mat>::size_type i = 0; i < images.size(); ++i) {
        indices[i].reserve(mIndicatorVec.size());

        for (auto& indicator : mIndicatorVec) {
            indices[i].push_back(indicator->calc(images[i]));
        }

        foVec.emplace_back("", images);

        if (mpCondition)    foVec.back().passed = mpCondition(indices[i], foVec.back().index);
        else                foVec.back().passed = mpDefaultCondition(indices[i], foVec.back().index);
    }

    return foVec;
}

FilterOutput ImageFilter::filter(const std::string& imagePath)
{
    return filter(std::vector<std::string>({ imagePath })).front();
}

std::vector<FilterOutput> ImageFilter::filter(const std::vector<std::string>& imagePaths)
{
    std::vector< std::vector<double> > indices{};
    std::vector<FilterOutput> foVec;

    indices.reserve(imagePaths.size());
    foVec.reserve(imagePaths.size());

    for (std::vector<const cv::Mat>::size_type i = 0; i < imagePaths.size(); ++i) {
        indices[i].reserve(mIndicatorVec.size());
        cv::Mat image = cv::imread(imagePaths[i], cv::IMREAD_GRAYSCALE);

        for (auto& indicator : mIndicatorVec) {
            indices[i].push_back(indicator->calc(image));
        }

        foVec.emplace_back(imagePaths[i]);

        if (mpCondition)    foVec.back().passed = mpCondition(indices[i], foVec.back().index);
        else                foVec.back().passed = mpDefaultCondition(indices[i], foVec.back().index);
    }

    return foVec;
}