/* 
 * File:   Vect3D.h
 * Author: raitis
 *
 * Created on July 12, 2018, 8:49 PM
 * 
 * To be used as a key in STL associated containers this
 * class must be:
 *   Copyable
 *   Assignable
 *   Comparable, since the map is sorted by key
 */

#ifndef VECT3D_H
#define VECT3D_H

#include <iostream>
#include <cmath>
#include <limits>

class Vect3D {
    //use max 16 digits after decimal point
    const std::string FLOAT_FMT = "%.16f";
    const double SCALE = 1e16;
    
public:
    
    Vect3D(double x=0., double y=0., double z=0., double dx=0., double dy=0., double dz=0.) :
    x(x), y(y), z(z), dx(dx), dy(dy), dz(dz) {
    }

    Vect3D(const Vect3D& other) :
     x(other.x), y(other.y), z(other.z), dx(other.dx), dy(other.dy), dz(other.dz) {
    }

    
    double GetDx() const {
        return dx;
    }

    double GetDy() const {
        return dy;
    }

    double GetDz() const {
        return dz;
    }

    double GetX() const {
        return x;
    }

    double GetY() const {
        return y;
    }

    double GetZ() const {
        return z;
    }
    
    void SetDx(double dx) {
        this->dx = dx;
    }

    void SetDy(double dy) {
        this->dy = dy;
    }

    void SetDz(double dz) {
        this->dz = dz;
    }

    void SetX(double x) {
        this->x = x;
    }

    void SetY(double y) {
        this->y = y;
    }

    void SetZ(double z) {
        this->z = z;
    }

    
    double module() const;
    double module_error() const;
    
    bool operator==(const Vect3D& right) const ;
    Vect3D& operator=(const Vect3D& right) ;
    
    bool operator<(const Vect3D& right) const ;

   

private:
    double x;
    double y;
    double z;

    double dx;
    double dy;
    double dz;
    
    bool AreSame(double a, double b) const;
    bool AreSameAbs(double a, double b) const; 
    
    friend std::ostream& operator<<(std::ostream& os, const Vect3D& vect) ;

};

#endif /* VECT3D_H */

