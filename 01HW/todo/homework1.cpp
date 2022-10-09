/*
 * @Author: zhanghao
 * @Date: 2022-10-09 21:13:01
 * @LastEditTime: 2022-10-09 21:34:04
 * @FilePath: /hao_slamstar/01HW/todo/homework1.cpp
 * @Description: 
 */
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>  //mkdir文件
#include "dependency/fmt/include/fmt/core.h"

using namespace std;

int main(int argc, char** argv) {
    string imagePATH = "/home/hao007/github/hao_slamstar/01HW/rgbd_dataset_freiburg1_desk/rgb"; //待处理图片位置路径
    //创建新文件夹存放修改了文件名的图片
    string newImagePath = imagePATH + "/newImageFolder";
    int isCreate = mkdir("/home/hao007/github/hao_slamstar/01HW/rgbd_dataset_freiburg1_desk/rgb/newImageFolder", S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
    if( !isCreate )
        printf("create path:%s\n", "/home/hao007/github/hao_slamstar/01HW/rgbd_dataset_freiburg1_desk/rgb/newImageFolder");
    else
        printf("create path failed! error code : %s \n", isCreate, "/home/hao007/github/hao_slamstar/01HW/rgbd_dataset_freiburg1_desk/rgb/newImageFolder");

    vector<string> image_name;
    cv::glob(imagePATH,image_name, false);//遍历文件下的图片，并获取图片名称
    if (image_name.size()==0){
        cout << "There's no file in" << imagePATH << endl;
    }

    for (int i = 0; i < image_name.size(); ++i) {
        cv::Mat readImage = cv::imread(image_name[i],cv::IMREAD_COLOR);  //读取一张图片
        if (readImage.empty()){
            cout << "Read Image Failed!" << image_name[i] << endl;  //判断是否读取成功
        }
        string newImageName = newImagePath + "/" + fmt::format("{:0>4}",i)+ ".png";  //使用fmt对其进行重命名
        cv::imwrite(newImageName,readImage);
        cout << to_string(i) << "rename successful!" << endl;
    }
    cout<<"totally rename "<<image_name.size()<<" pictures!"<<endl;
    return 0;
}
