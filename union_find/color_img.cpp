#include "color_img.hpp"

using namespace std;
using namespace cv;
void color_points(cv::Mat &img, std::vector< cv::Point> &points, cv::Vec3b color)
{
	for(Point point : points) {
		img.at<Vec3b>(point.y,point.x)[0] = color[0];
		img.at<Vec3b>(point.y,point.x)[1] = color[1];
		img.at<Vec3b>(point.y,point.x)[2] = color[2];
	}
}


void color_rect(cv::Mat &img, cv::Rect rect, cv::Vec3b color)
{
	for(int i = rect.y; i < (rect.y + rect.height); i++){
		for(int j = rect.x; j < (rect.x + rect.width); j++){
			img.at<Vec3b>(i,j) = color;
		}
	}





}