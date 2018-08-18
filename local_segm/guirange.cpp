#include <opencv2/opencv.hpp>
#include "color_space.hpp"
#include "rect_op.hpp"
#include <cstdio>
#include <iostream>
#include <string>
#include "SimpleRectGui.hpp"
#include "hist_calc.hpp"

using namespace std;
using namespace cv;

#define SHOW(x,y) {imshow(x,y); waitKey(0); destroyWindow(x);}


int main(int argc, char **argv)
{
	string s(argv[1]);
	string w = "ante hi";
	Mat img = imread(s);
	Mat gray; cvtColor(img,gray,COLOR_BGR2GRAY);
	SimpleRectGui app;
	app.set_image_and_window_name(img,w);
	app.autowork();
	vector<Point> pp = app.get_points();
	vector<Rect>  rr = app.get_rects();
	Mat temp(img.size(),CV_8UC1,Scalar(0));
	Mat mask(img.size(),CV_8UC1,Scalar(255));
	for(Rect r : rr){
		mask(r) = Scalar::all(0);
	}
	for(int i = 0; i<pp.size();i++){
		cout<<i<<endl;
		pair<Vec3b , Vec3b> bounds = obtain_lower_upper_color_bounds(img.at<Vec3b>(pp[i].y,pp[i].x), Vec3b(50,50,50), COLOR_BGR);
		//Mat tt = histogram_single_channel_rect(gray, rr[i],32); friendly_print(tt);
		in_range_rect(img,temp,rr[i],bounds.first,bounds.second);
		bitwise_or(temp(rr[i]),mask(rr[i]),mask(rr[i]));
	}
	cout<<"outside"<<endl;
	cvtColor(mask,mask,CV_GRAY2BGR);
	bitwise_and(mask,img,img);
	imshow(w,img);
	waitKey(0); destroyAllWindows();
	SHOW(w,mask);
}

































