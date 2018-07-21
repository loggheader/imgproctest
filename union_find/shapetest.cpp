#include "partition.hpp"
#include "color_img.hpp"
#include "repair_partition.hpp"
#include <vector>
#include <cstdio>
#include <iostream>


using namespace std;
using namespace cv;

/********************* some define's ****************/
#define CUTOFF 50
#	define WAIT  cv::waitKey(0); \
				 cv::destroyAllWindows();
#define F4
/********************* actual code *****************/

void dowork(cv::Mat &img, cv::Mat &img2 ,int choice)
{
	vector<vector<Point> > sets;
	vector<vector< bool> > barray;
	binary_image_to_boolean_array(img,barray);
    partition_boolean_array_to_black_and_white_sets(barray,sets,false,true); // write black then write white...   
    for(int i=0;i<sets.size();i++){
    	Mat img3=img.clone();
    	color_points(img3,sets[i],cv::Vec3b(0,250,0));
    	cout<<"original area is " << contourArea(sets[i]) <<endl;
  //  	cout<<"original naoume is "<<is_contour_closed(sets[i])<<endl;
    	cv::imshow("oime",img3);
    	waitKey(0);
    	destroyAllWindows();
    	color_points(img3,sets[i],cv::Vec3b(0,0,0));
    	vector<vector<Point> > hullset;
    	hullset.resize(1);
    	cv::convexHull(sets[i],hullset[0]);
    	cout<<"after testing for match we have"<<endl;
    	cout<<matchShapes(hullset[0],sets[i],CV_CONTOURS_MATCH_I1,0)<<endl;
    	cout<<matchShapes(hullset[0],sets[i],CV_CONTOURS_MATCH_I2,0)<<endl;
    	cout<<matchShapes(hullset[0],sets[i],CV_CONTOURS_MATCH_I3,0)<<endl;
		cout<<"new area is " << contourArea(hullset[0]) <<endl;    	
//		cout<<"naoume is "<<is_contour_closed(hullset[0])<<endl<<endl<<endl;   //this is wrong!!!!!!!!!!!!!!!!!!!!!
    	drawContours(img3,hullset,0,cv::Vec3b(250,0,0));
    	cv::imshow("oime-nope",img3);
    	waitKey(0);
    	destroyAllWindows();    	
    }
    //color_rect(img2,rect,cv::Vec3b(0,250,0));
       
}

int get_numb_from_string(char *str)
{
	int temp=0;
	sscanf(str,"%d",&temp);
	return temp;
}


void dowork2(Mat &img)
{
	Mat img2 = img.clone();
	vector<vector<Point> > contours,hullset;
	hullset.resize(1);
	cv::cvtColor(img,img,CV_BGR2GRAY);
	threshold(img, img, 200, 255,0);
	findContours( img, contours,  CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
	sort(contours.begin(),contours.end(),cmp_set_size);
	for(vector<Point> temp : contours){
		//cout << temp<<endl;
		cout<<temp.size()<<endl;
		cout<<"original area "<<cv::contourArea(temp)<<endl;
		Mat img3 = img2.clone();
		drawContours(img3,vector<vector<Point> > (1,temp),0,cv::Vec3b(250,0,0));

		//color_points(img3,temp, cv::Vec3b(250,0,0));;
		cv::imshow("naoume",img3);
		cv::waitKey(0);
		cv::destroyAllWindows();





		img3=img2.clone();
	
		convexHull(temp,hullset[0]);
		cout<<"after convexhull "<<cv::contourArea(hullset[0])<<endl<<endl;
		drawContours(img3,hullset,0,cv::Vec3b(0,250,0));
		cv::imshow("hhh",img3);
		cv::waitKey(0); cv::destroyAllWindows();
	}
}


void remove_open_contours_test(Mat &img);
void image_after_segmenting_closed_contours(cv::Mat &img);




int main(int argc, char **argv)
{
	
    //int choice = get_numb_from_string(argv[2]);
//	int low =get_numb_from_string(argv[3]);
//	int hig =get_numb_from_string(argv[4]);
	cv::Mat img = cv::imread(argv[1]);
	cv::Mat img2 = img.clone();
	//cv::cvtColor(img,img,CV_BGR2GRAY);
	//cv::Canny(img,img,low,hig,3);

/*
#ifdef F1
	dowork(img,img2,choice);
#endif

#ifdef F2
	dowork2(img);
#endif

#ifdef F3
	remove_open_contours_test(img);
#endif
*/

	/* if(choice == 1) dowork(img,img2,choice);
	else if (choice == 2) dowork2(img);
//	else if(choice == 3) remove_open_contours_test(img);
	else if(choice == 4) */
	image_after_segmenting_closed_contours(img);
}



/*
void remove_open_contours_test(cv::Mat &img)
{
	vector< vector<Point> > sets;
	vector<vector<bool> > array;
	partition_image_to_black_and_white_sets(img,sets,false,true);
	img = Scalar::all(0);
	cv::Mat img2 = img.clone();
	for(int i=0;i<sets.size();i++){
		int check_index = is_contour_closed(sets[i]);
		if(check_index == 2) {
			color_points(img2,sets[i],cv::Vec3b(255,0,0));
			fix_2contour(sets[i]);
			color_points(img,sets[i],cv::Vec3b(0,0,255));
			//cout << "yeah";
		}
	}
	cv::imshow("after removing everything that seems open",img2);
	WAIT
	cv::imshow("after removing everything that seems open",img);
	WAIT
	


}
*/


void image_after_segmenting_closed_contours(cv::Mat &img)
{
	Mat img2 = img.clone();
	img2 = Scalar::all(0);
	vector<vector<Point> > sets, result;
	partition_image_to_black_and_white_sets(img,sets,false,true);	
	for(int i=0;i<sets.size();i++){
		segment_contour_to_subsets(sets[i],result);
	}
	cout<<"here"<<endl;
	for(int i=0;i<result.size();i++){
		color_points(img2,result[i],cv::Vec3b(255,255,255));
	}
	imshow("lets test this",img2);
	WAIT
	partition_image_to_black_and_white_sets(img2,sets,true,false);
	for(int i=1; i<sets.size();i++){
		if(sets[i].size() > CUTOFF || true) color_points(img,sets[i],Vec3b(255,0,0));
	}
	imshow("finally painting original image",img);
	WAIT

}





