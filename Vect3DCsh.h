
/* 
 * File:   Vect3DCsh.h
 * Author: raitis
 *
 * Created on August 3, 2018, 2:35 PM
 */

#ifndef VECT3DCSH_H
#define VECT3DCSH_H

#include "CashAble.h"
#include "Vect3D.h"

struct Vect3DCsh: public CashAble{

    Vect3D vect;


    Vect3DCsh(double x=0., double y=0., double z=0., double dx=0., double dy=0., double dz=0.) 
    {
        vect.SetX(x); vect.SetY(y); vect.SetZ(z); vect.SetDx(dx);
        vect.SetDy(dy); vect.SetDz(dz);
    }
    
    Vect3DCsh(const Vect3D& vect) :
    vect(vect) {
    }

    bool operator==(const Vect3DCsh& right) const {
        bool result = false; // Compare right and *this here
        result = this->vect == right.vect;
        return result;
    }

    bool operator<(const Vect3DCsh& right) const {
        return this->vect < right.vect;
    }

   
    double result() const override{
        return vect.module();
    }

    double result_error() const override{
        return vect.module_error();
    }
    friend std::ostream& operator<<(std::ostream& os, const Vect3DCsh& obj) {
        os<<obj.vect;
        return os;
    }
    
}; 

#endif /* VECT3DCSH_H */

