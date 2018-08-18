#include "hist_calc.hpp"
#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;
using namespace cv;



#ifndef OLD
/**************************************************************************************************************************************/
/*********************************************** calcualte single channel histogram ***************************************************/
/**************************************************************************************************************************************/




/*************************************** functions returning Mat ****************************************/
cv::Mat calculate_histogram_single_channel(cv::Mat &img, int channel, int num_clusters, float lower_value, float upper_value)
{
	Mat ret;
	int channels [] = {channel};
	int histSize [] = {num_clusters};
	float range[] = {lower_value,upper_value};
	const float * ranges[]  = {range};
	calcHist(&img,1,channels,Mat(),ret,1,histSize,ranges,true,false);
	return ret;	
}

cv::Mat calculate_histogram_single_channel(cv::Mat &img, int channel, int num_clusters)
{
	return calculate_histogram_single_channel(img,channel,num_clusters,0,256);
}

cv::Mat calculate_histogram_single_channel(cv::Mat &img, int num_clusters, float lower_value, float upper_value)
{
	return calculate_histogram_single_channel(img,0,num_clusters,lower_value,upper_value);
}

cv::Mat calculate_histogram_single_channel(cv::Mat &img, int num_clusters)
{
	return calculate_histogram_single_channel(img,num_clusters,0,256);	
}




/*****************************************functions returning Histogram ******************************************/
Histogram calculate_histogram_single_channel_hist(cv::Mat &img, int channel, int num_clusters, float lower_value, float upper_value)
{
	Histogram ret;
	ret.push_back(calculate_histogram_single_channel(img,channel,num_clusters,lower_value,upper_value));
	return ret;
}

Histogram calculate_histogram_single_channel_hist(cv::Mat &img, int channel, int num_clusters)
{
	return calculate_histogram_single_channel_hist(img,channel,num_clusters,0,256);
}

Histogram calculate_histogram_single_channel_hist(cv::Mat &img, int num_clusters, float lower_value, float upper_value)
{
	return calculate_histogram_single_channel_hist(img,0,num_clusters,lower_value,upper_value);
}

Histogram calculate_histogram_single_channel_hist(cv::Mat &img, int num_clusters)
{
	return calculate_histogram_single_channel_hist(img,0,num_clusters,0,256);
}

Histogram calculate_histogram_single_channel_hist_rect(cv::Mat &img, cv::Rect rect,int num_clusters)
{
	Mat img_reg = img(rect);
	return calculate_histogram_single_channel_hist(img_reg,num_clusters);
}

/********************************** additional single channel functions (for use in multi channel images) ***********************/
cv::Mat calculate_histogram_single_channel_b(MULTI_CHANNEL cv::Mat &img, int num_clusters)
{
	return calculate_histogram_single_channel(img,0,num_clusters);
}


cv::Mat calculate_histogram_single_channel_g(cv::Mat &img, int num_clusters)
{
	return calculate_histogram_single_channel(img,1,num_clusters);
}

cv::Mat calculate_histogram_single_channel_r(cv::Mat &img, int num_clusters)
{
	return calculate_histogram_single_channel(img,2,num_clusters);
}


cv::Mat calculate_histogram_single_channel_h(cv::Mat &img, int num_clusters)
{
	return calculate_histogram_single_channel(img,0,num_clusters,0,180);
}

cv::Mat calculate_histogram_single_channel_s(cv::Mat &img, int num_clusters)
{
	return calculate_histogram_single_channel(img,1,num_clusters);
}

cv::Mat calculate_histogram_single_channel_v(cv::Mat &img, int num_clusters)
{
	return calculate_histogram_single_channel(img,2,num_clusters);
}



/******************************************************************************************************************************/
/********************************************calculate multi channel histograms ***********************************************/
/******************************************************************************************************************************/



Histogram calculate_histogram(cv::Mat &img, int num_clusters)
{
	Histogram hist;
	//printf("\n\ninside %s\n",__builtin_FUNCTION());
	for(int i=0;i<img.channels();i++) {
		Mat g =calculate_histogram_single_channel(img,i,num_clusters);
		//friendly_print(g);
		hist.push_back(g);
	}
	//printf("outside\n\n");
	return hist;
}

Histogram calculate_histogram_bgr(cv::Mat &img, int num_clusters)
{
	return calculate_histogram(img,num_clusters);
}

