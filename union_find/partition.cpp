#include <opencv2/opencv.hpp>
#include "partition.hpp"
#include "UnionFind2D.hpp"
#include <algorithm>
#include <vector>
using namespace std;
using namespace cv;


bool is_black(const cv::Vec3b input)
{
	return input[0] < ZERO_UPPER_LIMIT;
}

bool is_white(const cv::Vec3b input)
{
	return input[0] >= ZERO_UPPER_LIMIT;
}


bool cmp_pair_root_point_by_root(const std::pair<int, cv::Point> &a, const std::pair<int, cv::Point> &b)
{
	return a.first < b.first;
}

bool cmp_set_size (const std::vector< cv::Point> &a, const std::vector<cv::Point> &b)
{
	return a.size() > b.size();
}

void binary_image_to_boolean_array ( cv::Mat &img, std::vector< std::vector<bool> > &barray)
{
	barray.clear();
    int num_row = img.size().height;
    int num_col = img.size().width;
    barray.resize(num_row);
    for(int i=0;i<num_row;i++) barray[i].resize(num_col);
   	for(int i=0;i<num_row;i++){
   		for(int j=0;j<num_col;j++){
   			if(is_black(img.at<Vec3b>(i,j))) barray[i][j]=false; //black pixel
   			else barray[i][j]=true; //white pixel
   		}
   	}
}





void partition_boolean_array_to_black_and_white_sets(std::vector< std::vector<bool> > &input, 
													 std::vector< std::vector< cv::Point> > &sets, 
													 bool write_black, bool write_white)
{
	int white_count = 0, black_count = 0;
	int num_row = input.size();
	int num_col = input[0].size();
	UnionFind2D unionfind2d (num_row,num_col);
	for(int i=0;i<num_row;i++){
		for(int j=0;j<num_col;j++){
			if(write_black == true && input[i][j] == false){
				black_count++;
				if((i != num_row - 1) && input[i+1][j] == false) unionfind2d.unite(i,j,i+1,j);
				if((j != num_col - 1) && input[i][j+1] == false) unionfind2d.unite(i,j,i,j+1);
			}
			else if(write_white == true && input[i][j] == true){
				white_count++;
				if((i != num_row - 1) && input[i+1][j]) unionfind2d.unite(i,j,i+1,j);
				if((j != num_col - 1) && input[i][j+1]) unionfind2d.unite(i,j,i,j+1);
				if((i != num_row - 1) && (j != num_col -1) && input[i+1][j+1]) unionfind2d.unite(i,j,i+1,j+1);
				if((i != 0) && (j != num_col -1) && input[i-1][j+1]) unionfind2d.unite(i,j,i-1,j+1);
			}
		}
	}
	sets.clear();
	vector< pair< int, Point> > temp; int tempcounter=0;
	temp.resize(white_count + black_count); // if write_white is false white_count will be zero
	for(int i=0; i<num_row ;i++){
		for(int j=0;j<num_col;j++){
			if( (input[i][j] == true && write_white == true) || (input[i][j] == false && write_black == true) ){
				temp[tempcounter].first = unionfind2d.root(i,j);
				temp[tempcounter++].second = Point(j,i); // CAREFUL, Point stores data in a (column, row) format
			}
		}
	}
	sort(temp.begin(),temp.end(),cmp_pair_root_point_by_root);
	int current_root=-1;
	for(int i=0;i<temp.size();i++){
		int root = temp[i].first;
		if(root != current_root){
			sets.push_back(vector<Point>() );
			current_root = root;
		}
		sets.back().push_back(temp[i].second);
		//if(temp[i].second.x == 0 && temp[i].second.y == 0) cout<<"oime"<<endl;
		//cout<<temp[i].second.x << "  inside sets part "<<temp[i].second.y<<endl;
		//cout<<temp[i].second<<endl;
	}
	for(int i=0;i<sets.size();i++){
		//if(sets[i].size() >= 19000) cout<<sets[i];
	}
	sort(sets.begin(),sets.end(),cmp_set_size);
	//cout<<tempcounter<<endl;
	//cout<< input.size() << " "<<input[0].size()<<endl;
}

#include <iostream>

void partition_image_to_black_and_white_sets(cv::Mat &img, std::vector<std::vector<cv::Point> > &set, bool write_black, bool write_white)
{
	vector< vector<bool> > array;
	binary_image_to_boolean_array(img,array);
	partition_boolean_array_to_black_and_white_sets(array,set,write_black,write_white);
}














