#ifndef GAUSSSEIDEL_H
#define GAUSSSEIDEL_H

#include "Equation.h"
#include "Variable.h"
#include "IMesh.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <memory>


class GaussSeidel {
public:
    // Constructeur
    GaussSeidel(std::shared_ptr<IMesh> mesh, std::shared_ptr<Equation> equation, double tolerance, size_t max_iterations)
        : mesh(mesh), equation(equation), tolerance(tolerance), max_iterations(max_iterations) {
        if (!mesh || !equation) {
            throw std::invalid_argument("Mesh or equation pointer is null");
        }
    }

    // Méthode pour résoudre l'équation avec Gauss-Seidel
    void solve() {
        Variable u_k(mesh.get(), "u_k");      // Solution à l'itération k
        Variable u_kp1(mesh.get(), "u_kp1");  // Solution à l'itération k+1

        // Initialisation de la condition initiale
        auto initial_condition = [](double x) { return (30.0 + 15.0) / 2.0; };
        equation->computeInitialCondition(u_k, mesh.get(), initial_condition);

        // Initialisation des valeurs du terme de droite et des coefficients
        std::vector<double> rhsValues(mesh->x_size(), 0.0);  // Initialisé à 0.0
        std::vector<double> coeffValues(mesh->x_size(), 4.0); // Exemple avec des coefficients

        equation->setRHSValues(rhsValues);
        equation->setCoeffValues(coeffValues);

        size_t iteration = 0;
        double error = tolerance + 1.0;

        while (iteration < max_iterations && error > tolerance) {
            // Mise à jour des points internes
            for (size_t i = 1; i < mesh->x_size() - 1; ++i) {
                double sum = 0.0;
                if (i > 0) sum += u_k[i - 1];  // Valeur précédente
                if (i + 1 < mesh->x_size()) sum += u_k[i + 1];  // Valeur suivante

                // Calcul de la nouvelle valeur pour u_i à l'itération k+1
                try {
                    double rhs_value = equation->getRHS(i);
                    double coeff_value = equation->getCoeff(i);
                    u_kp1[i] = (rhs_value - sum) / coeff_value;
                } catch (const std::out_of_range& e) {
                    std::cerr << "Erreur dans getCoeff : " << e.what() << " pour l'indice " << i << std::endl;
                }
            }

            // Calcul des conditions aux bords
            equation->computeBoundaryConditions(u_kp1);

            // Calcul de l'erreur maximale pour vérifier la convergence
            error = 0.0;
            for (size_t i = 1; i < mesh->x_size() - 1; ++i) {
                error = std::max(error, std::abs(u_kp1[i] - u_k[i]));
            }

            // Préparation pour la prochaine itération
            u_k = u_kp1;
            ++iteration;
        }

        // Vérification si la convergence n'est pas atteinte après les itérations maximales
        if (iteration == max_iterations) {
            std::cout << "Convergence non atteinte après " << max_iterations << " itérations.\n";
        }

        // Exportation de la solution finale
        u_kp1.writeToFile("u_kp1_final.data");

        // Calcul et affichage du résidu
        computeResidue(u_kp1);
    }

private:
    // Méthode pour calculer le résidu
    void computeResidue(const Variable& u_kp1) {
        double max_residue = 0.0;
        for (size_t i = 1; i < mesh->x_size() - 1; ++i) {
            double residual = equation->getRHS(i) - equation->getCoeff(i) * u_kp1[i];
            max_residue = std::max(max_residue, std::abs(residual));
        }
        std::cout << "Norme infinie du résidu: " << max_residue << std::endl;

        if (max_residue < tolerance) {
            std::cout << "Le résidu est suffisamment petit, la solution est correcte." << std::endl;
        } else {
            std::cout << "Le résidu est trop élevé, la solution peut être incorrecte." << std::endl;
        }
    }

    std::shared_ptr<IMesh> mesh;
    std::shared_ptr<Equation> equation;
    double tolerance;
    size_t max_iterations;
};

#endif // GAUSSSEIDEL_H
