#include<iostream>
#include<opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include<opencv2/stitching.hpp>
using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

//1、使用特征检测算法找到两张图像中相似的点，计算变换矩阵
//2、将图像right透视变换后得到的图片与图像left拼接


//图像融合，消除拼接缝
bool OptimizeSeam(int start_x, int end_x, Mat& WarpImg, Mat& DstImg)
{
	double Width = (end_x - start_x);//重叠区域的宽度  

	//图像加权融合，通过改变alpha修改DstImg与WarpImg像素权重，达到融合效果
	double alpha = 1.0;
	for (int i = 0; i < DstImg.rows; i++)
	{
		for (int j = start_x; j < end_x; j++)
		{
			for (int c = 0; c < 3; c++)
			{
				//如果图像WarpImg像素为0，则完全拷贝DstImg
				if (WarpImg.at<Vec3b>(i, j)[c] == 0)
				{
					alpha = 1.0;
				}
				else
				{
					double l = Width - (j - start_x); //重叠区域中某一像素点到拼接缝的距离
					alpha = l / Width;
				}
				DstImg.at<Vec3b>(i, j)[c] = DstImg.at<Vec3b>(i, j)[c] * alpha + WarpImg.at<Vec3b>(i, j)[c] * (1.0 - alpha);
			}
		}
	}

	return true;
}


