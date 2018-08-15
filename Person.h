
/* 
 * File:   Person.h
 * Author: raitis
 *
 * Created on July 30, 2018, 6:59 PM
 */

#ifndef PERSON_H
#define PERSON_H

#include <iostream>


class Person {

public:

    
    Person(std::string name, int age=0) :
    name(name), age(age) {
    }
    int GetAge() const {
        return age;
    }

    void SetAge(const int age) {
        this->age = age;
    }

    std::string GetName() const {
        return name;
    }

    void SetName(const std::string name) {
        this->name = name;
    }
    
   
    /**
     * Default comparator for Person class.
     * For usage Person as key in associated containers like: set , map...
     * @param right
     * @return 
     */
    bool operator<(const Person& right) const {
        return this->name<right.name;
    }

    
private:
    std::string name;
    int         age; 
   
    
    friend std::ostream& operator<<(std::ostream& os, const Person& obj) {
        os<<"Person ["<<obj.name<<", "<<obj.age<<" ]";
        return os;
    }

};


#endif /* PERSON_H */

