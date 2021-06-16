#include "Vec2D.hpp"
#include <cmath>

double Vec2D::get_norm() const{
    return sqrt(pow(_x,2)+pow(_y,2));
}