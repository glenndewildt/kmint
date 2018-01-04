#include <cmath>
#include "../../include/linal/vector.h"

using namespace Linal::G2D;

Vector::Vector() : xAxis(0), yAxis(0), startingX(0), startingY(0) {}
Vector::Vector(double xAxis, double yAxis) : xAxis(xAxis), yAxis(yAxis), startingX(0), startingY(0) {};
Vector::Vector(double xAxis, double yAxis, double xStart, double yStart) : xAxis(xAxis), yAxis(yAxis), startingX(xStart), startingY(yStart) {};
Vector::~Vector() {};

Vector Vector::operator+(const Vector& rhs) {
    return Vector(xAxis + rhs.x(), yAxis + rhs.y());
}
Vector& Vector::operator+=(const Vector& rhs)
{
    xAxis += rhs.x();
    yAxis += rhs.y();

    return *this;
}
Vector Vector::operator-(const Vector& rhs)
{
    return Vector(xAxis - rhs.x(), yAxis - rhs.y());
}
Vector& Vector::operator-=(const Vector& rhs) {
    xAxis -= rhs.x();
    yAxis -= rhs.y();

    return *this;
}
Vector Vector::operator*(const double& rhs)
{
    return Vector(xAxis * rhs, yAxis * rhs);
}
Vector Vector::operator*(const Vector& rhs)
{
    return Vector(xAxis * rhs.x(), yAxis * rhs.y());
}
Vector& Vector::operator*=(const double & rhs) {
    auto oldX = xAxis;
    auto oldY = yAxis;

    x(oldX);
    y(oldY);

    return *this;
}
Vector Vector::operator/(const double& rhs)
{
    return Vector(xAxis / rhs, yAxis / rhs);
}
Vector Vector::operator/(const Vector& rhs)
{
    return Vector(xAxis / rhs.x(), yAxis / rhs.y());
}

Vector Vector::GetUnitVector() {
    auto vec = Vector(
        xAxis / sqrt(pow(xAxis, 2) + pow(yAxis, 2)),
        yAxis / sqrt(pow(xAxis, 2) + pow(yAxis, 2))
    );

    if (std::isnan(vec.x())) vec.x(0);
    if (std::isnan(vec.y())) vec.y(0);

    return vec;
}

double Vector::x() {
    return xAxis;
};

double Vector::x() const {
    return xAxis;
};

double Vector::y() {
    return yAxis;
};

double Vector::y() const {
    return yAxis;
};

Vector& Vector::x(double nx) {
    xAxis = nx;
    return *this;
};

Vector& Vector::y(double ny) {
    yAxis = ny;
    return *this;
};