bool Image_Stitching(Mat image_left, Mat image_right, Mat & WarpImg, Mat &DstImg, bool draw)
{
	//创建SURF特征检测器
	int Hessian = 800;
	Ptr<SURF>detector = SURF::create(Hessian);

	//进行图像特征检测、特征描述
	vector<KeyPoint>keypoint_left, keypoint_right;
	Mat descriptor_left, descriptor_right;
	detector->detectAndCompute(image_left, Mat(), keypoint_left, descriptor_left);
	detector->detectAndCompute(image_right, Mat(), keypoint_right, descriptor_right);
	
	//使用FLANN算法进行特征描述子的匹配
	FlannBasedMatcher matcher;
	vector<DMatch>matches;
	matcher.match(descriptor_left, descriptor_right, matches);

	double Max = 0.0;
	for (int i = 0; i < matches.size(); i++)
	{
		//float distance –>代表这一对匹配的特征点描述符（本质是向量）的欧氏距离，数值越小也就说明两个特征点越相像。
		double dis = matches[i].distance;
		if (dis > Max)
		{
			Max = dis;
		}
	}

	//筛选出匹配程度高的关键点
	vector<DMatch>goodmatches;
	vector<Point2f>goodkeypoint_left, goodkeypoint_right;
	for (int i = 0; i < matches.size(); i++)
	{
		double dis = matches[i].distance;
		if (dis < 0.15*Max)
		{
			/*
			以右图做透视变换
			左图->queryIdx:查询点索引（查询图像）
			右图->trainIdx:被查询点索引（目标图像）
			*/
			//注：对image_right图像做透视变换，故goodkeypoint_left对应queryIdx，goodkeypoint_right对应trainIdx
			//int queryIdx –>是测试图像的特征点描述符（descriptor）的下标，同时也是描述符对应特征点（keypoint)的下标。
			goodkeypoint_left.push_back(keypoint_left[matches[i].queryIdx].pt);
			//int trainIdx –> 是样本图像的特征点描述符的下标，同样也是相应的特征点的下标。
			goodkeypoint_right.push_back(keypoint_right[matches[i].trainIdx].pt);
			goodmatches.push_back(matches[i]);
		}
	}

	//绘制特征点
	if (draw)
	{
		Mat result;
		drawMatches(image_left, keypoint_left, image_right, keypoint_right, goodmatches, result);
		imshow("特征匹配", result);

		Mat temp_left = image_left.clone();
		for (int i = 0; i < goodkeypoint_left.size(); i++)
		{
			circle(temp_left, goodkeypoint_left[i], 3, Scalar(0, 255, 0), -1);
		}
		imshow("goodkeypoint_left", temp_left);

		Mat temp_right = image_right.clone();
		for (int i = 0; i < goodkeypoint_right.size(); i++)
		{
			circle(temp_right, goodkeypoint_right[i], 3, Scalar(0, 255, 0), -1);
		}
		imshow("goodkeypoint_right", temp_right);
	}

	//findHomography计算单应性矩阵至少需要4个点
	/*
	计算多个二维点对之间的最优单映射变换矩阵H（3x3），使用MSE或RANSAC方法，找到两平面之间的变换矩阵
	*/
	if (goodkeypoint_left.size() < 4 || goodkeypoint_right.size() < 4) return false;


	//获取图像right到图像left的投影映射矩阵，尺寸为3*3
	//注意顺序，srcPoints对应goodkeypoint_right，dstPoints对应goodkeypoint_left
	Mat H = findHomography(goodkeypoint_right, goodkeypoint_left, RANSAC);

	//对image_right进行透视变换
	warpPerspective(image_right, WarpImg, H, Size(image_right.cols + image_left.cols, image_right.rows));

	namedWindow("透视变换", WINDOW_NORMAL);
	imshow("透视变换", WarpImg);

	DstImg = WarpImg.clone();
	//将image_left拷贝到透视变换后的图片上，完成图像拼接
	image_left.copyTo(DstImg(Rect(0, 0, image_left.cols, image_left.rows)));
	namedWindow("图像全景拼接", WINDOW_NORMAL);
	imshow("图像全景拼接", DstImg);

	//透视变换左上角(0,0,1)
	Mat V2 = (Mat_<double>(3, 1) << 0.0, 0.0, 1.0);
	Mat V1 = H * V2;
	Point left_top;
	left_top.x = V1.at<double>(0, 0) / V1.at<double>(2, 0);
	left_top.y = V1.at<double>(0, 1) / V1.at<double>(2, 0);
	if (left_top.x < 0)left_top.x = 0;

	//透视变换左下角(0,src.rows,1)
	V2 = (Mat_<double>(3, 1) << 0.0, image_left.rows, 1.0);
	V1 = H * V2;
	Point left_bottom;
	left_bottom.x = V1.at<double>(0, 0) / V1.at<double>(2, 0);
	left_bottom.y = V1.at<double>(0, 1) / V1.at<double>(2, 0);
	if (left_bottom.x < 0)left_bottom.x = 0;

	int start_x = min(left_top.x, left_bottom.x);//重合区域起点
	int end_x = image_left.cols;//重合区域终点
	
	OptimizeSeam(start_x, end_x, WarpImg, DstImg); //图像融合

	namedWindow("图像融合", WINDOW_NORMAL);
	imshow("图像融合", DstImg);


	return true;
}


bool OpenCV_Stitching(Mat image_left, Mat image_right)
{
	//将待拼接图片放进容器里面
	vector<Mat>images;
	images.push_back(image_left);
	images.push_back(image_right);

	//创建Stitcher模型
	Ptr<Stitcher>stitcher = Stitcher::create();

	Mat result;
	Stitcher::Status status = stitcher->stitch(images, result);// 使用stitch函数进行拼接

	if (status != Stitcher::OK) return false;

	imshow("OpenCV图像全景拼接", result);

	return true;
}

int main()
{

	Mat image_left = imread("../left.jpg");
	Mat image_right = imread("../right.jpg");
	if (image_left.empty() || image_right.empty())
	{
		cout << "No Image!" << endl;
		system("pause");
		return -1;
	}

	Mat WarpImg, DstImg;
	if (!Image_Stitching(image_left, image_right, WarpImg, DstImg, false))
	{
		cout << "can not stitching the image!" << endl;
		system("pause");
		return false;
	}


	if (!OpenCV_Stitching(image_left, image_right))
	{
		cout << "can not stitching the image!" << endl;
		system("pause");
		return false;
	}

	waitKey(0);
	destroyAllWindows();
	system("pause");
	return 0;
}
