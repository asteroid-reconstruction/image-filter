#pragma once
#include "Indicator.h"

namespace ar
{

	class StdIndicator :
		public Indicator
	{
	public:
		StdIndicator(const std::string& id) :Indicator(id) {}
		virtual ~StdIndicator() {}

	public:
		// Í¨¹ý Indicator ¼Ì³Ð
		virtual double calc(const cv::Mat& img) override;
	};

}

