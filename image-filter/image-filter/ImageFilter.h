#pragma once
#include "Indicator.h"
#include "FilterOutput.h"
#include <numeric>

//asteroid reconstruction
namespace ar {

	/**
	* @brief	图像过滤器类
	* 
	* 该类使用质量指数运算类(@ref Indicator)计算一张或一组图像的
	* 质量的得分，按照筛选条件进行过滤
	* 
	*/
	class ImageFilter {

	public:
		explicit ImageFilter(const std::string& _id):id(_id){}
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
		//质量评价指数计算器序列
		IndiVecType mIndicatorVec{};

		//过滤条件
		FilterCondition mpCondition{nullptr};

		//默认过滤条件
		FilterCondition mpDefaultCondition = 
			[](const std::vector<double>& indices, double& finalIndex) {
				finalIndex = std::accumulate(indices.begin(), indices.end(), 0);
				return true;
			};

		//过滤器ID
		std::string id = "undefined-filter";

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

		/**
		* @brief	获取过滤器ID
		* @return	过滤器ID
		*/
		std::string getID()const { return id; }

		/**
		* @brief	设置过滤器ID
		* @param	_id		过滤器ID
		*/
		void setID(const std::string& _id) { id = _id; }
	};
};