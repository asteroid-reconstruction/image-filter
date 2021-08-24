#pragma once
#include "Indicator.h"
#include <numeric>

//asteroid reconstruction
namespace ar {

	/**
	* @brief	过滤器输出类
	*
	* 用于保存过滤器的过滤结果，同时拥有源图像信息
	*/
	struct FilterOutput{

		std::string		imagePath{};	/**< 图像文件路径，仅当使用路径指定图像时不为空*/
		cv::Mat			image{};		/**< 图像矩阵，仅当使用OpenCV Mat指定图像时不为空*/
		double			index{};		/**< 最终质量得分，由过滤条件计算得到*/
		bool			passed{};		/**< 是否通过，由过滤条件计算指定*/

		/**
		* @brief	构造函数
		*
		* @param	_imgPath	图像路径
		* @param	_img		图像
		* @param	_index		最终质量得分
		* @param	_passed		是否通过过滤
		*/
		FilterOutput(
			const std::string& _imgPath = "",
			const cv::Mat& _img = cv::Mat(),
			double _index = 0,
			bool _passed = false) :
			imagePath(_imgPath), image(_img), index(_index), passed(_passed) {}

	};

	/**
	* @brief	图像过滤器类
	* 
	* 该类使用质量指数运算类(@ref Indicator)计算一张或一组图像的
	* 质量的得分，按照筛选条件进行过滤
	* 
	*/
	class ImageFilter {

	public:
		explicit ImageFilter(){}
		virtual ~ImageFilter(){}

	public:
		/**
		* @brief	过滤条件函数类型
		* 
		* 第一个参数为输入参数，为该图像的所有质量指数
		* 第二个参数为输出参数，为该图像的综合质量得分
		* 返回值指定该图像是否通过过滤
		* 
		* 参考示例(@ref)
		*/
		using FilterCondition = bool(*)(const std::vector<double>&, double&);

	private:
		typedef std::vector<std::shared_ptr<Indicator> > IndiVecType;
		IndiVecType mIndicatorVec{};

		FilterCondition mpCondition{nullptr};

		FilterCondition mpDefaultCondition = 
			[](const std::vector<double>& indices, double& finalIndex) {
				finalIndex = std::accumulate(indices.begin(), indices.end(), 0);
				return true;
			};

	public:
		/**
		* @brief	添加指数计算器对象
		* 
		* @param[in]	indicator	计算器对象的共享指针
		* 
		* @par 示例
		*	@code
		*		imagefilter.addIndicator(std::make_shared<Indicator>();
		*	@endcode
		*/
		void addIndicator(const std::shared_ptr<Indicator> indicator) { mIndicatorVec.push_back(indicator); }
		
		/**
		* @brief	添加多个指数计算器对象
		* 
		* @param[in]	indicator	计算器对象的共享指针
		*
		* @par 示例
		*	@code
		*		imagefilter.addIndicator(std::make_shared<Indicator>();
		*	@endcode
		*/
		void addIndicator(const IndiVecType& indicators) { for (auto& ptr : indicators) mIndicatorVec.push_back(ptr); }
		
		/**
		* @brief	获取指数计算器数组引用(只读)
		*
		* @return	指数计算器数据的常引用
		*/
		const IndiVecType& indicators()const { return mIndicatorVec; }

		/**
		* @brief	获取指数计算器数组引用
		*
		* @return	指数计算器数据的引用
		*/
		IndiVecType& indicators() { return mIndicatorVec; }

		/**
		* @brief	清除指数计算器数组
		* 
		* 该函数为std::vector<>::clear()的包装
		*/
		void clearIndicators() { mIndicatorVec.clear(); }

		/**
		* @brief	设定过滤条件
		*
		* 若过滤条件为空，将使用默认过滤条件：
		* 累加所有指数计算器的评分值，所有的图像都将通过过滤
		* 
		* @param[in]	condition	条件
		* 
		* @see	FilterCondition
		*/
		void setFilterCondition(FilterCondition condition = nullptr) { mpCondition = condition; }

		/**
		* @brief	过滤图像
		*
		* 若没有调用setFilterCondition设置过滤条件，将使用默认过滤条件：
		* 累加所有指数计算器的评分值，所有的图像都将通过过滤
		*
		* @param[in]	image	图像矩阵
		* @return	过滤结果[FilterOutput](@ref FilterOutput)
		* 
		*/
		FilterOutput filter(const cv::Mat& image);

		/**
		* @brief	过滤图像
		*
		* 若没有调用setFilterCondition设置过滤条件，将使用默认过滤条件：
		* 累加所有指数计算器的评分值，所有的图像都将通过过滤
		*
		* @param[in]	images	图像矩阵数组
		* @return	过滤结果数组[FilterOutput](@ref FilterOutput)
		*
		*/
		std::vector<FilterOutput> filter(const std::vector<cv::Mat> images);

		/**
		* @brief	过滤图像
		*
		* 若没有调用setFilterCondition设置过滤条件，将使用默认过滤条件：
		* 累加所有指数计算器的评分值，所有的图像都将通过过滤
		*
		* @param[in]	imagePath	图像文件路径
		* @return	过滤结果[FilterOutput](@ref FilterOutput)
		*
		*/
		FilterOutput filter(const std::string& imagePath);

		/**
		* @brief	过滤图像
		*
		* 若没有调用setFilterCondition设置过滤条件，将使用默认过滤条件：
		* 累加所有指数计算器的评分值，所有的图像都将通过过滤
		*
		* @param[in]	imagePath	图像文件路径数组
		* @return	过滤结果数组[FilterOutput](@ref FilterOutput)
		*
		*/
		std::vector<FilterOutput> filter(const std::vector<std::string>& imagePaths);
	};
};