#pragma once
#include "ImageFilter.h"

namespace ar {

	/**
	* @brief	ar::util命名空间
	* 
	* 该项目的通用设施
	*/
	namespace util {

		/**
		* @brief	过滤结果可视化器
		* 
		* 为过滤结果提供可视化工具
		*/
		class Visualizer
		{
		public:
			explicit Visualizer(){}
			virtual ~Visualizer(){}

		private:

		public:
			void show(const FilterOutput& fo);
			void show(const std::vector<FilterOutput>& foVec);

			void save(const FilterOutput& fo);
			void save(const std::vector<FilterOutput>& foVec);

		private:
			cv::Mat _mosaic(
				const std::vector<FilterOutput>& foVec,
				std::vector<FilterOutput>::size_type from,
				std::vector<FilterOutput>::size_type count,
				cv::Size frameSize);
		};

	};
};