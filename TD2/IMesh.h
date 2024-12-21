#ifndef IMESH_H
#define IMESH_H

#include <cstddef>

class IMesh {
public:
    virtual ~IMesh() = default;

    virtual double getXMin() const = 0;    // Retourne la borne minimale
    virtual double getXMax() const = 0;    // Retourne la borne maximale
    virtual double getDX() const = 0;      // Retourne le pas du maillage
    virtual int getNumPoints() const = 0;  // Retourne le nombre de points
    virtual int x_size() const = 0;        // Taille du maillage (équivalent au nombre de points)
    virtual double x_i(int i) const = 0;   // Retourne la position du point i
};

#endif // IMESH_H
