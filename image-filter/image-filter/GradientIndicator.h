#pragma once
#include "Indicator.h"

namespace ar
{

	class GradientIndicator :
		public Indicator
	{
	public:
		GradientIndicator(const std::string& id) :Indicator(id) {}
		virtual ~GradientIndicator() { }

	public:
		// Í¨¹ý Indicator ¼Ì³Ð
		virtual double calc(const cv::Mat& img) override;

	};

}