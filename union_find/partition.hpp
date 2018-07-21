#ifndef header_partition_image_hpp
#	define header_partition_image_hpp
#	include <opencv2/opencv.hpp>
#	include <vector>


/****************** Some constants that may be useful ****************/
#define ZERO_UPPER_LIMIT  200

/****************** functions to be used in code *********************/
void partition_image_to_black_and_white_sets(cv::Mat &img, std::vector<std::vector<cv::Point> > &set, bool write_black, bool write_white);


bool is_black(const cv::Vec3b);
bool is_white(const cv::Vec3b);

/******************* help functions for implementation ***************/
void binary_image_to_boolean_array ( cv::Mat &img, std::vector< std::vector<bool> > &barray);
void partition_boolean_array_to_black_and_white_sets(std::vector< std::vector<bool> > &input, 
													 std::vector< std::vector< cv::Point> > &sets, 
													 bool write_black, bool write_white);

bool cmp_pair_root_point_by_root(const std::pair<int, cv::Point> &a, const std::pair<int, cv::Point> &b);
bool cmp_set_size (const std::vector< cv::Point> &a, const std::vector<cv::Point> &b);
/**************** though they can still be used in code ************/



#endif