/* 
 * File:   CashAble.h
 * Author: raitis
 *
 * Created on August 3, 2018, 1:42 PM
 */

#ifndef CASHABLE_H
#define CASHABLE_H

class CashAble {

public:
    virtual double result() const = 0;
    
    virtual double result_error() const = 0;
};

#endif /* CASHABLE_H */

