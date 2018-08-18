#include <opencv2/opencv.hpp>
#include "color_space.hpp"
#include "hist_segm.hpp"
#include "hist_calc.hpp"
#include "SimpleRectGui.hpp"
#include <cstdio>
#include <cstdlib>
#

using namespace std;
using namespace cv;

void help()
{
	fprintf(stderr,"Usage:\n"
			"./maskhist [img name] [correl limit] [hellinger limit]\n"
		);
	exit(0);
}

#define SHOW(x,y) {imshow(x,y); waitKey(0); destroyWindow(x);}

int main(int argc, char ** argv)
{
	if(argc != 4) help();
	Mat img = imread(argv[1]); if(img.empty()){fprintf(stderr,"no such file %s\n",argv[1]); help();}
	Mat gray; cvtColor(img,gray,COLOR_BGR2GRAY);


	SimpleRectGui app;
	app.set_image_and_window_name(img,"window");
	app.autowork();
	if(app.get_rects().size() == 0) return 0;
	Rect rect= app.get_rects().back();

	Mat mask_bgr (img.size(),CV_8UC1, Scalar(0));
	Mat mask_gray (img.size(),CV_8UC1, Scalar(0));

	Histogram hist = calculate_histogram(img,rect,32,COLOR_BGR);
	HistogramComp hc; hc.hellinger = atof(argv[3]); hc.correl = atof(argv[2]);
	mask_img_given_hist_iter(hist,img,mask_bgr,Size(25,25),hc,5,5,COLOR_BGR);
	
	Histogram hist_gray = calculate_histogram(gray,rect,32,COLOR_GRAY);
	HistogramComp hc_gray; hc_gray.hellinger = atof(argv[3]); hc_gray.correl = atof(argv[2]);
	mask_img_given_hist_iter(hist_gray,gray,mask_gray,Size(25,25),hc_gray,5,5,COLOR_GRAY);

	Mat mask(img.size(),CV_8UC1,Scalar(0));
	bitwise_or(mask_gray,mask_bgr,mask);
	SHOW("mask_gray",mask_gray);
	SHOW("mask_bgr",mask_bgr);

	SHOW("mask",mask);
	Mat outp;
	bitwise_and(img,img,outp,mask);
	SHOW("outp",outp);
}

























