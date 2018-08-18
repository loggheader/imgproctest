#include <opencv2/opencv.hpp>
#include "hist_segm.hpp"
#include "hist_calc.hpp"
#include "rect_op.hpp"
#include <iostream>

using namespace std;
using namespace cv;


#	ifndef OLD

/*********************************************** simple histogram matching ******************************/

bool histograms_match(Histogram & one, Histogram &two, HistogramComp limit)
{
	HistogramComp hc = compare_histogram(one,two);
	//cout << hc.correl<<endl<<hc.hellinger<<endl;
	if(hc.correl > limit.correl && hc.hellinger < limit.hellinger) return true;
	else return false;
}


bool histograms_match(cv::Mat & one, cv::Mat &two, HistogramComp limit)
{
	HistogramComp hc = compare_histogram(one,two);
	if(hc.correl > limit.correl && hc.hellinger < limit.hellinger) return true;
	else return false;
}



/****************************************** histogramical matching of images ************************/
bool hist_img_match_img(cv::Mat & one, cv::Mat &two, HistogramComp limit,  int num_clusters, int color_space)
{
	Histogram hone = calculate_histogram(one,num_clusters,color_space);
	Histogram htwo = calculate_histogram(two,num_clusters,color_space);
	return histograms_match(hone,htwo,limit);
}


bool hist_hist_match_img(Histogram &hist, cv::Mat &img, HistogramComp limit, int num_clusters, int color_space)
{
	Histogram hist_img = calculate_histogram(img,num_clusters,color_space);
	return histograms_match(hist,hist_img,limit);
}

bool hist_hist_match_img(Histogram &hist, cv::Mat &img, cv::Rect rect,HistogramComp limit, int num_clusters, int color_space)
{
	Mat img_reg = img(rect);
	return hist_hist_match_img(hist,img_reg,limit,num_clusters,color_space);
}



bool hist_hist_match_img(cv::Mat &hist, cv::Mat &img, HistogramComp limit, int num_clusters, int color_space)
{
	return true;
}



/*****************************************************************************************************/



void mask_img_given_hist_iter(Histogram &hist, cv::Mat &img,cv::Mat &mask,cv::Size rs, HistogramComp limit, int xstep, int ystep, int color_space)
{
	Rect img_rect = Rect(Point(0,0), img.size());
	Rect rect = Rect(Point(0,0),rs);
	cout<<"image rect"<<endl<<img_rect<<endl<<endl;
	for(rect.x = 0; !(rect.y = 0) &&(rect & img_rect) == rect; rect.x += xstep){
		for(rect.y = 0; (rect & img_rect) == rect; rect.y += ystep){
	//		cout<<rect<<endl;
			if(hist_hist_match_img(hist,img,rect,limit,hist[0].size().height,color_space) == true){
				rectangle(mask,rect,Scalar(255),CV_FILLED);
			}
	//		cout<<endl;
		}
	}
}






#	endif
#	ifdef OLD

#define OFFSET 15
#define STEP   5
#define LIMIT_SIM 0.5


void hist_filter_mid(cv::Mat & _img, cv::Mat &mask)
{
	Mat img = _img.clone(); //cvtColor(img,img,COLOR_BGR2GRAY);
	Size imgs = img.size();
	Size defs = Size(25,25);
	int x_positive = imgs.width/2 - 12 - OFFSET;
	int y_positive = imgs.height/2 -12;
	Rect positive(x_positive,y_positive,defs.width,defs.height);
	Rect r(0,0,defs.width,defs.height);
	mask = Scalar::all(0);
	Mat hist_positive = histogram_bgr_rect(img,positive,32);
	for(r.x=0;r.x+r.width < imgs.width;r.x += STEP){
		for(r.y=0; r.y + r.height < imgs.height; r.y += STEP){
			Mat hist_local = histogram_bgr_rect(img,r,32);
			double similarity = compareHist(hist_positive,hist_local,HISTCMP_CORREL);
			if(similarity > LIMIT_SIM) mask(r).setTo(255);
		}
	}
}




#	endif




