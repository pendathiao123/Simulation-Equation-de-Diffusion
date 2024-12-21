#ifndef EQUATION_H
#define EQUATION_H

#include "Variable.h"
#include <vector>
#include <functional> // Pour std::function

class Equation {
public:
    // Constructeur avec valeurs de température aux bornes
    Equation(double T1 = 30, double T2 = 15);

    // Retourne le second membre (rhs) pour un indice donné
    double getRHS(std::size_t i) const;

    // Retourne le coefficient (coeff) pour un indice donné
    double getCoeff(std::size_t i) const;

    // Initialise les valeurs de rhs
    void setRHSValues(const std::vector<double>& values);

    // Initialise les valeurs de coeff
    void setCoeffValues(const std::vector<double>& values);

    // Appliquer une itération de la méthode de Jacobi
    void compute(const Variable& u_k, Variable& u_kp1) const;

    // Appliquer une itération de la méthode de Gauss-Seidel
    void computeGaussSeidel(Variable& u_k) const;

    // Appliquer les conditions aux limites
    void computeBoundaryConditions(Variable& u) const;

    // Calculer la solution exacte
    void computeExactSolution(Variable& u_ref, const IMesh* mesh) const;

    // Initialisation avec condition initiale
    void computeInitialCondition(Variable& u, const IMesh* mesh, std::function<double(double)> initial_condition) const;

    // Vérifier la convergence entre u_k et u_kp1
    bool hasConverged(const Variable& u_k, const Variable& u_kp1, double epsilon) const;

private:
    double T1, T2;                     // Températures aux bornes
    std::vector<double> rhsValues;     // Second membre
    std::vector<double> coeffValues;   // Coefficients
};

#endif // EQUATION_H
