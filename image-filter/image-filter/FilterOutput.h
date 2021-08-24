#pragma once

#include <opencv2/core.hpp>

namespace ar {

	/**
	* @brief	�����������
	*
	* ���ڱ���������Ĺ��˽����ͬʱӵ��Դͼ����Ϣ
	*/
	class FilterOutput {

    public:

		std::string		imagePath{};	/**< ͼ���ļ�·��������ʹ��·��ָ��ͼ��ʱ��Ϊ��*/

		double			finalIndex{};	/**< ���������÷֣��ɹ�����������õ�*/
		bool			passed{};		/**< �Ƿ�ͨ�����ɹ�����������ָ��*/

		std::vector<double>			stageIndices{};	/**< �׶������÷�*/
		std::vector<std::string>	indicatorIDs{};	/**< ����ָ��������ID����*/
		std::string					filterID{};		/**< ������ID����*/

		/**
		* @brief	��������תΪJSON�ı�
		*
		* @attention	image��Ա�����޷�ת��ΪJSON�ı�
		*
		* @return	JSON�ı��ַ���
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