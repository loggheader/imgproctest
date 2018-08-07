#ifndef header_polygon_projection_hpp
#	define header_polygon_projection_hpp

#	include <opencv2/opencv.hpp>
#	include <vector>

/*
	This header file includes function and macro definitions that will be used in the 
	polygon projection approach. 
	
	To elaborate more, the key concept is to try to classify various shapes to polygons
	with 3,4,5,... vertices. This can be achieved by means of the OpenCV's approxPolyDP
	function. For more information on that function, you may refer here

		https://docs.opencv.org/2.4/modules/imgproc/doc/structural_analysis_and_shape_descriptors.html

	Nonetheless, we face 2 main problems. Firstly, the output of approxPolyDP depends 
	heavily on the value of the epsilon parameter. As a result, a choice of parameter
	yeilding excellent results for a particular shape, can produce unsatisfactory results
	when used for a shape that is smaller. Secondly, as the shapes are not polygons and 
	in some cases dont really have clear "edges", there can be cases where classifying
	them into a one category or the other might not seem meaningfull. A possible solution
	is to iterate over a set of different suitable epsilon values and do some sort of 
	frequency analysis on the output of approxPolyDP to "project" the shape	to polygons
	with a varying number of vertices. This enables us to have for instance shapes 
	classified as 50% 4-polygon and 50% 5-polygon, hopefully mitagating the errors and 
	information loss due to "gray" areas.

	The projection coefficients can be stored in a double array and can reach as high 
	polygon dimensions as necassary. However, since it seems unlikely to clssify shapes 
	with more than 7 vertices, structures and functions will be provided for projecting
	to polygons to polygons with up to 7 vertices.
*/


/*
	The first step is to iterate over various epsilon values and count how many times
	we get each result. We could further assign weights for each epsilon value and the
	following macro's are to that end.
*/

#	define APPROX_POLY_CONSTANT 		0
#	define APPROX_POLY_LINEAR   		1
#	define APPROX_POLY_LINEAR_ABS   	2
#	define APPROX_POLY_QUADRATIC    	3
#	define APPROX_POLY_QUADRATIC_ABS	4
#	define APPROX_POLY_GAUSSIAN			5

/* For the time being these macro's have no affect */

void partition_contour_to_curve(std::vector<cv::Point> & contour, std::vector<cv::Point> &curve);

void iter_approx_poly_dp_curve(std::vector<cv::Point> &curve, double * proj, int num_polyg, int iter, double estart, double estep, int mode = 0);
void choose_parameters_for_approx_poly_dp(std::vector<cv::Point> &curve, int &iter, double &estart, double &estep);



#	define NORM_LINEAR 		0
#	define NORM_QUADRATIC	1

void normalise_projections(double *proj, int num_polyg, int mode = NORM_LINEAR);





/*** a data structure *****/
struct PolygonProjection{
	double proj[5];
};


/********************************* API intended functions *********************************************/
void project_shape_to_polygons(std::vector<cv::Point> &contour, double * proj, int num_polyg, int mode = 0);
void print_polyg(PolygonProjection p);
PolygonProjection project_shape_to_polygons(std::vector<cv::Point> & contour, int mode = 0);











#endif