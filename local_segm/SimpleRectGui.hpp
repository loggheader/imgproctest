#ifndef header_SimpleRectGui_hpp
#	define header_SimpleRectGui_hpp


#	include <opencv2/opencv.hpp>
#	include "rect_op.hpp"
#	include <vector>



class SimpleRectGui{
public:
	static SimpleRectGui * ptr;
	static void on_mouse( int event, int x, int y, int flags, void* param )
	{
		SimpleRectGui::ptr->handle_mouse_click(event,x,y,flags,param);
	}
	void set_image_and_window_name(cv::Mat & _img,  std::string _winName);
	void show_image();
	void handle_keyboard_input(char c);
	void handle_mouse_click( int event, int x, int y, int flags, void* param );
	void autowork();
    bool done() const;
	void help() const;
	void reset();
	void undo();
	std::vector<cv::Point> get_points();
	std::vector<cv::Rect>  get_rects();
	cv::Point get_last_point();
	cv::Rect  get_last_rect();
protected:
	void incw();
	void inch();
	void decw();
	void dech();
	void store();
	cv::Mat  *  img;
	cv::Mat win_img;
	std::string winName;
	std::vector<cv::Point> point_vect;
	std::vector<cv::Rect>  rect_vect;
	bool point_chosen = false;
	bool rect_chosen = false;
	bool is_done = false;
	cv::Rect curr_rect;
	cv::Size desired_size;
	cv::Point curr_point;
};











#endif










