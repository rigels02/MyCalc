/* 
 * File:   Vect3D.cpp
 * Author: raitis
 * 
 * Created on July 12, 2018, 8:49 PM
 */

#include "Vect3D.h"


/**
 * Calculate vector module.
 * @return 
 */
double Vect3D::module() const{
    return  sqrt( pow(x,2.) + pow(y,2.) + pow(z, 2.) );
}

/**
 * Calculate this vector module's absolute error.
 * @return 
 */
double Vect3D::module_error() const{

    double a = pow(x, 2.) * pow(dx, 2.) +
               pow(y, 2.) * pow(dy, 2.) +
               pow(z, 2.) * pow(dz, 2.);
    double b = pow(x, 2) + pow(y, 2)+ pow(z, 2);
    double delta = sqrt(a / b);
        //sometimes double could be presented in scientific form like
        // 9.9999999E-4 etc.
        //Below we try to convert it into decimal form like: 0.0001
    double rounded = round(delta * SCALE) / SCALE; 
       // Double rounded = Double.valueOf(String.format(FLOAT_FMT, delta));
       // System.out.println("org.rb.round.Vect3D.module_error()- before round: "+delta+" ,after= "+rounded);
        return rounded;
}

bool Vect3D::AreSame(double a, double b) const {
    return std::fabs(a - b) < std::numeric_limits<double>::epsilon();
}

bool Vect3D::AreSameAbs(double a, double b) const {
    return a == b;
}

bool Vect3D::operator==(const Vect3D& right) const {
        bool result = false; // Compare right and *this here
       
        
        result = AreSameAbs(this->x, right.x) &&
                AreSameAbs(this->y, right.y) &&
                AreSameAbs(this->z, right.z) &&
                AreSameAbs(this->dx, right.dx) &&
                AreSameAbs(this->dy, right.dy) &&
                AreSameAbs(this->dz, right.dz) ;
        return result;
}

Vect3D& Vect3D::operator=(const Vect3D& right) {
        // Check for self-assignment!
        if (this == &right) // Same object?
            return *this; // Yes, so skip assignment, and just return *this.
        // Deallocate, allocate new space, copy values...
        this->x = right.x; this->y = right.y; this->z = right.z;
        this->dx = right.dx; this->dy = right.dy; this->dz = right.dz;
        return *this;
    }

/**
     * Default comparator for Vect3D class.
     * For usage Vect3D as key in associated containers like: set , map...
     * @param right
     * @return 
     */
bool Vect3D::operator <(const Vect3D& right) const{
  bool ok=  this->x < right.x ||
    this->y < right.y ||
    this->z < right.z ||
    this->dx < right.dx ||
    this->dy < right.dy ||
    this->dz < right.dz ;    
  return ok;
}


std::ostream& operator<<(std::ostream& os, const Vect3D& vect) {
        // Write obj to stream
    os<<"( "<<vect.x<<","<<vect.y<<","<<vect.z<<", "<<vect.dx<<","<<vect.dy<<","<<vect.dz<<" )";
        return os;
    }
