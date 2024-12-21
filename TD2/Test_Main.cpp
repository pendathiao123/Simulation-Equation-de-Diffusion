/*#include <gtest/gtest.h>
#include "UniformMesh.h"
#include "Problem.h"
#include "Equation.h"

// Test pour la classe UniformMesh
TEST(UnitaryTest, MeshTest) {
    // Construction d'une instance de UniformMesh
    UniformMesh mesh(0.0, 1.0, 0.2); // x_min = 0, x_max = 1, dx = 0.2

    // Test des valeurs retournées
    EXPECT_DOUBLE_EQ(mesh.getXMin(), 0.0);
    EXPECT_DOUBLE_EQ(mesh.getXMax(), 1.0);
    EXPECT_DOUBLE_EQ(mesh.getDX(), 0.2);
    EXPECT_EQ(mesh.getNumPoints(), 6); // 0, 0.2, 0.4, 0.6, 0.8, 1.0
}

// Test pour la classe Problem
TEST(UnitaryTest, ProblemTest) {
    UniformMesh* mesh = new UniformMesh(0.0, 1.0, 0.2); // Création d'un maillage uniforme
    Problem problem(mesh);

    // Ici, on appelle la méthode solve() pour vérifier qu'elle ne plante pas
    ASSERT_NO_THROW(problem.solve());

    // Vérifier le nombre d'itérations (devrait être au moins 1)
    //XPECT_GT(problem.getNumIterations(), 0); // Assurez-vous d'avoir une méthode getNumIterations()
}

// Test pour la classe Equation
TEST(MainFunctionTest, EquationTest) {
    Equation equation;

    // Simuler l'appel à la méthode compute avec un maillage
    UniformMesh mesh(0.0, 1.0, 0.2);
    
    // Ici, nous voulons vérifier que la méthode compute ne plante pas
    ASSERT_NO_THROW(equation.compute(&mesh));

    // Ajouter des tests spécifiques si nécessaire
}
*/