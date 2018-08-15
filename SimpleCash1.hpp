/* 
 * File:   SimpleCash1.hpp
 * Author: raitis
 *
 * Created on August 4, 2018, 5:18 PM
 */

#ifndef SIMPLECASH1_HPP
#define SIMPLECASH1_HPP

#include "SimpleCash1.h"

template<class T>
std::pair<double, double> SimpleCash1<T>::take(const T& val) {
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
    add(val, result);
    return result;
}

template<class T>
void SimpleCash1<T>::add(const T& val, const std::pair<double, double> result) {
    DEBUG_THREAD_MSG("Add entered...")
    std::unique_lock<std::mutex> locker(_lock);
    DEBUG_THREAD_MSG("Waiting for not reading...");
    not_read.wait(locker, [this]() {
        return !read; });
    //not read by other thread, then modify
    modify = true;
    DEBUG_THREAD_MSG("Modifying...")
    //find once more on val element, possible another thread has put it into cash         
    for (auto elem : _cash) {
        if (elem.element == val) {
           
            modify = false;
            locker.unlock();
            not_modify.notify_all();
            return;
        }
    }
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
int SimpleCash1<T>::size() const {
    std::lock_guard<std::mutex> locker(_lock);
    
    return _cash.size();
}

template<class T>
void SimpleCash1<T>::_printCash() const {
    std::cout << "Size= " << _cash.size() << std::endl;
    int counter = 1;
    for (auto elem : _cash) {
        std::cout <<counter++<<": "<< elem.element << std::endl;
    }
}

#endif /* SIMPLECASH1_HPP */

