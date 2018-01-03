//
// Created by administrator on 3-1-18.
//

#ifndef KMINTFRAMEWORK_VECTOR_H
#define KMINTFRAMEWORK_VECTOR_H

namespace Linal
{
    namespace G2D
    {
        class Vector
        {
        public:
            Vector();
            Vector(double xAxis, double yAxis);
            Vector(double xAxis, double yAxis, double xStart, double yStart);
            ~Vector();

            Vector operator+(const Vector&);
            Vector& operator+=(const Vector&);
            Vector operator-(const Vector&);
            Vector& operator-=(const Vector&);

            Vector operator*(const double&);
            Vector operator*(const Vector&);
            Vector operator/(const double&);
            Vector operator/(const Vector&);

            double x();
            double x() const;
            double y();
            double y() const;
            Vector& x(double nx);
            Vector& y(double ny);

        private:
            double xAxis;
            double yAxis;

            double startingX;
            double startingY;
        };
    }
}

#endif //KMINTFRAMEWORK_VECTOR_H
