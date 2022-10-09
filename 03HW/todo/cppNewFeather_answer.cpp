/****************************
* 题目：请使用C++新特性改下以下函数。该函数功能：将一组无序的坐标按照“Z”字形排序，并输出。
*
* 本程序学习目标：
* 熟悉C++新特性（循环、自动类型推导、列表初始化、lambda函数）
*
* 作者：公众号：计算机视觉life。发布于公众号旗下知识星球：从零开始学习SLAM
* 时间：2018.09
****************************/


#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

bool cmp(Point2i pt1, Point2i pt2){
	if (pt1.x != pt2.x){
		return (pt1.x < pt2.x);
	}
	if (pt1.y != pt2.y){
		return (pt1.y < pt2.y);
	}
}
int main()
{
	vector<Point2i> vec{  Point2i(2, 1), Point2i(3, 3), Point2i(2, 3), Point2i(3, 2), Point2i(3, 1), Point2i(1, 3), Point2i(1, 1),Point2i(2, 2), Point2i(1, 2) };

	cout << "Before sort: " << endl;
	for (auto p : vec){
		cout << p << endl;
	}

	// 方法1
	sort(vec.begin(), vec.end(), [=](Point2i pt1, Point2i pt2)->bool{ if (pt1.x != pt2.x){ return (pt1.x < pt2.x); } if (pt1.y != pt2.y){ return (pt1.y < pt2.y); } });

	// 方法2
	//sort(vec.begin(), vec.end(), cmp);

	cout << "After sort: " << endl;
	for (auto p : vec){
		cout << p << endl;
	}

	return 0;
}




