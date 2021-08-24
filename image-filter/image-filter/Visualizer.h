#pragma once
#include "ImageFilter.h"

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