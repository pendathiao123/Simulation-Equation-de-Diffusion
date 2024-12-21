#include "Problem.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

// Constructor
Problem::Problem(std::shared_ptr<IMesh> mesh, std::shared_ptr<Equation> equation, double tolerance, size_t max_iterations)
    : mesh(std::move(mesh)), equation(std::move(equation)), tolerance(tolerance), max_iterations(max_iterations) {
    if (!this->mesh || !this->equation) {
        throw std::invalid_argument("Mesh or equation pointer is null");
    }
}

// Jacobi method
void Problem::solve() {
    Variable u_k(mesh.get(), "u_k");       // Solution at iteration k
    Variable u_kp1(mesh.get(), "u_kp1");   // Solution at iteration k+1
    Variable u_ref(mesh.get(), "u_ref");   // Exact solution

    // Initialize initial condition
    auto initial_condition = [](double x) { return 30.0 - 15.0 * x; };  // Une condition lisse
    equation->computeInitialCondition(u_k, mesh.get(), initial_condition);

    // Initialize rhs and coeff values (example with specific values)
    std::vector<double> rhsValues(mesh->x_size(), 0.0);  // Initialize to 0.0
    std::vector<double> coeffValues(mesh->x_size(), 1.0); // Initialize to 1.0

    // Apply setRHSValues and setCoeffValues
    equation->setRHSValues(rhsValues);
    equation->setCoeffValues(coeffValues);

    // Export initial condition
    u_k.writeToFile("u_k_initial.data");

    // Compute exact solution
    equation->computeExactSolution(u_ref, mesh.get());
    u_ref.writeToFile("u_ref_exact.data");

    size_t iteration = 0;
    while (iteration < max_iterations) {
        // Compute next step
        equation->compute(u_k, u_kp1);
        equation->computeBoundaryConditions(u_kp1);

        // Check convergence
        if (equation->hasConverged(u_k, u_kp1, tolerance)) {
            std::cout << "Convergence atteinte aprés " << iteration + 1 << " iterations.\n";
            break;
        }

        // Prepare for next iteration
        u_k = u_kp1;
        ++iteration;
    }


    if (iteration == max_iterations) {
        std::cout << "Convergence not reached after " << max_iterations << " iterations.\n";
    }

    // Export final solution
    u_kp1.writeToFile("u_kp1_final.data");
}

// Gauss-Seidel method
void Problem::gaussSeidelSolve() {
    Variable u_k_gs(mesh.get(), "u_k_gs");
    Variable u_kp1_gs(mesh.get(), "u_kp1_gs");

    u_k_gs.reset(); // Reset to zero (or initial condition if needed)
    size_t iteration = 0;
    double error = tolerance + 1.0;

    // Loop for iterations until convergence or max iterations
    while (iteration < max_iterations && error > tolerance) {
        // Update internal points, excluding boundaries
        for (size_t i = 1; i < mesh->x_size() - 1; ++i) {
            double sum = 0.0;
            
            // Adding previous and next values (for internal points)
            if (i > 0) sum += u_k_gs[i - 1];  // Previous value
            if (i + 1 < mesh->x_size()) sum += u_k_gs[i + 1];  // Next value

            // Compute new value at point i using the equation
            try {
                double rhs_value = equation->getRHS(i);
                double coeff_value = equation->getCoeff(i);
                u_kp1_gs[i] = (rhs_value - sum) / coeff_value;
            } catch (const std::out_of_range& e) {
                std::cerr << "Error in getCoeff: " << e.what() << " for index " << i << std::endl;
            }
        }

        // Handle boundary conditions (e.g., Dirichlet boundary condition)
        equation->computeBoundaryConditions(u_kp1_gs);

        // Compute max error for convergence check
        error = 0.0;
        for (size_t i = 1; i < mesh->x_size() - 1; ++i) {
            error = std::max(error, std::abs(u_kp1_gs[i] - u_k_gs[i]));
        }

        // Prepare for next iteration
        u_k_gs = u_kp1_gs;  // Update u_k_gs for next iteration
        ++iteration;
    }

    // If convergence wasn't reached after max iterations
    if (iteration == max_iterations) {
        std::cout << "Convergence not reached after " << max_iterations << " iterations.\n";
    }

    // Export final solution
    u_kp1_gs.writeToFile("u_kp1_gs_final.data");
}




    auto initial_condition = [](double x) { return (x < 0.5) ? 30.0 : 15.0; };
