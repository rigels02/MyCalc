
/* 
 * File:   Vect3Dtest.cpp
 * Author: raitis
 *
 * Created on July 12, 2018, 9:22 PM
 */

#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <stdbool.h>
#include <chrono>
#include <vector>
#include <set>
#include <map>
#include <thread>
#include <unordered_map>
#include "Vect3D.h"

#define TIMING
 
#ifdef TIMING
#define INIT_TIMER auto start = std::chrono::high_resolution_clock::now();
#define START_TIMER  start = std::chrono::high_resolution_clock::now();
#define STOP_TIMER(name)  std::cout << "RUNTIME of " << name << ": " << \
    std::chrono::duration_cast<std::chrono::milliseconds>( \
            std::chrono::high_resolution_clock::now()-start \
    ).count() << " ms " << std::endl; 
#define SLEEP(tim) std::this_thread::sleep_for(std::chrono::milliseconds(tim));
#else
#define INIT_TIMER
#define START_TIMER
#define STOP_TIMER(name)
#define SLEEP(tim)
#endif

/*
 * Simple C++ Test Suite
 */

void testForSet() {

    std::set<Vect3D> myvect;
    myvect.insert(Vect3D(1.2, 1.3, 1.1, 0.1, 0.1, 0.1));
    myvect.insert(Vect3D(1., 1., 1., 0.1, 0.1, 0.1));
    myvect.insert(Vect3D(1., 1., 1., 0.01, 0.01, 0.01));
    myvect.insert(Vect3D(1.2, 1.1, 1.1, 0.1, 0.1, 0.1));
    myvect.insert(Vect3D(1.1, 1.1, 1.1, 0.1, 0.1, 0.1));
    myvect.insert(Vect3D(1.2, 1.1, 1.1, 0.1, 0.1, 0.01));
    myvect.insert(Vect3D(1.2, 1.1, 1.1, 0.1, 0.1, 0.1)); //duplicated

    std::cout << "Set values:" << std::endl;
    for (auto elem : myvect) {
        std::cout << elem << std::endl;
    }
    if (myvect.size() != 6) {
        std::cout << "%TEST_FAILED% time=0 testname=testForSet (Vect3Dtest) message= myvect size error" << std::endl;
    }
    //Map of vector and its value -  pair of module,module_error
    std::map<Vect3D, std::pair<double, double>> mymap;
    INIT_TIMER
    SLEEP(2000); //2sec
    STOP_TIMER("diff")
    
    START_TIMER
    Vect3D vect(1.2, 1.3, 1.1, 0.1, 0.1, 0.1);
    mymap[vect] = std::make_pair(vect.module(), vect.module_error());
    Vect3D vect1(1., 1., 1., 0.1, 0.1, 0.1);
    mymap[vect1] = std::make_pair(vect1.module(), vect1.module_error());
    Vect3D vect2(1., 1., 1., 0.01, 0.01, 0.01);
    mymap[vect2] = std::make_pair(vect2.module(), vect2.module_error());
    Vect3D vect3(1.2, 1.1, 1.1, 0.1, 0.1, 0.1);
    mymap[vect3] = std::make_pair(vect3.module(), vect3.module_error());
    Vect3D vect4(1.1, 1.1, 1.1, 0.1, 0.1, 0.1);
    mymap[vect4] = std::make_pair(vect4.module(), vect4.module_error());
    Vect3D vect5(1.2, 1.1, 1.1, 0.1, 0.1, 0.01);
    mymap[vect5] = std::make_pair(vect5.module(), vect5.module_error());
    STOP_TIMER("MAPTime ms")
    
    std::cout << "Map size= " << mymap.size()<< ", Map values:" << std::endl;
    for (auto elem : mymap) {
        std::cout << elem.first << " => " << elem.second.first << " : " << elem.second.second << std::endl;
    }

    std::map<Vect3D, std::pair<double, double>>::iterator it = mymap.find(Vect3D(1.2, 1.1, 1.1, 0.1, 0.1, 0.1));

    if (it == mymap.end()) {
        std::cout << "%TEST_FAILED% time=0 testname=testForSet (Vect3Dtest) message= mymap element not found error!" << std::endl;

    }

    it = mymap.find(Vect3D(1.2, 1.1, 1.1, 0.1, 0.1, 0.001));

    if (it != mymap.end()) {
        std::cout << "%TEST_FAILED% time=0 testname=testForSet (Vect3Dtest) message= mymap element not found error_1 !" << std::endl;
    }

}

