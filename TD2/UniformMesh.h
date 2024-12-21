#ifndef UNIFORMMESH_H
#define UNIFORMMESH_H

#include "IMesh.h"
#include <vector>

class UniformMesh : public IMesh {
public:
    UniformMesh(double xMin, double xMax, int numPoints);

    double getXMin() const override;
    double getXMax() const override;
    double getDX() const override;
    int getNumPoints() const override;
    int x_size() const override;
    double x_i(int i) const override;

private:
    double xMin, xMax, dx;
    std::vector<double> points;
};

#endif // UNIFORMMESH_H
