#pragma once
#include "../FilterOutput.h"

namespace ar {

	namespace util {

		/**
		* @brief	JSON文本转换器
		* 
		* 将各个输出类转换为JSON文本
		* 该类不能实例化，应使用静态成员函数完成转换
		* 
		*/

		class JSONParser
		{
		private:
			JSONParser(){}
			~JSONParser(){}
		public:
			static std::string parse(const FilterOutput& fo) { return fo.toJSON(); }
			static std::string parse(const std::vector<FilterOutput>& foVec);

		};
	};
};