void testVect3D_with_vector(){

        std::vector<Vect3D> myvect;
    myvect.push_back(Vect3D(1.2, 1.3, 1.1, 0.1, 0.1, 0.1));
    myvect.push_back(Vect3D(1., 1., 1., 0.1, 0.1, 0.1));
    myvect.push_back(Vect3D(1., 1., 1., 0.01, 0.01, 0.01));
    myvect.push_back(Vect3D(1.2, 1.1, 1.1, 0.1, 0.1, 0.1));
    myvect.push_back(Vect3D(1.1, 1.1, 1.1, 0.1, 0.1, 0.1));
    myvect.push_back(Vect3D(1.2, 1.1, 1.1, 0.1, 0.1, 0.01));
    myvect.push_back(Vect3D(1.2, 1.1, 1.1, 0.1, 0.1, 0.1)); //duplicated
    
     std::cout << "Vector size= " << myvect.size()<< ", Vector values:" << std::endl;
    for (auto elem : myvect) {
        std::cout << elem << std::endl;
    }
     std::vector<Vect3D>::iterator it;
    it = std::find(myvect.begin(),myvect.end(),Vect3D(1., 1., 1., 0.01, 0.01, 0.01));
    if(it!= myvect.end()){
        std::cout<<"Found: "<<*it<<std::endl;
    }else
        std::cout<<"Not Found!"<<std::endl;

    //sort vector...
    std::sort(myvect.begin(), myvect.end());
    
     std::cout << "Vector size= " << myvect.size()<< ", After Sort Vector values:" << std::endl;
    for (auto elem : myvect) {
        std::cout << elem << std::endl;
    }
    
}


/**
 * For unordered_map not implemented yet.
 * The hash function has to be implemented for Vect3D.
 */
void testVect3D_with_unordered_map(){

    double d1= 1.0;
    double d2= 1.1;
    double d3=1.2;
    std::cout<<"H(1.0)= "<<std::hash<double>()(d1)<<std::endl;
     std::cout<<"H(1.1)= "<<std::hash<double>()(d2)<<std::endl;
      std::cout<<"H(1.2)= "<<std::hash<double>()(d3)<<std::endl<<"===============\n";
     
      
    std::map<Vect3D, std::pair<double, double>> mymap;
    Vect3D vect(1.2, 1.3, 1.1, 0.1, 0.1, 0.1);
    mymap[vect] = std::make_pair(vect.module(), vect.module_error());
    Vect3D vect1(1., 1., 1., 0.1, 0.1, 0.1);
    mymap[vect1] = std::make_pair(vect1.module(), vect1.module_error());
    Vect3D vect2(1., 1., 1., 0.01, 0.01, 0.01);
    mymap[vect2] = std::make_pair(vect2.module(), vect2.module_error());
    Vect3D vect3(1.2, 1.1, 1.1, 0.1, 0.1, 0.1);
    mymap[vect3] = std::make_pair(vect3.module(), vect3.module_error());
    Vect3D vect4(1.1, 1.1, 1.1, 0.1, 0.1, 0.1);
    mymap[vect4] = std::make_pair(vect4.module(), vect4.module_error());
    Vect3D vect5(1.2, 1.1, 1.1, 0.1, 0.1, 0.01);
    mymap[vect5] = std::make_pair(vect5.module(), vect5.module_error());
    //-----//
    Vect3D vect6(1.2, 1.1, 1.1, 0.1, 0.1, 0.01); //duplicated element!!
    mymap.insert({ vect6,std::make_pair(vect6.module(), vect6.module_error()) });

    std::cout << "Map size= " << mymap.size() << ", Map values:" << std::endl;
    for (auto elem : mymap) {
        std::cout << elem.first << " => " << elem.second.first << " : " << elem.second.second << std::endl;
    }

    if (mymap.size() != 7) {
        std::cout << "%TEST_FAILED% time=0 testname=testVect3D_with_unordered_map (Vect3Dtest) message= mymap size error" << std::endl;
    }
}

