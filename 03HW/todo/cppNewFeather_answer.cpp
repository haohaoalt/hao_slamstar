/****************************
* ��Ŀ����ʹ��C++�����Ը������º������ú������ܣ���һ����������갴�ա�Z���������򣬲������
*
* ������ѧϰĿ�꣺
* ��ϤC++�����ԣ�ѭ�����Զ������Ƶ����б��ʼ����lambda������
*
* ���ߣ����ںţ�������Ӿ�life�������ڹ��ں�����֪ʶ���򣺴��㿪ʼѧϰSLAM
* ʱ�䣺2018.09
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

	// ����1
	sort(vec.begin(), vec.end(), [=](Point2i pt1, Point2i pt2)->bool{ if (pt1.x != pt2.x){ return (pt1.x < pt2.x); } if (pt1.y != pt2.y){ return (pt1.y < pt2.y); } });

	// ����2
	//sort(vec.begin(), vec.end(), cmp);

	cout << "After sort: " << endl;
	for (auto p : vec){
		cout << p << endl;
	}

	return 0;
}




