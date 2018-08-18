#ifndef header_hist_calc_hpp
#	define header_hist_calc_hpp

#	include <opencv2/core.hpp>
#	include <opencv2/imgproc.hpp>
#	include <opencv2/imgcodecs.hpp>
#	include "color_space.hpp"
#	include <cstdio>

//#	define OLD
#	ifndef OLD

/******************************************some defintions **********************************************************/
typedef std::vector<cv::Mat> Histogram;

struct HistogramComp{
	double correl;
	double hellinger;
};

#	define SINGLE_CHANNEL
#	define MULTI_CHANNEL

/***********************************calculating single channel histograms********************************************/
cv::Mat calculate_histogram_single_channel(cv::Mat &img, int channel, int num_clusters, float lower_value, float upper_value);
cv::Mat calculate_histogram_single_channel(cv::Mat &img, int channel, int num_clusters);
cv::Mat calculate_histogram_single_channel(cv::Mat &img, int num_clusters, float lower_value, float upper_value);
cv::Mat calculate_histogram_single_channel(cv::Mat &img, int num_clusters);


Histogram calculate_histogram_single_channel_hist(cv::Mat &img, int channel, int num_clusters, float lower_value, float upper_value);
Histogram calculate_histogram_single_channel_hist(cv::Mat &img, int channel, int num_clusters);
Histogram calculate_histogram_single_channel_hist(cv::Mat &img, int num_clusters, float lower_value, float upper_value);
Histogram calculate_histogram_single_channel_hist(cv::Mat &img, int num_clusters);

Histogram calculate_histogram_single_channel_hist_rect(cv::Mat &img, cv::Rect rect,int num_clusters);


/****************************************** some additional functions for convenience ********************************/
cv::Mat calculate_histogram_single_channel_b(MULTI_CHANNEL cv::Mat &img, int num_clusters);
cv::Mat calculate_histogram_single_channel_g(cv::Mat &img, int num_clusters);
cv::Mat calculate_histogram_single_channel_r(cv::Mat &img, int num_clusters);
cv::Mat calculate_histogram_single_channel_h(cv::Mat &img, int num_clusters);
cv::Mat calculate_histogram_single_channel_s(cv::Mat &img, int num_clusters);
cv::Mat calculate_histogram_single_channel_v(cv::Mat &img, int num_clusters);




/********************************** calculating multi channel histograms *********************************************/
Histogram calculate_histogram(cv::Mat &img, int num_clusters);
Histogram calculate_histogram_bgr(cv::Mat &img, int num_clusters);
Histogram calculate_histogram_hsv(cv::Mat &img, int num_clusters);
Histogram calculate_histogram(cv::Mat &img, int num_clusters, int color_space);
Histogram calculate_histogram(cv::Mat &img, cv::Rect rect, int num_clusters, int color_space);


/********************************************** comparing **************************************************************/
double compare_histogram_min(Histogram &one, Histogram &two, int method);
double compare_histogram_max(Histogram &one, Histogram &two, int method);

HistogramComp compare_histogram(Histogram &hist_one, Histogram &hist_two);
HistogramComp compare_histogram(cv::Mat &hist_one, cv::Mat &hist_two);







#	endif

void friendly_print(cv::Mat &hist, FILE *fp = stdout);

double  comp_split_hist(cv::Mat & hist_one, cv::Mat & hist_two, int mode);


#	ifdef OLD
cv::Mat calculate_histogram_single_channel(cv::Mat &img, int num_clusters = 256);
cv::Mat calculate_histogram_bgr(cv::Mat &img, int num_clusters = 256);
#	endif













#endif