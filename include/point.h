#ifndef _KMINT_POINT_H
#define _KMINT_POINT_H

#include <istream>
#include <cmath>

namespace kmint {
    class point {
    public:
        using coord = float;
        point() : _x{0}, _y{0} {}
        point(coord x, coord y) : _x{x}, _y{y} {}
        coord x()  noexcept { return _x; }
        void x(coord newX) noexcept { _x = newX; }
        coord y() const noexcept { return _y; }
        void y(coord newY) noexcept { _y = newY; }
    private:
        coord _x;
        coord _y;
    };

    std::istream &operator>>(std::istream &is, point &p);

    inline point operator-(point a, point b) {
        return { a.x() - b.x(), a.y() - b.y() };
    }

    inline point operator+(point a, point b) {
        return { a.x() + b.x(), a.y() + b.y() };
    }

    inline auto dot(point a, point b) {
        return a.x()*b.x() + a.y() + b.y();
    }

    inline point normalize(point p) {
        auto ls = dot(p, p);
        return { p.x() / ls, p.y() / ls };
    }

    inline auto norm(point p) {
        return std::sqrt(dot(p, p));
    }

    inline auto distance(point from, point to) {
        return norm(to - from);
    }
}

#endif
