#include "MeshFactory.h"
#include "UniformMesh.h"
#include "NonUniformMesh.h"

std::shared_ptr<IMesh> MeshFactory::createMesh(MeshType type, double x_min, double x_max, double dx) {
    if (type == MeshType::Uniform) {
        return std::make_shared<UniformMesh>(x_min, x_max, static_cast<int>((x_max - x_min) / dx + 1));
    } else if (type == MeshType::NonUniform) {
        // Exemple de points non uniformes
        std::vector<double> points = {x_min, x_min + 0.1, x_min + 0.3, x_min + 0.5, x_max - 0.2, x_max};
        return std::make_shared<NonUniformMesh>(x_min, x_max, points);
    }
    return nullptr; 
}
