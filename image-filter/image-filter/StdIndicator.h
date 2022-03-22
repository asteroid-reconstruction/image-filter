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
		// ͨ�� Indicator �̳�
		virtual double calc(const cv::Mat& img) override;
	};

}

