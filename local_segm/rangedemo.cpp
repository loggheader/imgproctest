#include "color_space.hpp"
#include "rect_op.hpp"
#include <vector>
#include <cstdio>
#include <cstdint>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>

;

using namespace std;
using namespace cv;

#define SHOW(x,y) {imshow(x,y); waitKey(0); destroyAllWindows();}

void help(void)
{
	printf("Usage:\n"
			"./rangedemo [img name] [column] [row] [p1] [p2] [p3] [bgr / hsv] (out file name , optional)\n"
		);
	exit(0);
}




int main(int argc, char **argv)
{
	if(argc != 8 && argc != 9) help();
	Mat img = imread(argv[1]);
	cout<<"here"<<endl;
	Mat outp(img.size(),CV_8UC1,Scalar(0));
	cout<<"there"<<endl;
	int col = atoi(argv[2]);
	int row = atoi(argv[3]);
	int p1  = atoi(argv[4]);
	int p2  = atoi(argv[5]);
	int p3  = atoi(argv[6]);
	string cspace = string(argv[7]);
	if(cspace != "bgr" && cspace != "hsv") help();
	Vec3b tolerance(p1,p2,p3);
	Point point(col,row);
	Rect rect = in_range_rect_around_point(img,outp,point,Size(100,100),tolerance,cspace == "bgr"?COLOR_BGR : COLOR_HSV);
	img.at<Vec3b>(row,col) = Vec3b(255,255,255);
	SHOW("original",img);
	SHOW("part",img(rect));
	SHOW("output",outp);
	if(argc == 9) imwrite(string(argv[8]), outp);
}


