/* 
 * File:   SimpleCash_Test.cpp
 * Author: raitis
 *
 * Created on July 31, 2018, 7:06 PM
 */

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "SimpleCash.h"
#include "Vect3DCsh.h"

/*
 * Simple C++ Test Suite
 */


template<typename T>
void simpleCash_take_test(
        SimpleCash<T>& cash,const T& vect, 
        const std::pair<double,double>& expected,
        const int expected_size){
    
std::pair<double, double> result = cash.take(vect);
    if (expected.first != result.first ||
        expected.second != result.second    
            ) {
        std::cout << "%TEST_FAILED% time=0 testname=simpleCash_take_test (SimpleCash_Test) message=Result differ" << std::endl;
    }
    if(expected_size> -1){
    if(cash.size()!=expected_size){
         std::cout << "%TEST_FAILED% time=0 testname=simpleCash_take_test (SimpleCash_Test) message=Bad cash size! expected= "
                 <<expected_size << std::endl;
    
         }    
    }
}

void testTake() {
     SimpleCash<Vect3DCsh> simpleCash;
    Vect3DCsh vect(1.,1.,1.,0.1,0.1,0.1);
    std::pair<double,double> expected = std::make_pair(vect.result(),vect.result_error());
     simpleCash_take_test(simpleCash,vect,expected, 1 );
    
    Vect3DCsh vect1(1.,1.,1.,0.1,0.1,0.1);//vect1 == vect
     simpleCash_take_test(simpleCash,vect1,expected, 1 );
      
    Vect3DCsh vect2(2.,1.,1.,0.1,0.1,0.1);
    std::pair<double,double> expected2 = std::make_pair(vect2.result(),vect2.result_error());
     simpleCash_take_test(simpleCash,vect2,expected2, 2 );
     
    Vect3DCsh vect3(2.,1.2,1.,0.1,0.1,0.1);
    std::pair<double,double> expected3 = std::make_pair(vect3.result(),vect3.result_error());
     simpleCash_take_test(simpleCash,vect3,expected3,3 );
    
}

template <typename T>
void thread_test_task(SimpleCash<T>& cash){

    Vect3DCsh vect(1.,1.,1.,0.1,0.1,0.1);
    std::pair<double,double> expected = std::make_pair(vect.result(),vect.result_error());
     simpleCash_take_test(cash,vect,expected, -1 );
    
    Vect3DCsh vect1(1.,1.,1.,0.1,0.1,0.1);//vect1 == vect
     simpleCash_take_test(cash,vect1,expected, -1 );
      
    Vect3DCsh vect2(2.,1.,1.,0.1,0.1,0.1);
    std::pair<double,double> expected2 = std::make_pair(vect2.result(),vect2.result_error());
     simpleCash_take_test(cash,vect2,expected2, -1 );
     
    Vect3DCsh vect3(2.,1.2,1.,0.1,0.1,0.1);
    std::pair<double,double> expected3 = std::make_pair(vect3.result(),vect3.result_error());
     simpleCash_take_test(cash,vect3,expected3, -1 );
}

void test_thread_test_task(){

    SimpleCash<Vect3DCsh> simpleCash;
    std::vector<std::thread> mythreads;
    auto start = std::chrono::high_resolution_clock::now();
    for(int i=1; i<=10; i++){
      mythreads.push_back( std::thread(thread_test_task<Vect3DCsh> ,std::ref(simpleCash) ));
    }
    for (int i=0; i<mythreads.size(); i++) {
        mythreads[i].join();
    }
    auto stop = std::chrono::high_resolution_clock::now();
    std::cout<<"Elapsed time= "<<std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count()<<" ms"<<std::endl;
    if(simpleCash.size()!=3){
        std::cout << "%TEST_FAILED% time=0 testname=test_thread_test_task (SimpleCash_Test) message=Bad cash size! expected= 3"
                << std::endl;
    }
}

template <typename T>
void thread_test_task_1(SimpleCash<T>& cash){

    Vect3DCsh vectors[]={
        Vect3DCsh(1.,1.,1.,0.1,0.1,0.1),
        Vect3DCsh(1.1,1.,1.,0.1,0.1,0.1),
        Vect3DCsh(1.,1.2,1.,0.1,0.1,0.1),
        Vect3DCsh(1.,1.,1.3,0.1,0.1,0.1),
        Vect3DCsh(1.,1.,1.,0.1,0.1,0.1), //duplicate
        Vect3DCsh(1.4,1.,1.,0.1,0.1,0.1),
        Vect3DCsh(1.,1.5,1.,0.1,0.1,0.1),
        Vect3DCsh(1.,1.,1.6,0.1,0.1,0.1),
        Vect3DCsh(1.,1.,1.,0.1,0.1,0.1), //duplicate
        Vect3DCsh(1.7,1.,1.5,0.1,0.1,0.1)
    };
    std::pair<double,double> expected[]={
        std::make_pair(vectors[0].vect.module(),vectors[0].vect.module_error()),
        std::make_pair(vectors[1].vect.module(),vectors[1].vect.module_error()),
        std::make_pair(vectors[2].vect.module(),vectors[2].vect.module_error()),
        std::make_pair(vectors[3].vect.module(),vectors[3].vect.module_error()),
        std::make_pair(vectors[4].vect.module(),vectors[4].vect.module_error()),
        std::make_pair(vectors[5].vect.module(),vectors[5].vect.module_error()),
         std::make_pair(vectors[6].vect.module(),vectors[6].vect.module_error()),
        std::make_pair(vectors[7].vect.module(),vectors[7].vect.module_error()),
        std::make_pair(vectors[8].vect.module(),vectors[8].vect.module_error()),
        std::make_pair(vectors[9].vect.module(),vectors[9].vect.module_error()) 
    };

   
    for(int i=0; i< sizeof(vectors)/sizeof(Vect3DCsh); i++){
         simpleCash_take_test(cash,vectors[i],expected[i], -1 );
    }

}


