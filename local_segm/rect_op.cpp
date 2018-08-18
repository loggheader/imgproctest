#include "rect_op.hpp"
#include "color_space.hpp"
#include "hist_calc.hpp"
#include <vector>


using namespace std;
using namespace cv;


/********************************************Rect containing point ***************************************************/

/****** backend functions ***************/

static Rect rect_containing_point_left_up(cv::Point point, cv::Size imgs, cv::Size s)
{
	return Rect(point.x,point.y,s.width,s.height) & Rect(0,0,imgs.width,imgs.height);
}

static Rect rect_containing_point_mid(cv::Point point, cv::Size imgs, cv::Size s)
{
	return Rect(point.x - s.width/2,point.y - s.height/2,s.width,s.height) & Rect(0,0,imgs.width,imgs.height);
}

static Rect rect_containing_point_left_down(Point point, Size imgs, Size s)
{
	return Rect(Point(point.x, point.y- s.height), s) & Rect(Point(0,0), imgs);
}



Rect rect_containing_point(cv::Point point, cv::Size imgs, cv::Size s, int rect_mode)
{
	if(rect_mode == POINT_MID) return rect_containing_point_mid(point,imgs,s);
	else if(rect_mode == POINT_LEFT_UP) return rect_containing_point_left_up(point,imgs,s);
	else if(rect_mode == POINT_LEFT_DOWN) return rect_containing_point_left_down(point,imgs,s);
	else return Rect(0,0,0,0);
}

/******************************************** in range operations ****************************************************/

void in_range_rect(cv::Mat &img, cv::Mat &outp, cv::Rect rect, cv::Vec3b lower_bound, cv::Vec3b upper_bound)
{
	Mat img_region  = img(rect);
	Mat outp_region = outp(rect);
	cv::inRange(img_region,lower_bound,upper_bound,outp_region);
}


cv::Rect in_range_rect_around_point(cv::Mat &img, cv::Mat &outp, cv::Point point, cv::Size s, cv::Vec3b tolerance,int colorspace)
{
	cv::Size imgs = img.size();
	Rect rect = rect_containing_point(point,imgs,s,POINT_MID);
	cv::Vec3b pcolor = img.at<Vec3b>(point.y,point.x);
	pair<Vec3b,Vec3b> bounds = obtain_lower_upper_color_bounds(pcolor,tolerance,colorspace);
	in_range_rect(img,outp,rect,bounds.first,bounds.second);
	return rect;
}


/****************************************** treshold operations ******************************************************/
/*
void treshold_rect_gray(cv::Mat &img, cv::Mat &outp, cv::Rect rect, int thesh_mode, int tresh_value)
{
	Mat img_region = img(rect);
	Mat outp_region = outp(rect);
	return cv::threshold(img_region,)
}
*/

























