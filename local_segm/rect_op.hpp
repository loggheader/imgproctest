#ifndef header_rect_op_hpp
#	define header_rect_op_hpp

#	include <opencv2/opencv.hpp>


/************************* create rect functions *************/

#	define DEFAULT_RECT_SIZE         cv::Size(50,50)


#	define POINT_MID 			 0
#	define POINT_LEFT_UP         1
#	define POINT_LEFT_DOWN       2
#	define POINT_RIGHT_UP 		 3	
#	define POINT_RIGHT_DOWN 	 4
#	define POINT_RANDOM			 5

cv::Rect rect_containing_point(cv::Point point, cv::Size imgs, cv::Size s = DEFAULT_RECT_SIZE, int rect_mode = POINT_LEFT_UP);

/************************ in range operations ******************/
void in_range_rect(cv::Mat &img, cv::Mat &outp, cv::Rect rect, cv::Vec3b lower_bound, cv::Vec3b upper_bound);
cv::Rect in_range_rect_around_point(cv::Mat &img, cv::Mat &outp, cv::Point point, cv::Size s, cv::Vec3b tolerance,int colorspace);


/********************* treshold operations ***********************/
/*
double treshold_rect_gray(cv::Mat &img, cv::Mat &outp, cv::Rect rect, int thesh_mode, int tresh_value = 128);
*/



#endif