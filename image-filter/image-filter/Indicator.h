#pragma once
#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>

/**
* @brief	Asteroid Reconstruction 命名空间
* 
* 该库的所有类均在此命名空间定义
*/

namespace ar {

	/**
	* @brief 质量评价指数计算虚基类
	* 
	* 子类提供一种图像质量评价方法，
	* 对每一张图像进行运算并给出质量评分。
	*/

	class Indicator{

	public:
		explicit Indicator(){}
		virtual ~Indicator(){}

	public:

		/**
		* @brief	质量评价指数计算函数
		* 
		* 由子类实现该函数进行评价指数计算，返回评分
		* 
		* @param[in]	img		图像
		* @return		评分
		*/
		virtual double calc(const cv::Mat& img) = 0;


		/**
		* @brief	质量评价指数计算函数
		*
		* 读入图像文件到内存中，调用[calc](@ref virtual double calc(const cv::Mat& img) = 0)完成计算
		*
		* @param[in]	imgPath		图像文件路径
		* @return		评分
		*/
		double calc(const std::string& imgPath);

		/**
		* @brief	定义函数对象调用运算符
		*/
		double operator()(const cv::Mat& img) { return calc(img); }

		/**
		* @brief	定义函数对象调用运算符
		*/
		double operator()(const std::string& imgPath) { return calc(imgPath); }
	};

};