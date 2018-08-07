#include "polygon_projection.hpp"
#include <iostream>
using namespace std;
using namespace cv;



void iter_approx_poly_dp_curve(std::vector<cv::Point> &curve, double * proj, int num_polyg, int iter, double estart, double estep, int mode)
{
	if(num_polyg < 1) return ;
	vector<Point> approx_curve;
	double e = estart; int i;
	for(int j=0;j<num_polyg;j++) proj[j] = 0.0;
	for(i=0, e=estart; i<iter; i++,e+=estep){
		cv::approxPolyDP(curve,approx_curve,e,true);
		int output = approx_curve.size();
		cout<<output<<endl;
		if(output >= (2+num_polyg)) output = 2+num_polyg;
		proj[output-3] +=1.0;
	}
}

void normalise_projections(double *proj, int num_polyg, int mode)
{
	double sum = 0.0;
	for(int i=0;i<num_polyg;i++){
		if(mode == NORM_QUADRATIC) proj[i] = proj[i] * proj[i];
		sum = sum + proj[i];
	}
	//cout<<sum<<endl;
	for(int i=0;i<num_polyg;i++) proj[i] /= sum;
}

void choose_parameters_for_approx_poly_dp(std::vector<cv::Point> &curve, int &iter, double &estart, double &estep)
{
	double perimeter = cv::arcLength(curve,true);
	perimeter=curve.size();
	//cout<<perimeter<<endl;
	iter = 20;
	estep = 0.001 * perimeter;
	estart = 0.04 * perimeter;
	/* for the time being this function works statically */
}


void project_shape_to_polygons(std::vector<cv::Point> &contour, double * proj, int num_polyg, int mode)
{
	double estart, estep;
	int iter;
	choose_parameters_for_approx_poly_dp(contour,iter,estart,estep);
	iter_approx_poly_dp_curve(contour,proj,num_polyg,iter,estart,estep,0);
	//for(int i=0;i<5;i++) cout<<"p "<<proj[i]<<endl;
	normalise_projections(proj,num_polyg,mode);
}

PolygonProjection project_shape_to_polygons(std::vector<cv::Point> & contour, int mode)
{
	PolygonProjection ret;
	project_shape_to_polygons(contour,ret.proj,5,mode);
	return ret;
}

void print_polyg(PolygonProjection p)
{
	cout<<endl;
	for(int i=0;i<5;i++) cout<<p.proj[i]<<" ";
	cout<<endl<<endl;
}




















