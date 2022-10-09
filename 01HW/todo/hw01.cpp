/*
 * @Author: zhanghao
 * @Date: 2022-10-09 20:49:14
 * @LastEditTime: 2022-10-09 21:00:07
 * @FilePath: /hao_slamstar/01HW/todo/hw01.cpp
 * @Description: 
 */
#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdio.h>
using namespace std;
using namespace cv;
int main()
{
    //初始化一个outImage的矩阵用来保存输出的每一张图片
    Mat outImage;
    //指定原来时间序列存放图片的路径
    String src_path = "/home/hao007/github/hao_slamstar/01HW/rgbd_dataset_freiburg1_desk/rgb/";
    //指定改名后图片存放的路径
    String newName_path = src_path + "output/";
    //初始化新的名字，十个字符
    char newName[100];
    //定义文件的名字变量
    vector<String> filenames;
    //利用glob函数把rgb路径下所有的图片显示出来
    //注意:这里的路径和模式都用的是cv::String,
    //用来遍历文件夹下所有文件的！
    glob(src_path, filenames, false);
    cout << "filenames.size:" << filenames.size() << endl;
    for (int i = 0; i < filenames.size(); i++)
    {
        //取得当前每一张图片的名字
        String imgName = filenames[i];
        // npos是一个常数，用来表示不存在的位置！
        if (imgName.find(".png") != String::npos)
        {
            outImage = imread(imgName, cv::IMREAD_UNCHANGED);
            //(要写入的字符串，格式化字符串，变量)
            sprintf(newName, "%04d.png", i);
            //给换名字
            imwrite(newName_path + newName, outImage);
            cout << newName_path + newName << endl;
        }
        else
        {
            cout << "NOT A PNG IMAGE!" << endl;
        }
    }
    return 0;
}
