#include "hist_calc.hpp"
#include "rect_op.hpp"
#include "SimpleRectGui.hpp"
#include "hist_segm.hpp"
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

static void help()
{
	printf("Usage:\n"
		   "./histdemo [image name]" /*  " [option for distance calculation, see below]\n"*/
		   
		   /*
		   "\nOptions can be passed on of the following flags:\n"
		   "correl\n"
		   "chisqr\n"
		   "chisqr_alt\n"
		   "intersect\n"
		   "hellinger\n"
		   "kl_div\n"
		   */
		   );
	exit(0);
}

static int get_mode(string  s)
{
	if(s == "correl") return HISTCMP_CORREL;
	else if(s == "chisqr") return HISTCMP_CHISQR ;
	else if(s == "chisqr_alt") return HISTCMP_CHISQR_ALT;
	else if(s == "intersect") return HISTCMP_INTERSECT;
	else if(s == "hellinger") return HISTCMP_HELLINGER;
	else if(s == "kl_div") return HISTCMP_KL_DIV;
	else return -1;
}

#define KK 256

int main(int argc, char ** argv)
{
	if(argc != 2) help();
	Mat img = imread(argv[1]);
	if(img.empty()) help();
	Mat gray,hsv;
	cvtColor(img,gray,COLOR_BGR2GRAY);
	cvtColor(img,hsv,COLOR_BGR2HSV);
	string w = string("hello");
	//int mode = get_mode(string(argv[2])); if(mode == -1) help();
	
   	while(1){
		SimpleRectGui app;
		app.set_image_and_window_name(img,w);
		app.autowork();
		vector<Point> p = app.get_points();
		vector<Rect>  r = app.get_rects();
		if(p.size() < 2) break;
		cout << r[0]<<endl;
		cout << r[1]<<endl;
		cout << img.size() <<endl<<endl;

		Histogram g_one,g_two,bgr_one,bgr_two,hsv_one,hsv_two;
		g_one = calculate_histogram(gray, r[0], 32, COLOR_GRAY);
		g_two = calculate_histogram(gray, r[1], 32, COLOR_GRAY);
		bgr_one = calculate_histogram(img, r[0], 32, COLOR_BGR);
		bgr_two = calculate_histogram(img, r[1], 32, COLOR_BGR);
		hsv_one = calculate_histogram(img, r[1], 32, COLOR_HSV);
		hsv_two = calculate_histogram(img, r[1], 32, COLOR_HSV);

		/*Mat img_reg = img(r[0]);
		Mat tt =calculate_histogram_single_channel(img_reg,32);
		friendly_print(tt);
		tt = calculate_histogram_single_channel(img_reg,0,32);
		friendly_print(tt); */
		/*
		printf("bgr_one\n");
		friendly_print(bgr_one[0]);
		printf("bgr_two\n");
		friendly_print(bgr_one[1]);
		*/

		HistogramComp hcg = compare_histogram(g_one,g_two);
		HistogramComp hcc = compare_histogram(bgr_one,bgr_two);
		HistogramComp hcv = compare_histogram(hsv_one,hsv_two);
		printf("Correl and Hellinger distances:\n");
		printf("\nWorking in gray:\n");
		printf("%lf\n%lf\n",hcg.correl, hcg.hellinger);
		printf("\nWorking in bgr:\n");
		printf("%lf\n%lf\n",hcc.correl, hcc.hellinger);
		printf("\nWorking in hsv:\n");
		printf("%lf\n%lf\n",hcv.correl, hcv.hellinger);
		printf("*******************************************************************************************\n");
   }
}

