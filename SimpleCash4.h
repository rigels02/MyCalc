
/* 
 * File:   SimpleCash4.h
 * Author: raitis
 *
 * Created on August 8, 2018, 8:50 PM
 * 
 * The same as SimpleCash3 class, but for cash using std::list container
 *  with locking only in add() function.
 *  (conditional locks removed)
 */

#ifndef SIMPLECASH4_H
#define SIMPLECASH4_H

#include <iostream>
#include <list>
#include <iterator>
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
class SimpleCash4  {
    const static int Max_Size = 400;

    
struct Cell {
    T element;
    std::pair<double,double> result;
};

    
public:

    std::pair<double,double> take(const T& val);
    
    
    int size() const;

    void _printCash() const;
    
    std::list< Cell > getCash() const {
        return _cash;
    }

    int getACounter() const {
        std::lock_guard<std::mutex> locker(_lock);
        return aCounter;
    }

    int getTCounter() const {
        std::lock_guard<std::mutex> locker(_lock);
        return tCounter;
    }

    
private:

   mutable std::mutex _lock;
   
    
    std::list<Cell> _cash;
    
    void add(const T& val, const std::pair<double,double> result, int lastSize);
   
    //Take() access counter.Increment in locked block!
    int tCounter=0;
    //Add() with new entry adding counter.Increment in locked block!
    int aCounter=0;
    
};

#include "SimpleCash4.hpp"




#endif /* SIMPLECASH4_H */

