#pragma once

#include <opencv2/core.hpp>

namespace ar {

	/**
	* @brief	过滤器输出类
	*
	* 用于保存过滤器的过滤结果，同时拥有源图像信息
	*/
	class FilterOutput {

    public:

		std::string		imagePath{};	/**< 图像文件路径，仅当使用路径指定图像时不为空*/

		double			finalIndex{};	/**< 最终质量得分，由过滤条件计算得到*/
		bool			passed{};		/**< 是否通过，由过滤条件计算指定*/

		std::vector<double>			stageIndices{};	/**< 阶段质量得分*/
		std::vector<std::string>	indicatorIDs{};	/**< 质量指数计算器ID序列*/
		std::string					filterID{};		/**< 过滤器ID序列*/

		/**
		* @brief	将输出结果转为JSON文本
		*
		* @attention	image成员变量无法转换为JSON文本
		*
		* @return	JSON文本字符串
		*/
		std::string toJSON() const{
            std::stringstream json;

            auto wrap = [](const std::string& str) {
                return "\"" + str + "\"";
            };

            char colon = ':';
            char comma = ',';
            char lbra = '[', rbra = ']';
            char lcur = '{', rcur = '}';

            std::vector<std::string> properties{
                wrap("image-url"),
                wrap("final-index"),
                wrap("passed"),
                wrap("stage-indices"),
                wrap("indicator-ids"),
                wrap("filter-id"),
            };

            json << lcur;

            json << properties[0] << colon << wrap(imagePath) << comma;
            json << properties[1] << colon << finalIndex << comma;
            json << properties[2] << colon << (passed ? "true" : "false") << comma;

            json << properties[3] << colon << lbra;
            for (decltype(stageIndices)::size_type i = 0; i < stageIndices.size(); ++i) {
                json << stageIndices[i];
                if (i != stageIndices.size() - 1)
                    json << comma;
            }
            json << rbra;

            json << properties[4] << colon << lbra;
            for (decltype(indicatorIDs)::size_type i = 0; i < indicatorIDs.size(); ++i) {
                json << wrap(indicatorIDs[i]);
                if (i != stageIndices.size() - 1)
                    json << comma;
            }
            json << rbra;

            json << properties[5] << colon << wrap(this->filterID);

            json << rcur;

            return json.str();
		}
	};
}