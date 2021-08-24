#pragma once
#include "Indicator.h"
#include <numeric>

//asteroid reconstruction
namespace ar {

	/**
	* @brief	�����������
	*
	* ���ڱ���������Ĺ��˽����ͬʱӵ��Դͼ����Ϣ
	*/
	struct FilterOutput{

		std::string		imagePath{};	/**< ͼ���ļ�·��������ʹ��·��ָ��ͼ��ʱ��Ϊ��*/
		cv::Mat			image{};		/**< ͼ����󣬽���ʹ��OpenCV Matָ��ͼ��ʱ��Ϊ��*/
		double			index{};		/**< ���������÷֣��ɹ�����������õ�*/
		bool			passed{};		/**< �Ƿ�ͨ�����ɹ�����������ָ��*/

		/**
		* @brief	���캯��
		*
		* @param	_imgPath	ͼ��·��
		* @param	_img		ͼ��
		* @param	_index		���������÷�
		* @param	_passed		�Ƿ�ͨ������
		*/
		FilterOutput(
			const std::string& _imgPath = "",
			const cv::Mat& _img = cv::Mat(),
			double _index = 0,
			bool _passed = false) :
			imagePath(_imgPath), image(_img), index(_index), passed(_passed) {}

	};

	/**
	* @brief	ͼ���������
	* 
	* ����ʹ������ָ��������(@ref Indicator)����һ�Ż�һ��ͼ���
	* �����ĵ÷֣�����ɸѡ�������й���
	* 
	*/
	class ImageFilter {

	public:
		explicit ImageFilter(){}
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
		IndiVecType mIndicatorVec{};

		FilterCondition mpCondition{nullptr};

		FilterCondition mpDefaultCondition = 
			[](const std::vector<double>& indices, double& finalIndex) {
				finalIndex = std::accumulate(indices.begin(), indices.end(), 0);
				return true;
			};

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
		* @param[in]	image	ͼ�����
		* @return	���˽��[FilterOutput](@ref FilterOutput)
		* 
		*/
		FilterOutput filter(const cv::Mat& image);

		/**
		* @brief	����ͼ��
		*
		* ��û�е���setFilterCondition���ù�����������ʹ��Ĭ�Ϲ���������
		* �ۼ�����ָ��������������ֵ�����е�ͼ�񶼽�ͨ������
		*
		* @param[in]	images	ͼ���������
		* @return	���˽������[FilterOutput](@ref FilterOutput)
		*
		*/
		std::vector<FilterOutput> filter(const std::vector<cv::Mat> images);

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
	};
};