Histogram calculate_histogram_hsv(cv::Mat &img, int num_clusters)
{
	Histogram hist(3);
	hist[0] = calculate_histogram_single_channel_h(img,num_clusters);
	hist[1] = calculate_histogram_single_channel_s(img,num_clusters);
	hist[2] = calculate_histogram_single_channel_v(img,num_clusters);
	return hist;
}

Histogram calculate_histogram(cv::Mat &img, int num_clusters, int color_space)
{
	if(color_space == COLOR_GRAY || color_space == COLOR_BGR) return calculate_histogram(img,num_clusters);
	else if(color_space == COLOR_HSV) return calculate_histogram_hsv(img,num_clusters);
	else return Histogram();
}

Histogram calculate_histogram(cv::Mat &img, cv::Rect rect, int num_clusters, int color_space)
{
	Mat img_reg = img(rect);
	return calculate_histogram(img_reg,num_clusters,color_space);
}




/******************************************************************************************************************************************/
/******************************************************** histogram comparison ************************************************************/
/******************************************************************************************************************************************/
double compare_histogram_min(Histogram &one, Histogram &two, int method)
{
	bool start = true;
	if(one.size() != two.size()) return __builtin_huge_val();
	double minval;
	for(int i=0;i<one.size();i++){
		double d = compareHist(one[i],two[i],method);
		if(d < minval || start == true) {
			minval = d;
			start = false;
		}
	}
	return minval;
}

double compare_histogram_max(Histogram &one, Histogram &two, int method)
{
	bool start = true;
	if(one.size() != two.size()) return -1 * __builtin_huge_val();
	double maxval;
	for(int i=0;i<one.size();i++){
		double d = compareHist(one[i],two[i],method);
		if(d > maxval || start == true) {
			maxval = d;
			start = false;
		}
	}
	return maxval;
}


HistogramComp compare_histogram(Histogram &hist_one, Histogram &hist_two)
{
	HistogramComp hc;
	hc.correl = compare_histogram_min(hist_one,hist_two,HISTCMP_CORREL);
	hc.hellinger = compare_histogram_max(hist_one,hist_two,HISTCMP_HELLINGER);
	return hc;
}

HistogramComp compare_histogram(cv::Mat &hist_one, cv::Mat &hist_two)
{
	HistogramComp hc;
	hc.correl = compareHist(hist_one,hist_two,HISTCMP_CORREL);
	hc.hellinger = compareHist(hist_one,hist_two,HISTCMP_HELLINGER);
	return hc;
}







#endif


/***************************************************************old functions********************************************************************/


void friendly_print(cv::Mat &hist, FILE *fp)
{
	for(int i=0; i<hist.channels();i++){
		fprintf(fp,"\nchannel %d\n",i);
		for(int j=0; j<hist.size().height;j++){
			if( j % 8 == 0) fputc('\n',fp);
			fprintf(fp,"%f ",hist.at<float>(i,j));
		}
	}
	fputc('\n',fp);
}

double  comp_split_hist(cv::Mat & hist_one, cv::Mat & hist_two, int mode)
{
	vector<Mat> sp_one,sp_two;
	vector<double> comp;
	split(hist_one,sp_one);
	split(hist_two,sp_two);
	for(int i=0;i<sp_one.size();i++){
		comp.push_back(compareHist(sp_one[i],sp_two[i], mode));
	}
	double min_val = comp[0];
	for(double v : comp){
		if(v < min_val) min_val = v;
	}
	return min_val;
}








#ifdef OLD

cv::Mat calculate_histogram_single_channel(cv::Mat &img, int num_clusters)
{
	Mat ret;
	int channels [] = {0};
	int histSize [] = {num_clusters};
	float range[] = {0,256};
	const float * ranges[]  = {range};
	calcHist(&img,1,channels,Mat(),ret,1,histSize,ranges,true,false);
	return ret;
}


cv::Mat calculate_histogram_bgr(cv::Mat &img, int num_clusters)
{
	Mat ret;
	vector<Mat> out_mat, split_mat;
	split(img, split_mat);
	for(int i=0;i<split_mat.size();i++){
		out_mat.push_back(calculate_histogram_single_channel(split_mat[i],num_clusters));
	}
	merge(out_mat,ret);
	return ret;
}










#endif












