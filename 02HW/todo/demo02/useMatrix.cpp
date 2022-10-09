#include <iostream>

#include <Eigen/Core>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main()
{
    Quaterniond q(0.1, 0.35, 0.2, 0.3);
    cout << q.coeffs().transpose() << endl << endl;

    q.normalize();
    cout << "normalize" << endl;
    cout << q.coeffs().transpose() << endl << endl;

    Eigen::Matrix3d R = q.toRotationMatrix();
    Eigen::Matrix3d RT  = R.transpose();
    Eigen::Matrix3d RI  = R.inverse();

    cout << "RotationMatrix" << endl << R << endl << endl;
    cout << "RotationMatrix's transpose" << endl << RT << endl << endl;
    cout << "RotationMatrix's inverse" << endl << RI << endl << endl;

    // if(RT * R == E) orthogonal; else not orthogonal;
    cout << "RotationMatrix * RotationMatrix's transpose" << endl << R * RT << endl << endl;
    
}
