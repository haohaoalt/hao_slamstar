/**
 * @author yft
 * @date 2020-4-4
 * @descp  两点p, q 的叉乘 可以表示 过两点的直线l，即 l = p x q
 *         齐次坐标： 在原有坐标上添加一个维度
 *         优点： 表达点(x,y)在线(a,b,c;ax+by+c=0)上           点的齐次坐标与线的内积等于0
 *               表达点(x,y,z)在面(a,b,c,d;ax+by+cz+d=0)上    点的齐次坐标与面的内积等于0
 *               表达直线与直线的交点，平面与平面的交点
 *               表达两点构成线
 *               向量和点的齐次坐标表达
 *               无穷远点(点的齐次坐标的最后一个元素为0)
 *               欧式空间变换
 *
 */

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
    Point2f p(150,80);
    Point2f q(120,35);

    //转化为齐次坐标
    Point3f pt1(p.x,p.y,1);
    Point3f pt2(q.x,q.y,1);

    //两个点的齐次坐标叉乘
    Point3f l;
    l = pt1.cross(pt2);

    cout << "直线方程：" << endl;
    cout << "(" << l.x << ")x+(" << l.y << ")y+(" << l.z << ")=0;" << endl;

    cout << "将点p,g代入直线方程中得到:" << endl;
    cout << "\t\t\t" << pt1.dot(l) << endl;
    cout << "\t\t\t" << pt2.dot(l) << endl;

    Mat image(200,200,CV_8U,Scalar(0));

    //绘制直线
    for(int y = 0; y < image.rows ; y++)
    {
        uchar* p_row = image.ptr<uchar>(y);
        for(int x = 0; x < image.cols ; x++)
        {
           if(abs(l.x * x + l.y * y + l.z)<0.0000001)
           {
               p_row[x] = 255;
               cout << "(" << x << "," << y << ")" << endl;
           }
        }
    }
    //绘制点p,q
    circle(image,p,3,255,2);
    circle(image,q,3,255,2);
    imshow("显示直线",image);
    waitKey();
}