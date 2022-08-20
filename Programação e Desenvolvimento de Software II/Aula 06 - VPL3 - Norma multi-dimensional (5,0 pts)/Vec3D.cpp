#include "Vec3D.hpp"
#include <cmath>

double Vec3D::get_norm() const{
    return sqrt(pow(_x,2)+pow(_y,2)+pow(_z,2));
}