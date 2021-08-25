#pragma once
#include <vector>
#include <string>

namespace ar {

	namespace util {
		
		/**
		* @brief	影像文件管理
		* 
		* 用该类的静态成员函数将数据描述文件转换为路径序列
		* 该类不能被实例化
		*/
		class ImageParser
		{
		private:
			ImageParser() {}
			~ImageParser() {}

		public:
			static std::vector<std::string> fromMetaFile(const std::string& metaPath);
		};

	};
};
