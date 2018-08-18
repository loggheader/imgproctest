#include "SimpleRectGui.hpp"
using namespace std;
using namespace cv;

/********************** a small helping function *********************/

SimpleRectGui * SimpleRectGui::ptr = NULL;

void paint_rect(cv::Mat &win_img, cv::Rect &curent_rect, Scalar color)
{
	rectangle(win_img,Point(curent_rect.x,curent_rect.y),Point(curent_rect.x+curent_rect.width, curent_rect.y+curent_rect.height), color);
}

/*********************** class functions **************************/
void SimpleRectGui::set_image_and_window_name(cv::Mat & _img, std::string _winName)
{
	img     = & _img;
	winName = _winName;
	ptr = this;
	reset();
	namedWindow( winName, WINDOW_AUTOSIZE);
	setMouseCallback( winName, SimpleRectGui::on_mouse, 0 );
	
}

void SimpleRectGui::show_image()
{
	win_img = img->clone();
	for(Point p : point_vect){
		win_img.at<Vec3b>(p.y,p.x) = Vec3b(0,0,255);
	}
	for(Rect r  : rect_vect){
		paint_rect(win_img,r,Scalar(0,255,0));
	}
	if(rect_chosen == false){
		if(point_chosen == true){
			win_img.at<Vec3b>(curr_point.y,curr_point.x) = Vec3b(0,0,255);
			curr_rect = rect_containing_point(curr_point, img->size(), desired_size, POINT_MID);
			paint_rect(win_img,curr_rect,Scalar(0,255,255));
		}
	}
	imshow(winName,win_img);
}


void SimpleRectGui::handle_keyboard_input(char c)
{
	if(c == '\x1b') is_done = true;
	if(c == 'r') reset();
	if(is_done == true) return;
	if(point_chosen == true){
		if(c == 'w') incw();
		else if(c == 'd') decw();
		else if(c == 'h') inch();
		else if(c == 'j') dech();
		else if(c == 'n') store();
	}
	if(c == 'u') undo();
}

void SimpleRectGui::handle_mouse_click( int event, int x, int y, int flags, void* param )
{
	if(event ==  cv::EVENT_LBUTTONDOWN && point_chosen == false && !is_done){
		point_chosen = true;
		curr_point = Point(x,y);
	}
	if(event == cv::EVENT_MOUSEWHEEL && !is_done) {
		incw(); inch();
	}
}



void SimpleRectGui::autowork()
{
	do{
		show_image();
		char c = (char) waitKey(50);
		handle_keyboard_input(c);
	}while(is_done == false);
}


bool SimpleRectGui::done() const
{
	return is_done;
}

void SimpleRectGui::help() const
{
	return;
}

void SimpleRectGui::reset()
{
	point_chosen = false;
	rect_chosen  = false;
	is_done		 = false;
	point_vect.clear();
	rect_vect.clear();
	desired_size = Size(25,25);
}

void SimpleRectGui::undo()
{
	if(point_chosen == true){
		point_chosen = false;
		desired_size = Size(25,25);
	}
	else{
		if(point_vect.size() == 0) return ;
		else{
			curr_point = point_vect.back();
			curr_rect  = rect_vect.back();
			point_chosen = true;
			point_vect.pop_back();
			rect_vect.pop_back();
		}
	}
}

void SimpleRectGui::store()
{
	point_chosen = false;
	curr_rect = rect_containing_point(curr_point, img->size(), desired_size, POINT_MID);
	rect_vect.push_back(curr_rect);
	point_vect.push_back(curr_point);
	desired_size = Size(25,25);
}

void SimpleRectGui::incw()
{
	desired_size.width += 4;
}

void SimpleRectGui::decw()
{
	desired_size.width -= 4;
}

void SimpleRectGui::inch()
{
	desired_size.height += 4;
}

void SimpleRectGui::dech()
{
	desired_size.height -= 4;
}

std::vector<cv::Point> SimpleRectGui::get_points()
{
	return point_vect;
}

std::vector<cv::Rect>  SimpleRectGui::get_rects()
{
	return rect_vect;
}
	
cv::Point SimpleRectGui::get_last_point()
{
	return point_vect.size() > 0? point_vect.back():Point(-1,-1);
}

cv::Rect  SimpleRectGui::get_last_rect()
{
	return rect_vect.size() > 0 ? rect_vect.back() : Rect(0,0,0,0);
}


