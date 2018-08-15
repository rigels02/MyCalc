/* 
 * File:   SimpleCash2.hpp
 * Author: raitis
 *
 * The same as SimpleCash1 class, but modified add() function.
 * Created on August 7, 2018, 10:59 AM
 */

#ifndef SIMPLECASH2_HPP
#define SIMPLECASH2_HPP

#include "SimpleCash2.h"

template<class T>
std::pair<double, double> SimpleCash2<T>::take(const T& val) {
    //std::lock_guard<std::mutex> locker(_lock);
    std::pair<double, double> result;
    bool found = false;
    std::unique_lock<std::mutex> locker(_lock);
    DEBUG_THREAD_MSG("Waiting for not modify!")
    not_modify.wait(locker, [this]()-> bool {
        return !modify; });
    //if not modify by other thread
    //read
    read = true;
    DEBUG_THREAD_MSG("Reading...")
    int cashSize= _cash.size();        
    for (auto elem : _cash) {
        if (elem.element == val) {
            result = elem.result;
            found = true;
            break;
        }
    }
    read = false;
    locker.unlock();
    not_read.notify_all();

    if (found)
        return result;
    result = std::make_pair(val.result(), val.result_error());
    add(val, result, cashSize);
    return result;
}

template<class T>
void SimpleCash2<T>::add(const T& val, const std::pair<double, double> result,int cashSize) {
    DEBUG_THREAD_MSG("Add entered...")
    std::unique_lock<std::mutex> locker(_lock);
    DEBUG_THREAD_MSG("Waiting for not reading...");
    not_read.wait(locker, [this]() {
        return !read; });
    //not read by other thread, then modify
    modify = true;
    DEBUG_THREAD_MSG("Modifying...")
    //Has the required element been added to the cash by other thread?
    int new_cashSize = _cash.size();
    if(new_cashSize > cashSize){
        for(int i= cashSize; i< new_cashSize; i++){
           if(_cash[i].element == val){
               modify = false;
            locker.unlock();
            not_modify.notify_all();
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
    modify = false;
    locker.unlock();
    not_modify.notify_all();
}

template<class T>
int SimpleCash2<T>::size() const {
    std::lock_guard<std::mutex> locker(_lock);
    
    return _cash.size();
}

template<class T>
void SimpleCash2<T>::_printCash() const {
    std::cout << "Size= " << _cash.size() << std::endl;
    int counter = 1;
    for (auto elem : _cash) {
        std::cout <<counter++<<": "<< elem.element << std::endl;
    }
}


#endif /* SIMPLECASH2_HPP */

