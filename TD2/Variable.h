#ifndef VARIABLE_H
#define VARIABLE_H

#include "IMesh.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>

class Variable {
public:
    Variable(IMesh* mesh, const std::string& name)
        : mesh(mesh), name(name), data(mesh ? mesh->x_size() : 0, 0.0) {
        if (!mesh) {
            throw std::invalid_argument("Le pointeur mesh ne peut pas être nul");
        }
        if (mesh->x_size() == 0) {
            throw std::invalid_argument("La taille du maillage est invalide (0).");
        }
    }

    void reset() {
        std::fill(data.begin(), data.end(), 0.0);
    }

    void print() const {
        if (!mesh) {
            throw std::runtime_error("Le pointeur mesh est invalide.");
        }
        for (size_t i = 0; i < data.size(); ++i) {
            std::cout << "x = " << mesh->x_i(i) << ", u(x) = " << data[i] << std::endl;
        }
    }

    void writeToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Impossible d'ouvrir le fichier : " + filename);
        }
        for (size_t i = 0; i < data.size(); ++i) {
            file << mesh->x_i(i) << " " << data[i] << "\n";
        }
        file.close();
    }

    double operator[](size_t index) const {
        if (index >= data.size()) {
            throw std::out_of_range("Index hors des limites.");
        }
        return data[index];
    }

    double& operator[](size_t index) {
        if (index >= data.size()) {
            throw std::out_of_range("Index hors des limites.");
        }
        return data[index];
    }

    size_t size() const { return data.size(); }

private:
    IMesh* mesh;                  
    std::string name;             
    std::vector<double> data;      
};

#endif // VARIABLE_H
