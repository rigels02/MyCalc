
/* 
 * File:   main.cpp
 * Author: raitis
 *
 * Created on July 12, 2018, 3:08 PM
 */

#include <cstdlib>
#include <limits>
#include <cstring>

#include "RoundUtil.h"

#include <set>
#include <map>
#include "Person.h"

using namespace std;


inline uint64_t doubleToRawBits(double x) {
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
bool AreSame(double a, double b) {
    cout<<"AreSame... ";
    return std::fabs(a - b) < std::numeric_limits<double>::epsilon();
}

/**
 * Compare doubles and returns true if they are equal or false.
 * Comparing is done by converting doubles to raw bits and compare by bits.
 * @param a
 * @param b
 * @return true - if equal, false - otherwise
 */
bool AreSame_1(double a, double b) {
    cout<<"AreSame_1... ";
    uint64_t longA = doubleToRawBits(a);
    uint64_t longB = doubleToRawBits(b);
   return longA == longB ;
}



/*
 * 
 */
int main(int argc, char** argv) {
   
    bool (*ASame)(double a, double b) = &AreSame_1;
    
    cout<< "1. = "<< doubleToRawBits(1.)<<endl;
     cout<< "1.0000001 = "<< doubleToRawBits(1.0000001)<<endl;
    
    cout<< "double epsilon: "<< std::numeric_limits<double>::epsilon()<<endl;
   
    cout<<"1., 1.:Are same?: "<<ASame(1., 1.)<< endl;
    cout<<"Are same?: "<<ASame(1., 1.000000001)<< endl;
    cout<<"Are same?: "<<ASame(1., 1.00000000000001)<< endl;
     cout<<"Are same?: "<<ASame(1000000., 1000000.00000000000000)<< endl; 
     cout<<"Are same?: "<<ASame(1000000., 1000000.0000000001)<< endl; 
     cout<<"Are same?: "<<ASame(1000000., 1000000.00000000001)<< endl; 
     
    //----Person ----//
    
     
     Person p1("Name4",11);
     Person p2("Name3",22);
     Person p3("Name2",33);
     Person pd("Name4",77);//duplicate Name4
     Person p4("Name1",44);
     std::set<Person> persons;
     
     persons.insert(p1); persons.insert(p2);persons.insert(p3);persons.insert(p4);
     persons.insert(pd);//duplicate.It will not be inserted.
     
     for (auto elem : persons) {
         std::cout<<elem<<std::endl;
    }
    p2.SetName("Changed Name"); 
    std:set<Person>::iterator it= persons.find(Person("Name3"));
    if(it!= persons.end()){
        
        std::cout<<"Found: "<<*it<<std::endl;
       Person person_to_update = *it;
       persons.erase(it);
       person_to_update.SetName("Changed name");
       persons.insert(person_to_update);
       
    }
    std::cout<<"Persons after update:"<<std::endl;
     for (auto elem : persons) {
         std::cout<<elem<<std::endl;
    }
    //Lets build associated container map with key as person and related
    // value as number of children.
    std::map<Person,int> persons_child;
    persons_child[Person("Name1",23)] = 1;
    persons_child[Person("Name2",33)] = 2;
    persons_child[Person("Name3",43)] = 3;
    persons_child[Person("Name2",43)] = 4;// duplicate by name= Name2!
    
    //The value for key Person.name=Name2 becomes updated, but not Person's age! 
     std::cout<<"Persons Child map :"<<std::endl;
     for (auto elem : persons_child) {
         std::cout<<elem.first<<",Children= "<<elem.second<<std::endl;
    }
    //find person (key,value) by name = Name2 and update key for age=43
    std::map<Person,int>::iterator itk =  persons_child.find(Person("Name2"));
    if(itk != persons_child.end()){
        std::cout<<"Found: "<<itk->first<<", Childs= "<<itk->second <<", update age to 43"<<std::endl;
        Person p_key = itk->first;
        int p_v = itk->second;
        p_key.SetAge(43);
        persons_child.erase(itk); //erase old key,value
        persons_child[p_key] = p_v; //put new key,value
        
    }
    
    std::cout<<"Persons Child map after update :"<<std::endl;
     for (auto elem : persons_child) {
         std::cout<<elem.first<<",Children= "<<elem.second<<std::endl;
    }
     
    return 0;
}

