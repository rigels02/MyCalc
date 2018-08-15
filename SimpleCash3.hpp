/* 
 * File:   SimpleCash3.hpp
 * Author: raitis
 *
 * Created on August 7, 2018, 11:34 AM
 */

#ifndef SIMPLECASH3_HPP
#define SIMPLECASH3_HPP

#include "SimpleCash3.h"

template<class T>
std::pair<double, double> SimpleCash3<T>::take(const T& val) {
    
    std::pair<double, double> result;
    bool found = false;
    
    DEBUG_THREAD_MSG("Reading...")
    int cashSize=0;
    {   //lock this block
        std::lock_guard<std::mutex> locker(_lock);
       cashSize= _cash.size();
    }
    //Use this thread cashsize what was gotten by locked block above.
    //Any thread is able to add new element only to the end of _cash vector.
    for (int i=0; i< cashSize; i++) {
        
        if (_cash[i].element == val) {
            result = _cash[i].result;
            found = true;
            break;
        }
    }
    
    if (found)
        return result;
    result = std::make_pair(val.result(), val.result_error());
    add(val, result, cashSize);
    return result;
}

template<class T>
void SimpleCash3<T>::add(const T& val, const std::pair<double, double> result,int cashSize) {
    DEBUG_THREAD_MSG("Add entered...")
    //std::unique_lock<std::mutex> locker(_lock);
    std::lock_guard<std::mutex> locker(_lock);
    //modify = true;
    DEBUG_THREAD_MSG("Modifying...")
    //Has the required element been added to the cash by other thread?
    int new_cashSize = _cash.size();
    if(new_cashSize > cashSize){
        for(int i= cashSize; i< new_cashSize; i++){
           if(_cash[i].element == val){
            return;
           }
        }
    }
    // if not, then add it
    
    if (_cash.size() < Max_Size) {
        Cell cell;
        cell.element = val;
        cell.result = result;
        _cash.push_back(cell);
    }
    
}

template<class T>
int SimpleCash3<T>::size() const {
    std::lock_guard<std::mutex> locker(_lock);
    
    return _cash.size();
}

template<class T>
void SimpleCash3<T>::_printCash() const {
    std::cout << "Size= " << _cash.size() << std::endl;
    int counter = 1;
    for (auto elem : _cash) {
        std::cout <<counter++<<": "<< elem.element << std::endl;
    }
}


#endif /* SIMPLECASH3_HPP */

