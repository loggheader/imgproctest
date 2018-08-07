#include "partition.hpp"
#include "color_img.hpp"
#include "repair_partition.hpp"
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "polygon_projection.hpp"

using namespace std;
using namespace cv;

/********************* some define's ****************/
#define CUTOFF 50
#	define WAIT  cv::waitKey(0); \
				 cv::destroyAllWindows();
/********************* actual code *****************/



void remove_open_contours_test(Mat &img);
void image_after_segmenting_closed_contours(cv::Mat &img, int method);
void feature_work(Mat &img, int method);
void help()
{
	printf("Usage:\n"
		   "featuredemo [image name] ['none' / 'simple' option for findContours algorithm]\n");
	exit(0);
}



/* 	
	a small static demo for projectng to polygons. A LOT of things not the way they should be but it will be updated in the feature 
*/

int main(int argc, char **argv)
{
	if(argc != 3) help();
	string option = string(argv[2]);
	cv::Mat img = cv::imread(argv[1]);
	int method;
	if(option == "none") method = CV_CHAIN_APPROX_NONE;
	else if(option == "simple") method = CV_CHAIN_APPROX_SIMPLE;
	else help();
	image_after_segmenting_closed_contours(img,method);
}






void image_after_segmenting_closed_contours(cv::Mat &img, int method)
{
	Mat img2 = img.clone();
	img2 = Scalar::all(0);
	vector<vector<Point> > sets, result;
	partition_image_to_black_and_white_sets(img,sets,false,true);	
	for(int i=0;i<sets.size();i++){
		segment_contour_to_subsets(sets[i],result);
	}
	for(int i=0;i<result.size();i++){
		color_points(img2,result[i],cv::Vec3b(255,255,255));
	}
	imshow("lets test this",img2);
	WAIT
	partition_image_to_black_and_white_sets(img2,sets,true,false);
	img2 = Scalar::all(0);
	for(int i=1; i<sets.size();i++){
		if(sets[i].size() > CUTOFF /*|| true*/) color_points(img2,sets[i],Vec3b(255,0,0));
	}
	imshow("finally painting original image",img2);
	WAIT
	feature_work(img2,method);

}







void feature_work(Mat &img,int method)
{
	Mat img2 = img.clone();
	Mat img3 = img.clone(); img3 = Scalar::all(0);
	cvtColor(img,img2,CV_BGR2GRAY);
	threshold(img2,img2,10,255,0);
	vector<vector<Point> > contour;
	findContours(img2,contour,CV_RETR_EXTERNAL,method);
	for(int i = 0; i <contour.size();i++){
		PolygonProjection p = project_shape_to_polygons(contour[i]);
		cout<< arcLength(contour[i],true)<<endl;
		print_polyg(p);
		drawContours(img3,contour,i,Scalar(255,0,0));
		imshow("oime",img3); WAIT
		drawContours(img3,contour,i,Scalar(255,255,255));
	}

}




















