#include<iostream>
#include <vector>

struct A
{
    std::vector<int> data;
};

int main(){
    std::vector<int> vec{1,2,3,4};

    A a{};
    a.data=std::move(vec); //no copy 
}


#include "Problem.h"
#include <iostream>
#include <cmath>
#include <stdexcept>

// Constructeur
Problem::Problem(IMesh* mesh, Equation* equation, double tolerance, size_t max_iterations)
    : mesh(mesh), equation(equation), tolerance(tolerance), max_iterations(max_iterations) {
    if (!mesh || !equation) {
        throw std::invalid_argument("Le pointeur mesh ou equation est nul");
    }
}

// Destructeur
Problem::~Problem() {
    delete mesh;
    delete equation;
}

// Résolution du problème
void Problem::solve() {
    // Initialisation des variables
    Variable u_k(mesh, "u_k");       // Solution à l'itération k
    Variable u_kp1(mesh, "u_kp1");   // Solution à l'itération k+1
    Variable u_ref(mesh, "u_ref");   // Solution exacte pour comparaison

    // Définir la condition initiale
    auto initial_condition = [](double x) {
        return (x < 0.5) ? 30.0 : 15.0; // Exemple
    };
    equation->compute_initial_condition(u_k, mesh, initial_condition);

    // Exporter la condition initiale avant de démarrer le calcul
    u_k.print(); // Exporte u_k (condition initiale)

    // Calcul de la solution exacte
    equation->compute_exact_solution(u_ref, mesh);

    // Afficher les solutions initiales
    std::cout << "Conditions initiales :" << std::endl;
    u_k.print();
    u_ref.print();

    // Résolution itérative
    size_t iteration_count = 0;
    while (iteration_count < max_iterations) {
        // Calcul de l'étape suivante
        equation->compute(u_k, u_kp1);
        equation->compute_boundary_conditions(u_kp1);

        // Vérification de la convergence
        if (hasConverged(u_k, u_kp1, tolerance)) {
            std::cout << "Convergence atteinte après " << iteration_count + 1 << " itérations." << std::endl;
            break;
        }

        // Préparer la prochaine itération
        u_k = u_kp1;
        ++iteration_count;
    }

    if (iteration_count == max_iterations) {
        std::cout << "La convergence n'a pas été atteinte après " << max_iterations << " itérations." << std::endl;
    }

    // Exporter la solution numérique à la fin
    u_kp1.print();

    // Afficher la solution exacte et la solution numérique finale
    std::cout << "Solution exacte : " << std::endl;
    u_ref.print();

    std::cout << "Solution numérique finale : " << std::endl;
    u_kp1.print();
}

// Vérifie la convergence
bool Problem::hasConverged(const Variable& u_k, const Variable& u_kp1, double epsilon) const {
    double max_diff = 0.0;
    for (size_t i = 0; i < u_k.size(); ++i) { // Utilisation de size_t pour l'index
        max_diff = std::max(max_diff, std::abs(u_kp1[i] - u_k[i]));
    }
    return max_diff < epsilon;
}

// Résolution via Gauss-Seidel
void Problem::gaussSeidelSolve() {
    // Création des variables pour les solutions
    Variable u_k_gs(mesh, "u_k_gs");
    Variable u_kp1_gs(mesh, "u_kp1_gs");

    // Initialisation des conditions
    u_k_gs.reset(); // Assurer que u_k_gs est réinitialisé avant de commencer

    size_t iteration = 0;
    double error = tolerance + 1.0;

    while (iteration < max_iterations && error > tolerance) {
        // Application de Gauss-Seidel
        for (size_t i = 0; i < mesh->x_size(); ++i) {
            double sum = 0.0;

            // Calcul de la somme sur les voisins
            if (i > 0) sum += u_k_gs[i - 1];  // Valeur voisine à gauche
            if (i < mesh->x_size() - 1) sum += u_k_gs[i + 1];  // Valeur voisine à droite

            // Mise à jour de la valeur de u_kp1_gs (solution à la position i)
            u_kp1_gs[i] = (equation->rhs(i) - sum) / equation->coeff(i);
        }

        // Calcul de l'erreur (maximal)
        error = 0.0;
        for (size_t i = 0; i < mesh->x_size(); ++i) {
            error = std::max(error, std::abs(u_kp1_gs[i] - u_k_gs[i]));
        }

        // Mise à jour de u_k_gs
        u_k_gs = u_kp1_gs;

        // Exporter les résultats après chaque itération (ou à un moment spécifique)
        std::cout << "Iteration " << iteration + 1 << " : " << std::endl;
        u_k_gs.print();  // Affiche ou exporte les résultats après chaque itération

        ++iteration;
    }

    // Exporter la solution finale après la convergence (ou la fin des itérations)
    if (iteration == max_iterations) {
        std::cout << "La convergence n'a pas été atteinte après " << max_iterations << " itérations." << std::endl;
    }
    std::cout << "Solution finale de Gauss-Seidel : " << std::endl;
    u_k_gs.print(); // Affiche ou exporte la solution finale
}



