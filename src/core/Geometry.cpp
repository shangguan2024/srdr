#include "Geometry.hpp"
#include <cmath>

namespace srdr {

PlaneEquation::PlaneEquation(float A, float B, float C)
        : A(A),
          B(B),
          C(C) {}

PlaneEquation::PlaneEquation(float x0, float y0, float f0, float x1, float y1, float f1, float x2,
        float y2, float f2) {
    *this = computePlane(x0, y0, f0, x1, y1, f1, x2, y2, f2);
}

PlaneEquation PlaneEquation::computePlane(float x0, float y0, float f0, float x1, float y1,
        float f1, float x2, float y2, float f2) {
    float det = x0 * (y1 - y2) + x1 * (y2 - y0) + x2 * (y0 - y1);
    if (std::fabs(det) < 1e-6f) {
        // TODO: exceptions / error handling ?
        return PlaneEquation(0, 0, 0);
    }
    float inv_det = 1.0f / det;
    float A = (f0 * (y1 - y2) + f1 * (y2 - y0) + f2 * (y0 - y1)) * inv_det;
    float B = (f0 * (x2 - x1) + f1 * (x0 - x2) + f2 * (x1 - x0)) * inv_det;
    float C = (f0 * (x1 * y2 - x2 * y1) + f1 * (x2 * y0 - x0 * y2) + f2 * (x0 * y1 - x1 * y0)) *
              inv_det;
    return PlaneEquation(A, B, C);
}

float PlaneEquation::stepX() const { return A; }

float PlaneEquation::stepY() const { return B; }

float PlaneEquation::evaluate(float x, float y) const { return A * x + B * y + C; }

} // namespace srdr
