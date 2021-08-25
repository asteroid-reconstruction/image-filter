#pragma once
#include "../FilterOutput.h"

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
		private:
			explicit Visualizer(){}
			virtual ~Visualizer(){}


		public:
			/**
			* @brief	将过滤结果可视化
			* 
			* 函数生成过滤结果的JSON文本，并调用网页完成可视化
			*/
			static void show(std::vector<FilterOutput> foVec);


		};

	};
};