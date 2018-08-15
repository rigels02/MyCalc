
/* 
 * File:   RoundUtill_simpleTest.cpp
 * Author: raitis
 *
 * Created on July 12, 2018, 3:12 PM
 */

#include <stdlib.h>
#include <iostream>
#include "RoundUtil.h"

/*
 * Simple C++ Test Suite
 */





double posv[] = {0.3025, 0.3123, 0.3512, 0.36123,0.39123};
double negv[] = {-0.3025, -0.3123, -0.3512, -0.36123, -0.39123};

static void rounder(int precision){
    double d=10.;
    double pw= pow(d,precision);
    
    for (auto val : posv) {
         std::cout<<val<<", ";
    }
     std::cout<<std::endl;
    double result;
    for (auto val : posv) {
        result = round(val*pw)/pw;
        std::cout<<result<<", ";
    }
    std::cout<<std::endl;
}

void mrounder(double arrVal[], int arrSz, const int precision){
   
    for(int i=0; i< arrSz; i++){
         std::cout<<arrVal[i]<<", ";
    }

     std::cout<<std::endl;
    double result;
    for(int i=0; i< arrSz; i++){
        result = RoundUtil::mround(arrVal[i], precision);
        std::cout<<result<<", ";
    }
    std::cout<<std::endl;
}

void testRound(){
    std::cout<<"Precision 1 digit"<<std::endl;
    rounder(1);
    std::cout<<"Precision 2 digit"<<std::endl;
    rounder(2);
    std::cout<<"Precision 3 digit"<<std::endl;
    rounder(3);
    std::cout<<"Precision 4 digit"<<std::endl;
    rounder(4);
    
}

void testMRound(){
    std::cout<< "SZ= "<<sizeof(posv)/sizeof(double)<<std::endl;
    int sz = sizeof(posv)/sizeof(double);
    std::cout<<"Precision 1 digit"<<std::endl;
    
    mrounder(posv ,sz, 1);
    std::cout<<"Precision 2 digit"<<std::endl;
    mrounder(posv ,sz, 2);
    std::cout<<"Precision 3 digit"<<std::endl;
     mrounder(posv ,sz, 3);
    std::cout<<"Precision 4 digit"<<std::endl;
    mrounder(posv ,sz, 4);
     std::cout<<"Precision 5 digit"<<std::endl;
    mrounder(posv ,sz, 5);
    
}

void testMRoundNeg(){
    std::cout<< "SZ= "<<sizeof(negv)/sizeof(double)<<std::endl;
    int sz = sizeof(negv)/sizeof(double);
    std::cout<<"Precision 1 digit"<<std::endl;
    
    mrounder(negv ,sz, 1);
    std::cout<<"Precision 2 digit"<<std::endl;
    mrounder(negv ,sz, 2);
    std::cout<<"Precision 3 digit"<<std::endl;
     mrounder(negv ,sz, 3);
    std::cout<<"Precision 4 digit"<<std::endl;
    mrounder(negv ,sz, 4);
    std::cout<<"Precision 5 digit"<<std::endl;
    mrounder(negv ,sz, 5);
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% RoundUtill_simpleTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testRound (RoundUtill_simpleTest)" << std::endl;
    testRound();
    std::cout << "%TEST_STARTED% testMRound (RoundUtill_simpleTest)" << std::endl;
    testMRound();
    std::cout << "%TEST_FINISHED% time=0 testMRound (RoundUtill_simpleTest)" << std::endl;
    
     std::cout << "%TEST_STARTED% testMRoundNeg (RoundUtill_simpleTest)" << std::endl;
    testMRoundNeg();
    std::cout << "%TEST_FINISHED% time=0 testMRoundNeg (RoundUtill_simpleTest)" << std::endl;

    
    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