void test_thread_test_task_1(){

    SimpleCash<Vect3DCsh> simpleCash;
    //thread_test_task_1(simpleCash);
    
    std::vector<std::thread> mythreads;
    auto start = std::chrono::high_resolution_clock::now();
    for(int i=1; i<=10; i++){
      mythreads.push_back( std::thread(thread_test_task_1<Vect3DCsh> ,std::ref(simpleCash) ));
    }
    for (int i=0; i<mythreads.size(); i++) {
        mythreads[i].join();
    }
    auto stop = std::chrono::high_resolution_clock::now();
    std::cout<<"Elapsed time= "<<std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count()<<" ms"<<std::endl;
    
    simpleCash.printCash();
    
    int sz = simpleCash.size();
    std::cout<<"Sz= "<<sz<<std::endl;
    
    
    if(simpleCash.size()!=8){
        std::cout << "%TEST_FAILED% time=0 testname=test_thread_test_task_1 (SimpleCash_Test) message=Bad cash size! expected= 8"
                << std::endl;
    }
    
     
}


template <typename T>
void random_gen_task(SimpleCash<T>& cash, int vectNums){
    double lower_bound = 1.0;
   double upper_bound = 10.0;
   std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
   std::default_random_engine re;
    
    //int vectNums= 100;
    Vect3DCsh* vectors;
    std::pair<double,double>* expected;
    
    vectors = new Vect3DCsh[vectNums];
    expected = new std::pair<double,double>[vectNums];
    for(int i=0; i< vectNums; i++){
        double x= unif(re), y= unif(re), z=unif(re);
        vectors[i]= Vect3DCsh(x, y, z, 0.1, 0.1, 0.1);
        expected[i]= std::make_pair(vectors[i].result(), vectors[i].result_error());
    }
    
    for(int i=0; i< vectNums; i++){
         simpleCash_take_test(cash,vectors[i],expected[i], -1 );
    }
    
    //----clean------//
    delete[] vectors;
    delete[] expected;
}

void test_random_gen_tasks(){

    SimpleCash<Vect3DCsh> simpleCash;
    //thread_test_task_1(simpleCash);
    int vectNums = 200;
    std::vector<std::thread> mythreads;
    auto start = std::chrono::high_resolution_clock::now();
    for(int i=1; i<=10; i++){
      mythreads.push_back( std::thread(random_gen_task<Vect3DCsh> ,std::ref(simpleCash), vectNums));
    }
    for (int i=0; i<mythreads.size(); i++) {
        mythreads[i].join();
    }
    auto stop = std::chrono::high_resolution_clock::now();
    std::cout<<"Elapsed time= "<<std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count()<<" ms"<<std::endl;
    
    int sz = simpleCash.size();
    std::cout<<"Elements in cash= "<<sz<<std::endl;
    
    simpleCash.printCash();
    
    /***
    if(simpleCash.size()!=vectNums){
        std::cout << "%TEST_FAILED% time=0 testname=test_random_gen_tasks (SimpleCash_Test) message=Bad cash size! expected= XX"
                << std::endl;
    }
    */
     
}



int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% SimpleCash_Test" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    /**/
    std::cout << "%TEST_STARTED% testTake (SimpleCash_Test)" << std::endl;
    testTake();
    std::cout << "%TEST_FINISHED% time=0 testTake (SimpleCash_Test)" << std::endl;

    std::cout << "%TEST_STARTED% test_thread_test_task (SimpleCash_Test)" << std::endl;
    test_thread_test_task();
    std::cout << "%TEST_FINISHED% time=0 test_thread_test_task (SimpleCash_Test)" << std::endl;
    /**/
    std::cout << "%TEST_STARTED% test_thread_test_task_1 (SimpleCash_Test)" << std::endl;
    test_thread_test_task_1();
    std::cout << "%TEST_FINISHED% time=0 test_thread_test_task_1 (SimpleCash_Test)" << std::endl;

    std::cout << "%TEST_STARTED% test_random_gen_tasks (SimpleCash_Test)" << std::endl;
    test_random_gen_tasks();
    std::cout << "%TEST_FINISHED% time=0 test_random_gen_tasks (SimpleCash_Test)" << std::endl;

    
    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

