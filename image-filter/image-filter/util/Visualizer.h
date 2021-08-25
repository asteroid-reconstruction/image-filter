#pragma once
#include "../FilterOutput.h"

namespace ar {

	/**
	* @brief	ar::util�����ռ�
	* 
	* ����Ŀ��ͨ����ʩ
	*/
	namespace util {

		/**
		* @brief	���˽�����ӻ���
		* 
		* Ϊ���˽���ṩ���ӻ�����
		*/
		class Visualizer
		{
		private:
			explicit Visualizer(){}
			virtual ~Visualizer(){}


		public:
			/**
			* @brief	�����˽�����ӻ�
			* 
			* �������ɹ��˽����JSON�ı�����������ҳ��ɿ��ӻ�
			*/
			static void show(std::vector<FilterOutput> foVec);


		};

	};
};