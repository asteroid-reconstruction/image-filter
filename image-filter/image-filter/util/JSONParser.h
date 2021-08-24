#pragma once
#include "../FilterOutput.h"

namespace ar {

	namespace util {

		/**
		* @brief	JSON�ı�ת����
		* 
		* �����������ת��ΪJSON�ı�
		* ���಻��ʵ������Ӧʹ�þ�̬��Ա�������ת��
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