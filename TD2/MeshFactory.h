#ifndef MESHFACTORY_H
#define MESHFACTORY_H

#include "IMesh.h"
#include "UniformMesh.h"
#include "NonUniformMesh.h"
#include <memory>

enum class MeshType {
    Uniform,
    NonUniform
};

class MeshFactory {
public:
    static std::shared_ptr<IMesh> createMesh(MeshType type, double x_min, double x_max, double dx);
};

#endif // MESHFACTORY_H