void testModule() {
    Vect3D vect3D(1., 1., 1., 0, 0, 0);

    double expResult = sqrt(3.);
    double result = vect3D.module();
    double delta = 0.0;
    std::cout << "Expected = " << expResult << " ,vect1.module= " << result << " ,delta= " << delta << std::endl;
    bool ok = std::fabs(expResult - result) <= delta;
    if (!ok /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testModule (Vect3Dtest) message=error 1" << std::endl;
    }
    //----//
    double x = 1.001, y = 1.0003, z = 1.0004, dx = 0.001, dy = 0.001, dz = 0.001;
    Vect3D vect1(x, y, z, dx, dy, dz);

    result = vect1.module();
    delta = vect1.module_error();
    std::cout << "Expected = " << expResult << " ,vect1.module= " << result << " ,delta= " << delta << std::endl;
    ok = std::fabs(expResult - result) <= delta;
    if (!ok /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testModule (Vect3Dtest) message=error 2" << std::endl;
    }
    //----//
     x=1.0005; y=1.0003; z=1.0004; dx=0.001; dy=0.001; dz=0.001; //line 55
    Vect3D vect2(x, y, z, dx, dy, dz);

    result = vect2.module();
    delta = vect2.module_error();
    std::cout << "Expected = " << expResult << " ,vect2.module= " << result << " ,delta= " << delta << std::endl;
    ok = std::fabs(expResult - result) <= delta;
    if (!ok /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testModule (Vect3Dtest) message=error 3" << std::endl;
    }
    //----//
     x=1.0005; y=2.0003; z=3.0004; dx=0.001; dy=0.001; dz=0.001; //line 63
    Vect3D vect3(x, y, z, dx, dy, dz);
    expResult = sqrt(14.);
    result = vect3.module();
    delta = vect3.module_error();
    std::cout << "Expected = " << expResult << " ,vect3.module= " << result << " ,delta= " << delta << std::endl;
    ok = std::fabs(expResult - result) <= delta;
    if (!ok /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testModule (Vect3Dtest) message=error 4" << std::endl;
    }
    //----//
    x=100.0005; y=20.0003; z=300.0004; dx=0.001; dy=0.001; dz=0.001; //line 73
    Vect3D vect4(x, y, z, dx, dy, dz);
    expResult = sqrt(10000.+400.+90000.);
    result = vect4.module();
    delta = vect4.module_error();
    std::cout << "Expected = " << expResult << " ,vect4.module= " << result << " ,delta= " << delta << std::endl;
    ok = std::fabs(expResult - result) <= delta;
    if (!ok /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testModule (Vect3Dtest) message=error 5" << std::endl;
    }
    //----//
     x=300.0005; y=300.0003; z=300.0004; dx=0.001; dy=0.001; dz=0.001; //line 82
    Vect3D vect5(x, y, z, dx, dy, dz);
    expResult = sqrt(90000.+90000.+90000.);
    result = vect5.module();
    delta = vect5.module_error();
    std::cout << "Expected = " << expResult << " ,vect5.module= " << result << " ,delta= " << delta << std::endl;
    ok = std::fabs(expResult - result) <= delta;
    if (!ok /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testModule (Vect3Dtest) message=error 6" << std::endl;
    }
}

