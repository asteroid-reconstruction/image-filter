#pragma once
#include <vector>
#include <string>

namespace ar {

	namespace util {
		
		/**
		* @brief	Ӱ���ļ�����
		* 
		* �ø���ľ�̬��Ա���������������ļ�ת��Ϊ·������
		* ���಻�ܱ�ʵ����
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
