#ifndef header_hist_segm_hpp
#	define header_hist_segm_hpp

#	include <opencv2/core.hpp>
#	include <opencv2/imgcodecs.hpp>
#	include <opencv2/imgproc.hpp>
#	include <vector>
#	include "hist_calc.hpp"
#	include "color_space.hpp"

#ifndef OLD



/**********************************************************BASIC PRIMITIVES *******************************************/


/********************************* histogram - histogram matching ************************/
bool histograms_match(Histogram & one, Histogram &two, HistogramComp limit);
bool histograms_match(cv::Mat & one, cv::Mat &two, HistogramComp limit);



/******************************** hist - img matching ***********************************/
bool hist_img_match_img(cv::Mat & one, cv::Mat &two, HistogramComp limit, int num_clusters, int color_space);


/******************************* hist - img matching ***********************************/
bool hist_hist_match_img(Histogram &hist, cv::Mat &img, HistogramComp limit, int num_clusters, int color_space);
bool hist_hist_match_img(cv::Mat &hist, cv::Mat &img, HistogramComp limit, int num_clusters, int color_space);

bool hist_hist_match_img(Histogram &hist, cv::Mat &img, cv::Rect rect, HistogramComp limit, int num_clusters, int color_space);





/**************************************************** Segmenting functions ******************************************/
void mask_img_given_hist_iter(Histogram &hist, cv::Mat &img,cv::Mat &mask,cv::Size rs, HistogramComp limit, int xstep, int ystep, int color_space);

#endif

#ifdef OLD
void hist_filter_mid(cv::Mat & _img, cv::Mat &mask)
#endif





#endif