void testEQ(){
    Vect3D vect1(1., 1., 1., 0.001, 0.001, 0.001);
    Vect3D vect2(1., 1., 1., 0.001, 0.001, 0.001);
    
    bool eq = vect1 == vect2;
    std::cout<<vect1<<"=="<<vect2<<" =>"<<(eq?"true":"false")<<std::endl;
    if (!eq /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testEQ (Vect3Dtest) message=error 1" << std::endl;
    }
    Vect3D vect11(1., 1., 1., 0.001, 0.001, 0.001);
    Vect3D vect21(1., 1., 1., 0.0001, 0.001, 0.001);
    vect1 = vect11;
    vect2 = vect21;
    eq = vect1 == vect2;
    std::cout<<vect1<<"=="<<vect2<<" =>"<<(eq?"true":"false")<<std::endl;
    if (eq /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testEQ (Vect3Dtest) message=error 2" << std::endl;
    }
    Vect3D vect12(1., 1., 1., 0.001, 0.001, 0.001);
    Vect3D vect22(1., 1., 1.0001, 0.001, 0.001, 0.001);
    vect1 = vect12;
    vect2 = vect22;
    eq = vect1 == vect2;
    std::cout<<vect1<<"=="<<vect2<<" =>"<<(eq?"true":"false")<<std::endl;
    if (eq /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testEQ (Vect3Dtest) message=error 2" << std::endl;
    }
    Vect3D vect13(1000.00001, 1., 1., 0.001, 0.001, 0.001);
    Vect3D vect23(1000.00001, 1., 1., 0.001, 0.001, 0.001);
    vect1 = vect13;
    vect2 = vect23;
    eq = vect1 == vect2;
    std::cout<<vect1<<"=="<<vect2<<" =>"<<(eq?"true":"false")<<std::endl;
    if (!eq /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testEQ (Vect3Dtest) message=error 2" << std::endl;
    }
    Vect3D vect14(1000.00001, 1., 1., 0.001, 0.001, 0.001);
    Vect3D vect24(1000.00002, 1., 1., 0.001, 0.001, 0.001);
    vect1 = vect14;
    vect2 = vect24;
    eq = vect1 == vect2;
    std::cout<<vect1<<"=="<<vect2<<" =>"<<(eq?"true":"false")<<std::endl;
    if (eq /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testEQ (Vect3Dtest) message=error 2" << std::endl;
    }
}

void testEQDouble(){
    double v1 = 1.0;
    double v2 = 1.0;
    bool eq = v1 == v2;
     std::cout<<v1<<"=="<<v2<<" =>"<<(eq?"true":"false")<<std::endl;
    if ( !eq /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testEQDouble (Vect3Dtest) message=error " << std::endl;
    }
    v1= 1.004; v2=  1.005; 
    eq = v1 == v2;
     std::cout<<v1<<"=="<<v2<<" =>"<<(eq?"true":"false")<<std::endl;
    if ( eq /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testEQDouble (Vect3Dtest) message=error " << std::endl;
    }
     
    v1= 1.0000004; v2=  1.0000005; 
    eq = v1 == v2;
     std::cout<<v1<<"=="<<v2<<" =>"<<(eq?"true":"false")<<std::endl;
    if ( eq /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testEQDouble (Vect3Dtest) message=error " << std::endl;
    }
    
     v1= 1.0000003999; v2=  1.0000003999; 
    eq = v1 == v2;
     std::cout<<v1<<"=="<<v2<<" =>"<<(eq?"true":"false")<<std::endl;
    if ( !eq /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testEQDouble (Vect3Dtest) message=error " << std::endl;
    } 
    v1= 1.00000000399988765; v2=  1.00000000399988765; 
    eq = v1 == v2;
     std::cout<<v1<<"=="<<v2<<" =>"<<(eq?"true":"false")<<std::endl;
    if ( !eq /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testEQDouble (Vect3Dtest) message=error " << std::endl;
    }  
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% Vect3Dtest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testModule (Vect3Dtest)" << std::endl;
    testModule();
    std::cout << "%TEST_FINISHED% time=0 testModule (Vect3Dtest)" << std::endl;

    std::cout << "%TEST_STARTED% testEQ (Vect3Dtest)" << std::endl;
    testEQ();
    std::cout << "%TEST_FINISHED% time=0 testEQ (Vect3Dtest)" << std::endl;
    
    std::cout << "%TEST_STARTED% testEQDouble (Vect3Dtest)" << std::endl;
    testEQDouble();
    std::cout << "%TEST_FINISHED% time=0 testEQDouble (Vect3Dtest)" << std::endl;
    
     std::cout << "%TEST_STARTED% testForSet (Vect3Dtest)" << std::endl;
    testForSet();
    std::cout << "%TEST_FINISHED% time=0 testForSet (Vect3Dtest)" << std::endl;
    
     std::cout << "%TEST_STARTED% testVect3D_with_unordered_map (Vect3Dtest)" << std::endl;
    testVect3D_with_unordered_map();
    std::cout << "%TEST_FINISHED% time=0 testVect3D_with_unordered_map (Vect3Dtest)" << std::endl;
    
     std::cout << "%TEST_STARTED% testVect3D_with_vector (Vect3Dtest)" << std::endl;
    testVect3D_with_vector();
    std::cout << "%TEST_FINISHED% time=0 testVect3D_with_vector (Vect3Dtest)" << std::endl;
    
    
    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

