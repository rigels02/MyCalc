/* 
 * File:   SimpleCash4.hpp
 * Author: raitis
 *
 * Created on August 8, 2018, 8:50 PM
 */

#ifndef SIMPLECASH4_HPP
#define SIMPLECASH4_HPP

#include "SimpleCash4.h"

template<class T>
std::pair<double, double> SimpleCash4<T>::take(const T& val) {
    
    std::pair<double, double> result;
    bool found = false;
   
    
    DEBUG_THREAD_MSG("Reading...")
    typename std::list<Cell>::iterator it;        
    typename std::list<Cell>::iterator it_end; 
    int lastSize = 0;
    {
        std::lock_guard<std::mutex> locker(_lock);
         tCounter++;
        it_end = _cash.end();
        lastSize = _cash.size();
    }
    //Iterate to find required element.
    //Any thread is able to add new element only to the end of _cash list.
    for (it = _cash.begin(); it != it_end; it++) {
        
        if ( it->element == val) {
            result = it->result;
            found = true;
            break;
        }
    }
    
    if (found)
        return result;
    result = std::make_pair(val.result(), val.result_error());
    add(val, result, lastSize);
    return result;
}

template<class T>
void SimpleCash4<T>::add(
        const T& val, 
        const std::pair<double, double> result,
        int lastSize) 
{
    
    DEBUG_THREAD_MSG("Add entered...")
    
    std::lock_guard<std::mutex> locker(_lock);
   
    DEBUG_THREAD_MSG("Modifying...")
    //Has the required element been added to the cash by other thread?
    typename std::list<Cell>::reverse_iterator it = _cash.rbegin();           
    int newSize = _cash.size();  
    //cash size changed?
    if(newSize> lastSize){ 
        //Doing reverse iteration from the end towards beginning 
        //by counting changed size units 
        for(int i=1; i<= newSize - lastSize; i++, it++ ){
            if(it->element == val){
                /****
                std::cout<<"Thread id: "<<std::this_thread::get_id();
                std::cout<<", Cash size enlarged by: "<<i<<": found element----> "<<it->element<<" : "<<val<<std::endl;
                ****/
                return;
            }
        }
    }
    
    // if not found required element, then add it
    
    if (_cash.size() < Max_Size) {
        aCounter++;
        Cell cell;
        cell.element = val;
        cell.result = result;
        _cash.push_back(cell);
    }
    
}

template<class T>
int SimpleCash4<T>::size() const {
    std::lock_guard<std::mutex> locker(_lock);
    
    return _cash.size();
}

template<class T>
void SimpleCash4<T>::_printCash() const {
     std::lock_guard<std::mutex> locker(_lock);
    std::cout << "Size= " << _cash.size() << std::endl;
    std::cout <<"Take() Counter= "<<tCounter<<", Add() Counter= "<<aCounter<<std::endl;
    int counter = 1;
    for (auto elem : _cash) {
        std::cout <<counter++<<": "<< elem.element << std::endl;
    }
}


#endif /* SIMPLECASH4_HPP */

