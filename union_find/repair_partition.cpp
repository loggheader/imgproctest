#include "partition.hpp"
#include "repair_partition.hpp"
#include <cassert>
#include <vector>

using namespace std;
using namespace cv;

/******************************************* boolean playground **********************************/

void print_points_to_boolean(vector<Point> &points, cv::Point offset, vector<vector<bool> > &array, bool value)
{
	for(Point point : points){
		array[point.y + offset.y][point.x + offset.x] = value;
	}
}

bool boolean_or_of_neigh_only_no_check_boundary(vector<vector<bool> > &array, Point point)
{
	int row = point.y;
	int col = point.x;

	return (array[row-1][col-1] || array[row-1][col] || array[row-1][col+1] ||
		                array[row][col-1] || array[row][col+1] ||
		   array[row+1][col-1] || array[row+1][col] || array[row+1][col+1]) && (array[row][col] == false);
}

int find_index_of_zero_point(vector< vector < Point> > &contours)
{
	for(int i=0;i<contours.size();i++){
		for(int j=0;j<contours[i].size();j++){
			if(contours[i][j] == Point(0,0)) return i;
		}
	}
	return -1;
}

bool set_contains_zero(std::vector<cv::Point> &points)
{
	for (Point point : points) {
		if(point == Point(0,0)) return true;
	}
	return false;
}


bool is_gap_size3_kenrel(std::vector<std::vector<bool> > &array, int i, int j)
{
	if(array[i][j] == true) return false;
	/*int sum =0;
	for(int ii = i-1; ii<=i+1 ;ii++){
		for(int jj=j-1;jj<=j+1;jj++){
			sum += array[ii][jj];
		}
	}
	if(sum > 3) return false; */
	if(array[i][j-1]    && array[i][j+1])   return true; //horizontal
	if(array[i-1][j]    && array[i+1][j])   return true; //vertical
	if(array[i-1][j-1]  && array[i+1][j+1]) return true; //primary diag
	if(array[i+1][j-1]  && array[i-1][j+1]) return true; //second diag
	if(array[i-1][j-1] && array[i-1][j+1]) return true; // upper trig
	if(array[i+1][j-1]  && array[i+1][j+1]) return true; // down trig
	if(array[i-1][j-1]  && array[i+1][j-1]) return true; // left trig
	if(array[i-1][j+1]  && array[i+1][j+1]) return true; // right trig
	return false;
}


Rect make_boolean_array_out_of_ROI(std::vector<cv::Point> &contour, std::vector<std::vector<bool> > &array)
{
	array.clear();
	Rect rect = boundingRect(contour);
	array.resize(rect.height+OFFSET_AROUND);
	for(int i=0;i<array.size();i++) array[i].resize(rect.width+OFFSET_AROUND,false);
	for(Point point : contour){
		array[point.y - rect.y + OFFSET_AROUND/2][point.x - rect.x + OFFSET_AROUND/2] = true;
	}
	return rect;
}
void fill_single_gaps(std::vector<std::vector<bool> > &array, std::vector<cv::Point> &contour,cv::Point offset)
{
	int n=array.size(); int m=array[0].size();
	for(int i=HALF_OFFSET; i< n-HALF_OFFSET; i++){
		for(int j=HALF_OFFSET;j<m - HALF_OFFSET; j++){
			if(is_gap_size3_kenrel(array,i,j)) contour.push_back( Point(j,i) - offset);
		}
	}
	print_points_to_boolean(contour,offset,array,true);
}


/************************************************ segmentation functions ***************************************/
void return_contour_subset_surrounding_region(std::vector< cv::Point > &contour, 
											std::vector< cv::Point > &output,
											std::vector< cv::Point > &region,
											std::vector< std::vector<bool> > &array,
											cv::Point  offset)
{
	output.clear();
	//print_points_to_boolean(contour,offset,array,false);
	print_points_to_boolean(region,Point(0,0),array,true);
	for(int i=0;i<UNION_DEPTH;i++){
		print_points_to_boolean(output,offset,array,true);
		for(Point point : contour){
			if(boolean_or_of_neigh_only_no_check_boundary(array,point+offset)) output.push_back(point);
		}
	}
	print_points_to_boolean(output,offset,array,false);
	print_points_to_boolean(region,Point(0,0),array,false);

}


void segment_contour_to_subsets(std::vector< cv::Point > &contour,	std::vector< std::vector< cv::Point > > &output)
{
	vector<vector<bool> > array;
	Rect rect = make_boolean_array_out_of_ROI(contour,array);
	Point offset = Point(OFFSET_AROUND/2 - rect.x, OFFSET_AROUND/2 - rect.y);
	fill_single_gaps(array,contour,offset);
	vector<vector<Point> > set;
	partition_boolean_array_to_black_and_white_sets(array,set,true,false);
	print_points_to_boolean(contour,offset,array,false);
	for(int i=0;i<set.size();i++){
		if(set_contains_zero(set[i])) continue;
		output.push_back(vector<Point>());
		return_contour_subset_surrounding_region(contour,output.back(),set[i],array,offset);
	}

}











/* ************************************ old functions ***********************************
int is_contour_closed(vector<cv::Point> & contour)
{
	vector<vector<bool> > array;
	vector<vector<Point> > set;
	cv::Rect rect=cv::boundingRect(contour);
	make_boolean_array_out_of_ROI(contour,rect,array);
	partition_boolean_array_to_black_and_white_sets(array,set,true,false);
	return set.size();
}








void fix_2contour(std::vector<cv::Point> &contour)
{
	vector<vector<bool> >  array;
	vector<vector<Point> > set;
	vector<Point> fixed_contour;
	cv::Rect rect =  cv::boundingRect(contour);
	int xoffset = -rect.x + OFFSET_AROUND/2 ;
	int yoffset = -rect.y + OFFSET_AROUND/2 ;
	Point offset = Point(xoffset,yoffset);
	make_boolean_array_out_of_ROI(contour,rect,array);
	partition_boolean_array_to_black_and_white_sets(array,set,true,false);
	pair<int,int> position_of_zero = find_index_of_zero_point(set);
	assert(position_of_zero.first !=  -1);
	int id = (position_of_zero.first == 0)? 1:0;
	write_points_to_boolean_2d(contour,offset,array,false);
	write_points_to_boolean_2d(set[id],Point(0,0),array,true);
	for(int i=0;i<UNION_DEPTH;i++){
		write_points_to_boolean_2d(fixed_contour,offset,array,true);
		for(Point point : contour){
			if(boolean_or_of_neigh_only_no_check_boundary(array, point + offset)) fixed_contour.push_back(point);
		}
	}
	contour = fixed_contour;
}



*/






