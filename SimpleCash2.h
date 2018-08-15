/* 
 * File:   SimpleCash2.h
 * Author: raitis
 *
 * Created on August 7, 2018, 10:58 AM
 * 
 *  The same as SimpleCash1 class, but modified add() function.
 */

#ifndef SIMPLECASH2_H
#define SIMPLECASH2_H


#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "CashAble.h"


//#define DEBUG

#ifdef DEBUG
#define DEBUG_THREAD_MSG(msg)   std::cout<<std::this_thread::get_id()<<": "<<msg<<std::endl;
#else
#define DEBUG_THREAD_MSG(msg)
#endif

class T:public CashAble{};


template <class T>
class SimpleCash2  {
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
    std::condition_variable not_read;
    std::condition_variable not_modify;
    bool read = false;
    bool modify = false;
    
    std::vector<Cell> _cash;
    
    void add(const T& val, const std::pair<double,double> result, int cashSize);
   
    
};

#include "SimpleCash2.hpp"



#endif /* SIMPLECASH2_H */

