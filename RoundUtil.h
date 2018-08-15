/* 
 * File:   RoundUtil.h
 * Author: raitis
 *
 * Created on July 11, 2018, 6:00 PM
 */

#ifndef ROUNDUTIL_H
#define ROUNDUTIL_H

#include <iostream>
#include <cmath>
#include <cstring>
#include <limits>

class RoundUtil {

public:

    static inline uint64_t doubleToRawBits(double x);
    
    static bool AreSame(double a, double b);
    
    static bool AreSame_1(double a, double b);
    
    static double mround(double value, int precision);
    
    
private:
    RoundUtil();
    

};

#endif /* ROUNDUTIL_H */

