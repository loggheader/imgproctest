#ifndef header_color_img_hpp
#	define header_color_img_hpp

#	include <opencv2/opencv.hpp>
#	include <vector>

/*************** coloring part of an image *********************/
void color_points(cv::Mat &img, std::vector< cv::Point> &points, cv::Vec3b color);
void color_rect(cv::Mat &img, cv::Rect rect, cv::Vec3b color);




#endif