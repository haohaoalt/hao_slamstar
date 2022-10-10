/*
 * @Author: zhanghao
 * @Date: 2022-10-10 19:16:31
 * @LastEditTime: 2022-10-10 19:16:31
 * @FilePath: /hao_slamstar/03HW/todo/main.cpp
 * @Description: 
 */
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    vector<Point2i> vec = {{2, 1}, {3, 3}, {2, 3}, {3, 2}, {3, 1}, {1, 3}, {1, 1}, {2, 2}, {1, 2}};

    cout << "Before sort: " << endl;
    for (auto pt : vec)
    {
        cout << pt << endl;
    }

    sort(vec.begin(), vec.end(), [](Point2i &pt1, Point2i &pt2)
         { return (pt1.x != pt2.x) ? (pt1.x < pt2.x) : (pt1.y < pt2.y); });

    cout << "After sort: " << endl;
    for (auto pt : vec)
    {
        cout << pt << endl;
    }
    return 0;
}