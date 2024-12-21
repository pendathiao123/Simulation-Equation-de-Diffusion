#include "UniformMesh.h"
#include <stdexcept>

UniformMesh::UniformMesh(double xMin, double xMax, int numPoints)
    : xMin(xMin), xMax(xMax), dx((xMax - xMin) / (numPoints - 1)) {
    if (numPoints < 2) {
        throw std::invalid_argument("Le nombre de points doit être supérieur ou égal à 2.");
    }
    for (int i = 0; i < numPoints; ++i) {
        points.push_back(xMin + i * dx);
    }
}

double UniformMesh::getXMin() const {
    return xMin;
}

double UniformMesh::getXMax() const {
    return xMax;
}

double UniformMesh::getDX() const {
    return dx;
}

int UniformMesh::getNumPoints() const {
    return points.size();
}

int UniformMesh::x_size() const {
    return points.size();
}

double UniformMesh::x_i(int i) const {
    if (i < 0 || i >= static_cast<int>(points.size())) {
        throw std::out_of_range("Indice hors des limites du maillage.");
    }
    return points[i];
}
