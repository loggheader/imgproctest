#include "partition_sets.hpp"
#include <iostream>
#include <cstdio>
#include <vector>
#include <opencv2/opencv.hpp>
#include <cstring>
using namespace std;
using namespace cv;

bool cmp_vect_size(vector<pair<int,int> > a, vector<pair<int,int> > b)
{
	return a.size() > b.size();
}

bool is_black(Vec3b inp)
{
	return inp[0]<10;
}

void initialize_black_and_white_bool_array_from_image(cv::Mat &img,vector<vector<bool> > &vb)
{
	int nrow=img.size().height;
	int ncol=img.size().width;
	vb.resize(nrow);
	for(int i=0;i<nrow;i++) vb[i].resize(ncol);
	for(int i=0;i<nrow;i++){
		for(int j=0;j<ncol;j++){
			vb[i][j]=is_black(img.at<Vec3b>(i,j));
		}
	}
	cout<<"there"<<endl;
}

void partition_image_to_black_sets(cv::Mat &img, vector<vector< pair<int,int> > > & sets)
{
	vector<vector<bool> > vb;
	initialize_black_and_white_bool_array_from_image(img,vb);
	partition_to_sets(vb,sets);
}


void color_image_region(cv::Mat &img,vector<pair<int,int> > &points, int blue, int green, int red)
{
	for(auto point : points){
		img.at<Vec3b>(point.first,point.second)[0]=blue;
		img.at<Vec3b>(point.first,point.second)[1]=green;
		img.at<Vec3b>(point.first,point.second)[2]=red;
	}
}



void help(void)
{
	printf("Usage:\n"
			"shapetest [imagename]\n"
		);
}

int main(int argc, char **argv)
{
	if((argc != 2 ) || (argc == 2 && (strcmp(argv[1],"-h") == 0 || strcmp(argv[1],"-help") ==0) ) ){
		
			help();
			return 0;
		
	}
	cv::Mat img=cv::imread(argv[1]);
	vector<vector<pair<int,int> > > partitions;
	partition_image_to_black_sets(img,partitions);
	sort(partitions.begin(),partitions.end(),cmp_vect_size);
	int pick=0;
	cout<<"number of partitions is "<<partitions.size()<<endl<<"pick a number"<<endl;
	cv::Mat img2=img;
	while(true){
		cin>>pick;
		cout<<"you picked"<<pick<<endl;
		if(pick < 0) break;
		if(pick >= partitions.size()){
			cout<<"Error, too large pick\n";
			continue;
		}
		img2=img.clone();
		color_image_region(img2,partitions.at(pick),255,0,0);
		cv::imshow("imageee",img2);
		cv::waitKey(0);
		cv::destroyAllWindows();
	}
	return 0;
}














