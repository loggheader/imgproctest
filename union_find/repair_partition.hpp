#ifndef header_check_closed_contour_hpp
#	define header_check_closed_contour_hpp

# 	include <opencv2/opencv.hpp>
# 	include <vector>
#   include <cassert>
/******************* define constants ****************/
#	define OFFSET_AROUND 4
#	define HALF_OFFSET   OFFSET_AROUND/2
#	define UNION_DEPTH   2

/******************* API function ********************/


/*********functions for playing around with boolean arrays************/
cv::Rect make_boolean_array_out_of_ROI(std::vector<cv::Point> &contour, std::vector<std::vector<bool> > &array);
void print_points_to_boolean(std::vector<cv::Point> &points, cv::Point offset, std::vector<std::vector<bool> > &array, bool value);
void fill_single_gaps(std::vector<std::vector<bool> > &array, std::vector<cv::Point> &contour,cv::Point offset);
bool boolean_or_of_neigh_only_no_check_boundary(std::vector<std::vector<bool> > &array, cv::Point point);
bool set_contains_zero(std::vector<cv::Point> &points);
bool is_gap_size3_kenrel(std::vector<std::vector<bool> > &array, int i, int j);
int find_index_of_zero_point(std::vector< std::vector < cv::Point> > &contours);





/***********   segmentation functions **************/
void return_contour_subset_surrounding_region(std::vector< cv::Point > &contour, 
											std::vector< cv::Point > &output,
											std::vector< cv::Point > &area,
											std::vector< std::vector<bool> > &array,
											cv::Point  offset);

void segment_contour_to_subsets(std::vector< cv::Point > &contour,	std::vector< std::vector< cv::Point > > &output); 


/************************old***********************/
/*

int is_contour_closed(std::vector<cv::Point> &contour);
void fix_2contour(std::vector<cv::Point> &contour);
*/

#endif