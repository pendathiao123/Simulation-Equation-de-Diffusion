#include <iostream>
#include <memory>
#include "IMesh.h"
#include "UniformMesh.h"
#include "Equation.h"
#include "Problem.h"

int main(int argc, char* argv[]) {
    // Vérification des arguments
    if (argc != 6) {
        std::cerr << "Usage: " << argv[0] << " <x_min> <x_max> <dx> <mesh_type> <tolerance>" << std::endl;
        return 1;
    }

    // Lecture des arguments
    double x_min = std::stod(argv[1]);
    double x_max = std::stod(argv[2]);
    double nbpoints = std::stod(argv[3]);
    std::string mesh_type = argv[4];
    double tolerance = std::stod(argv[5]);
    size_t max_iterations = 1e7; // Nombre d'itérations maximum

    try {
        // Création du maillage
        std::shared_ptr<IMesh> mesh;
        if (mesh_type == "uniform") {
            mesh = std::make_shared<UniformMesh>(x_min, x_max, nbpoints);
        } else {
            throw std::invalid_argument("Type de maillage inconnu : " + mesh_type);
        }

        // Création de l'équation
        auto equation = std::make_shared<Equation>();

        // Création du problème
        Problem problem(mesh, equation, tolerance, max_iterations);

        // Résolution par méthode Jacobi
        std::cout << "Résolution avec la méthode itérative classique (Jacobi):" << std::endl;
        problem.solveJacobi();

        // Résolution par méthode de Gauss-Seidel
        std::cout << "\nRésolution avec la méthode de Gauss-Seidel:" << std::endl;
        problem.solveGaussSeidel();

        std::cout << "\nLes données ont été exportées dans des fichiers pour visualisation avec Gnuplot." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Erreur: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
