#pragma once
#include "Indicator.h"
#include "FilterOutput.h"
#include <numeric>

//asteroid reconstruction
namespace ar {

	/**
	* @brief	ͼ���������
	* 
	* ����ʹ������ָ��������(@ref Indicator)����һ�Ż�һ��ͼ���
	* �����ĵ÷֣�����ɸѡ�������й���
	* 
	*/
	class ImageFilter {

	public:
		explicit ImageFilter(const std::string& _id):id(_id){}
		virtual ~ImageFilter(){}

	public:
		/**
		* @brief	����������������
		* 
		* ��һ������Ϊ���������Ϊ��ͼ�����������ָ��
		* �ڶ�������Ϊ���������Ϊ��ͼ����ۺ������÷�
		* ����ֵָ����ͼ���Ƿ�ͨ������
		* 
		* �ο�ʾ��(@ref)
		*/
		using FilterCondition = bool(*)(const std::vector<double>&, double&);

	private:

		typedef std::vector<std::shared_ptr<Indicator> > IndiVecType;
		//��������ָ������������
		IndiVecType mIndicatorVec{};

		//��������
		FilterCondition mpCondition{nullptr};

		//Ĭ�Ϲ�������
		FilterCondition mpDefaultCondition = 
			[](const std::vector<double>& indices, double& finalIndex) {
				finalIndex = std::accumulate(indices.begin(), indices.end(), 0);
				return true;
			};

		//������ID
		std::string id = "undefined-filter";

	public:
		/**
		* @brief	���ָ������������
		* 
		* @param[in]	indicator	����������Ĺ���ָ��
		* 
		* @par ʾ��
		*	@code
		*		imagefilter.addIndicator(std::make_shared<Indicator>();
		*	@endcode
		*/
		void addIndicator(const std::shared_ptr<Indicator> indicator) { mIndicatorVec.push_back(indicator); }
		
		/**
		* @brief	��Ӷ��ָ������������
		* 
		* @param[in]	indicator	����������Ĺ���ָ��
		*
		* @par ʾ��
		*	@code
		*		imagefilter.addIndicator(std::make_shared<Indicator>();
		*	@endcode
		*/
		void addIndicator(const IndiVecType& indicators) { for (auto& ptr : indicators) mIndicatorVec.push_back(ptr); }
		
		/**
		* @brief	��ȡָ����������������(ֻ��)
		*
		* @return	ָ�����������ݵĳ�����
		*/
		const IndiVecType& indicators()const { return mIndicatorVec; }

		/**
		* @brief	��ȡָ����������������
		*
		* @return	ָ�����������ݵ�����
		*/
		IndiVecType& indicators() { return mIndicatorVec; }

		/**
		* @brief	���ָ������������
		* 
		* �ú���Ϊstd::vector<>::clear()�İ�װ
		*/
		void clearIndicators() { mIndicatorVec.clear(); }

		/**
		* @brief	�趨��������
		*
		* ����������Ϊ�գ���ʹ��Ĭ�Ϲ���������
		* �ۼ�����ָ��������������ֵ�����е�ͼ�񶼽�ͨ������
		* 
		* @param[in]	condition	����
		* 
		* @see	FilterCondition
		*/
		void setFilterCondition(FilterCondition condition = nullptr) { mpCondition = condition; }

		/**
		* @brief	����ͼ��
		*
		* ��û�е���setFilterCondition���ù�����������ʹ��Ĭ�Ϲ���������
		* �ۼ�����ָ��������������ֵ�����е�ͼ�񶼽�ͨ������
		*
		* @param[in]	imagePath	ͼ���ļ�·��
		* @return	���˽��[FilterOutput](@ref FilterOutput)
		*
		*/
		FilterOutput filter(const std::string& imagePath);

		/**
		* @brief	����ͼ��
		*
		* ��û�е���setFilterCondition���ù�����������ʹ��Ĭ�Ϲ���������
		* �ۼ�����ָ��������������ֵ�����е�ͼ�񶼽�ͨ������
		*
		* @param[in]	imagePath	ͼ���ļ�·������
		* @return	���˽������[FilterOutput](@ref FilterOutput)
		*
		*/
		std::vector<FilterOutput> filter(const std::vector<std::string>& imagePaths);

		/**
		* @brief	��ȡ������ID
		* @return	������ID
		*/
		std::string getID()const { return id; }

		/**
		* @brief	���ù�����ID
		* @param	_id		������ID
		*/
		void setID(const std::string& _id) { id = _id; }
	};
};