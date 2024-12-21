#include "NonUniformMesh.h"

NonUniformMesh::NonUniformMesh(double xMin, double xMax, const std::vector<double>& points)
    : xMin(xMin), xMax(xMax), points(points) {}

double NonUniformMesh::getXMin() const { return xMin; }
double NonUniformMesh::getXMax() const { return xMax; }
int NonUniformMesh::getNumPoints() const { return points.size(); }
int NonUniformMesh::x_size() const { return getNumPoints(); }
double NonUniformMesh::x_i(int i) const { return points[i]; }
double NonUniformMesh::getDX() const { return points.size() > 1 ? points[1] - points[0] : 0; }
