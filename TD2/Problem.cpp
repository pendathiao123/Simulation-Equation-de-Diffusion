#include "Problem.h"
#include "GaussSeidel.h"
#include <algorithm>
#include <iostream>

// Méthode Jacobi
void Problem::solveJacobi() {
    Variable u_k(mesh.get(), "u_k");
    Variable u_k1(mesh.get(), "u_k1");

    size_t iter = 0;
    while (iter < max_iterations) {
        u_k1.reset();

        // Vérification de l'indice dans le calcul de Jacobi
        for (int i = 1; i < mesh->x_size() - 1; ++i) {
            double rhs_value = equation->getRHS(i);  // Vérifier l'indice ici
            u_k1[i] = (rhs_value + u_k[i - 1] + u_k[i + 1]) / 2.0;
        }

        // Vérification de la convergence
        double diff = 0.0;
        for (int i = 0; i < mesh->x_size(); ++i) {
            diff = std::max(diff, std::abs(u_k[i] - u_k1[i]));
        }

        if (diff < tolerance) {
            std::cout << "Convergence atteinte après " << iter << " itérations (Jacobi)." << std::endl;
            break;
        }
        u_k = u_k1;
        ++iter;
    }
}


       
// Méthode Gauss-Seidel
void Problem::solveGaussSeidel() {
    GaussSeidel gaussSeidelSolver(mesh, equation, tolerance, max_iterations);
    gaussSeidelSolver.solve();
}

