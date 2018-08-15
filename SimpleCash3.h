/* 
 * File:   SimpleCash3.h
 * Author: raitis
 *
 * Created on August 7, 2018, 11:33 AM
 * 
 *  The same as SimpleCash2 class, but with locking only in add() function.
 *  (conditional locks removed)
 * The fastest (10x) cash then SimpleCash, SimpleCash1, SimpleCash2.
 */

#ifndef SIMPLECASH3_H
#define SIMPLECASH3_H

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>


#include "CashAble.h"


//#define DEBUG

#ifdef DEBUG
#define DEBUG_THREAD_MSG(msg)   std::cout<<std::this_thread::get_id()<<": "<<msg<<std::endl;
#else
#define DEBUG_THREAD_MSG(msg)
#endif

class T:public CashAble{};


template <class T>
class SimpleCash3  {
    const static int Max_Size = 400;

    
struct Cell {
    T element;
    std::pair<double,double> result;
};

    
public:

    std::pair<double,double> take(const T& val);
    
    
    int size() const;

    void _printCash() const;
    
    std::vector< Cell > getCash() const {
        return _cash;
    }

    
private:

   mutable std::mutex _lock;
   
    
    std::vector<Cell> _cash;
    
    void add(const T& val, const std::pair<double,double> result, int cashSize);
   
    
};

#include "SimpleCash3.hpp"




#endif /* SIMPLECASH3_H */

