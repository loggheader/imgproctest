#ifndef header_colorspace_hpp
#	define header_colorspace_hpp

#	include <opencv2/opencv.hpp>


#	define COLOR_BGR 	1
#	define COLOR_HSV 	2
#	define COLOR_GRAY 	4

;
inline std::pair<cv::Vec3b,cv::Vec3b> obtain_lower_upper_color_bounds(cv::Vec3b center, cv::Vec3b tolerance, int color_space)
{
	std::pair<cv::Vec3b,cv::Vec3b> ret;
	cv::Vec3b a = center, b = tolerance;
	if(color_space == COLOR_BGR){
		ret.first[0] = (a[0] >= b[0]) ? (a[0]-b[0]) : 0;
		ret.first[1] = (a[1] >= b[1]) ? (a[1]-b[1]) : 0;
		ret.first[2] = (a[2] >= b[2]) ? (a[2]-b[2]) : 0;

		ret.second[0] = (a[0] < 255-b[0]) ? (a[0]+b[0]) : 255;
		ret.second[1] = (a[1] < 255-b[1]) ? (a[1]+b[1]) : 255;
		ret.second[2] = (a[2] < 255-b[2]) ? (a[2]+b[2]) : 255;
	}
	else if(color_space == COLOR_HSV){
		ret.first[0] = (a[0] >= b[0]) ? (a[0]-b[0]) : (180 - (b[0]-a[0]));
		ret.first[1] = (a[1] >= b[1]) ? (a[1]-b[1]) : 0;
		ret.first[2] = (a[2] >= b[2]) ? (a[2]-b[2]) : 0;

		ret.second[0] = (a[0] < 180-b[0]) ? (a[0]+b[0]) : (a[0] - (180-b[0]));
		ret.second[1] = (a[1] < 255-b[1]) ? (a[1]+b[1]) : 255;
		ret.second[2] = (a[2] < 255-b[2]) ? (a[2]+b[2]) : 255;

		if(ret.second[0] < ret.first[0]) std::swap(ret.second[0],ret.first[0]);
	}
	return ret;
}








#endif