#include "Equation.h"
#include <cmath>
#include <stdexcept>
#include <algorithm> // Pour std::abs

// Constructeur
Equation::Equation(double T1, double T2)
    : T1(T1), T2(T2) {}

// Retourne le second membre (rhs) pour un indice donné
double Equation::getRHS(std::size_t i) const {
    if (i >= rhsValues.size()) {
        throw std::out_of_range("Indice hors limites pour rhs.");
    }
    return rhsValues[i];
}

// Retourne le coefficient (coeff) pour un indice donné
double Equation::getCoeff(std::size_t i) const {
    if (i >= coeffValues.size()) {
        throw std::out_of_range("Indice hors limites pour coeff.");
    }
    return coeffValues[i];
}

// Initialise les valeurs de rhs
void Equation::setRHSValues(const std::vector<double>& values) {
    if (values.size() != rhsValues.size()) {
        rhsValues.resize(values.size());
    }
    rhsValues = values;
}

// Initialise les valeurs de coeff
void Equation::setCoeffValues(const std::vector<double>& values) {
    if (values.size() != coeffValues.size()) {
        coeffValues.resize(values.size());
    }
    coeffValues = values;
}

// Appliquer une itération de la méthode de Jacobi
void Equation::compute(const Variable& u_k, Variable& u_kp1) const {
    for (int i = 1; i < u_k.size() - 1; ++i) {
        // Application de la formule de Jacobi
        u_kp1[i] = (u_k[i - 1] + u_k[i + 1]) / 2.0;
    }
}

// Appliquer une itération de la méthode de Gauss-Seidel
void Equation::computeGaussSeidel(Variable& u_k) const {
    for (int i = 1; i < u_k.size() - 1; ++i) {
        // Application de la formule de Gauss-Seidel
        u_k[i] = (u_k[i - 1] + u_k[i + 1]) / 2.0;
    }
}

// Appliquer les conditions aux limites
void Equation::computeBoundaryConditions(Variable& u) const {
    u[0] = T1; // Température à x = 0 (condition de Dirichlet)
    u[u.size() - 1] = T2; // Température à x = 1 (condition de Dirichlet)
}

// Calcul de la solution exacte
void Equation::computeExactSolution(Variable& u_ref, const IMesh* mesh) const {
    for (int i = 0; i < mesh->x_size(); ++i) {
        double x = mesh->x_i(i);
        u_ref[i] = (T2 - T1) * x + T1; // Solution exacte linéaire pour une conduction thermique
    }
}

// Initialisation avec condition initiale
void Equation::computeInitialCondition(Variable& u, const IMesh* mesh, std::function<double(double)> initial_condition) const {
    for (int i = 0; i < mesh->x_size(); ++i) {
        double x_i = mesh->x_i(i); // Obtenir la position x_i
        u[i] = initial_condition(x_i); // Appeler la fonction lambda pour définir la température
    }
}

// Vérifier la convergence entre u_k et u_kp1
bool Equation::hasConverged(const Variable& u_k, const Variable& u_kp1, double epsilon) const {
    double max_diff = 0.0;
    // Check convergence only for internal points
    for (int i = 1; i < u_k.size() - 1; ++i) {
        double diff = std::abs(u_kp1[i] - u_k[i]);
        if (diff > max_diff) {
            max_diff = diff;
        }
    }
    return max_diff < epsilon;
}
