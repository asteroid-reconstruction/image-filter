#pragma once
#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>

/**
* @brief	Asteroid Reconstruction �����ռ�
* 
* �ÿ����������ڴ������ռ䶨��
*/

namespace ar {

	/**
	* @brief ��������ָ�����������
	* 
	* �����ṩһ��ͼ���������۷�����
	* ��ÿһ��ͼ��������㲢�����������֡�
	*/

	class Indicator{

	public:
		explicit Indicator(){}
		virtual ~Indicator(){}

	public:

		/**
		* @brief	��������ָ�����㺯��
		* 
		* ������ʵ�ָú�����������ָ�����㣬��������
		* 
		* @param[in]	img		ͼ��
		* @return		����
		*/
		virtual double calc(const cv::Mat& img) = 0;


		/**
		* @brief	��������ָ�����㺯��
		*
		* ����ͼ���ļ����ڴ��У�����[calc](@ref virtual double calc(const cv::Mat& img) = 0)��ɼ���
		*
		* @param[in]	imgPath		ͼ���ļ�·��
		* @return		����
		*/
		double calc(const std::string& imgPath);

		/**
		* @brief	���庯��������������
		*/
		double operator()(const cv::Mat& img) { return calc(img); }

		/**
		* @brief	���庯��������������
		*/
		double operator()(const std::string& imgPath) { return calc(imgPath); }
	};

};