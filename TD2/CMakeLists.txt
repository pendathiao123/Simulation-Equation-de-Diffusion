# Version minimale de CMake requise
cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(POO)

# Définir la version de C++ à utiliser (ici C++17)
set(CMAKE_CXX_STANDARD 17)

# Inclure les répertoires où se trouvent les fichiers .h
include_directories(${CMAKE_SOURCE_DIR})

# Créer l'exécutable principal à partir des fichiers sources
add_executable(main 
    Main.cpp 
    Problem.cpp 
    Equation.cpp 
    UniformMesh.cpp  # Ajout de UniformMesh
    NonUniformMesh.cpp # Ajout de NonUniformMesh si nécessaire
    MeshFactory.cpp 
)

# Activer les tests
enable_testing()

# Trouver et inclure GoogleTest (GTest)
find_package(GTest REQUIRED)

# Créer l'exécutable pour les tests
add_executable(test_main 
    Test_Main.cpp 
    Problem.cpp 
    Equation.cpp 
    UniformMesh.cpp  # Ajout de UniformMesh
    NonUniformMesh.cpp # Ajout de NonUniformMesh si nécessaire
    MeshFactory.cpp
)

# Lier l'exécutable de test avec GTest et pthread (nécessaire pour GTest sous Linux)
target_link_libraries(test_main GTest::GTest GTest::Main pthread)

# Ajouter le test à CTest
add_test(NAME test_main COMMAND test_main)

# Installation des exécutables principaux dans un répertoire bin
install(TARGETS main
        RUNTIME DESTINATION bin)

install(TARGETS test_main
        RUNTIME DESTINATION bin)
