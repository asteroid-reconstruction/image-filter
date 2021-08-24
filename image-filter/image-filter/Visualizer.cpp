#include "Visualizer.h"

cv::Mat ar::util::Visualizer::_mosaic(
    const std::vector<FilterOutput>& foVec,
    std::vector<FilterOutput>::size_type from,
    std::vector<FilterOutput>::size_type count,
	cv::Size frameSize)
{
	//防止越界
	assert(from < foVec.size());
	count = count + from > foVec.size() ? count : foVec.size() - from;

	//---计算最佳单张分辨率---//

}
