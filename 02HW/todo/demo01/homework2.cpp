#include <iostream>
#include <cmath>
#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace std;

int main() {
    Eigen::Quaterniond q(0.1,0.35,0.2,0.3);
    Eigen::Matrix3d rotation_matrix = q.normalized().toRotationMatrix();  // 四元数转旋转矩阵
    cout << "旋转矩阵： r= \n" << rotation_matrix << endl;
    Eigen::Matrix3d rotation_matrix_t = rotation_matrix.transpose();  // 旋转矩阵转置
    cout << "旋转矩阵转置后： rt= \n" << rotation_matrix_t << endl;
    Eigen::Matrix3d rotation_matrix_inv = rotation_matrix.inverse();  // 旋转矩阵的逆
    cout << "旋转矩阵的逆矩阵： r.inv= \n" << rotation_matrix_inv << endl;
    Eigen::Matrix3d rotation_matrix_rrt = rotation_matrix * rotation_matrix_t;  //旋转矩阵乘以自身的转置
    cout << "旋转矩阵乘以自身的转置： r*rt= \n " << rotation_matrix_rrt << endl;

    return 0;
}
