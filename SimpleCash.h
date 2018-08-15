/* 
 * File:   SimpleCash.h
 * Author: raitis
 *
 * Created on July 31, 2018, 9:58 AM
 * 
 * Using std::map<T,std::pair<double,double>> _cash and conditional locking.
 */

#ifndef SIMPLECASH_H
#define SIMPLECASH_H

#include <iostream>
#include <map>
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
class SimpleCash  {
    const static int Max_Size = 400;
    
    
public:
    
    std::pair<double,double> take(const T& val);
    
    
    int size() const;
    int internal_size() const {return _cash.size(); }
    void printCash() const;

    
private:

   mutable std::mutex _lock;
    std::condition_variable not_read;
    std::condition_variable not_modify;
    bool read = false;
    bool modify = false;
    
    std::map<T,std::pair<double,double>> _cash;
    
    void add(const T& val, const std::pair<double,double> result);
   
    
};

#include "SimpleCash.hpp"


#endif /* SIMPLECASH_H */

