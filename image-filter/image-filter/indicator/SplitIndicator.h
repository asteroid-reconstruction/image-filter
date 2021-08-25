#pragma once
#include "../Indicator.h"

namespace ar {

    class SplitIndicator :
        public Indicator
    {
    public:
        explicit SplitIndicator(const std::string& id, int threshold = 127) :Indicator(id) {}
        virtual ~SplitIndicator() {}

    private:
        int threshold = 127;

    public:
        // Í¨¹ý Indicator ¼Ì³Ð
        virtual double calc(const cv::Mat& img) override;

    public:
        void setThreshold(int thres) { threshold = thres; }
        int getThreshold()const { return threshold; }
    };

};