#ifndef NONUNIFORMMESH_H
#define NONUNIFORMMESH_H

#include "IMesh.h"
#include <vector>

class NonUniformMesh : public IMesh {
public:
    NonUniformMesh(double xMin, double xMax, const std::vector<double>& points);

    double getXMin() const override;
    double getXMax() const override;
    double getDX() const override;
    int getNumPoints() const override;
    int x_size() const override;
    double x_i(int i) const override;

private:
    double xMin, xMax;
    std::vector<double> points;
};

#endif // NONUNIFORMMESH_H
