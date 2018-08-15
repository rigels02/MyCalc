/* 
 * File:   Cell.h
 * Author: raitis
 *
 * Created on August 7, 2018, 10:51 AM
 */

#ifndef CELL_H
#define CELL_H

#include <iostream>

template<typename T>
struct Cell {
    T element;
    std::pair<double,double> result;
};

#endif /* CELL_H */

