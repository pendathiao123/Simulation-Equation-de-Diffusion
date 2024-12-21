#ifndef PROBLEM_H
#define PROBLEM_H

#include "Variable.h"
#include "GaussSeidel.h"
#include "Equation.h"
#include <memory>
#include <stdexcept>

class Problem {
public:
    // Constructeur
    Problem(std::shared_ptr<IMesh> mesh, std::shared_ptr<Equation> equation, double tolerance, size_t max_iterations)
        : mesh(std::move(mesh)), equation(std::move(equation)), tolerance(tolerance), max_iterations(max_iterations) {
        if (!this->mesh || !this->equation) {
            throw std::invalid_argument("Mesh or equation pointer is null");
        }
    }

    // Méthode de résolution avec Jacobi
    void solveJacobi();

    // Méthode de résolution avec Gauss-Seidel
    void solveGaussSeidel();

private:
    std::shared_ptr<IMesh> mesh;         // Maillage
    std::shared_ptr<Equation> equation;  // Équation à résoudre
    double tolerance;                   // Tolérance de convergence
    size_t max_iterations;              // Nombre maximal d'itérations
};

#endif // PROBLEM_H
