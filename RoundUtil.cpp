/* 
 * File:   RoundUtil.cpp
 * Author: raitis
 * 
 * Created on July 11, 2018, 6:00 PM
 */

#include "RoundUtil.h"

RoundUtil::RoundUtil() {
}

inline uint64_t RoundUtil::doubleToRawBits(double x) {
    uint64_t bits;
    memcpy(&bits, &x, sizeof bits);
    return bits;
}

/**
 * Compare doubles and returns true if they are equal or false.
 * Comparing is done using epsilon: std::numeric_limits<double>::epsilon()
 * @param a 
 * @param b
 * @return true - if equal, false - otherwise
 */
bool RoundUtil::AreSame(double a, double b) {
    //cout<<"AreSame... ";
    return std::fabs(a - b) < std::numeric_limits<double>::epsilon();
}

/**
 * Compare doubles and returns true if they are equal or false.
 * Comparing is done by converting doubles to raw bits and compare by bits.
 * @param a
 * @param b
 * @return true - if equal, false - otherwise
 */
bool RoundUtil::AreSame_1(double a, double b) {
    //cout<<"AreSame_1... ";
    uint64_t longA = doubleToRawBits(a);
    uint64_t longB = doubleToRawBits(b);
   return longA == longB ;
}


 /**
     * Round value according to precision value.
     * Round and return double value with number of digits after the float point as many as
     * the value in the precision value.
     * @param value
     * @param precision digits number after the float point
     * @return
     */
 double RoundUtil::mround(double value, int precision){
 
     /***
      int scale = (int) pow(10., precision);
        return (double) round(value * scale) / scale;
      */
      double scale =  pow(10., precision);
        return round(value * scale) / scale;
 }
 
 

