#pragma once
#include "Indicator.h"

namespace ar {

    class AverageIndicator :
        public Indicator
    {

    public:
        AverageIndicator(const std::string& id) :Indicator(id) {}
        virtual ~AverageIndicator() { }

    public:
        // ͨ�� Indicator �̳�
        virtual double calc(const cv::Mat& img) override;

    };

};
