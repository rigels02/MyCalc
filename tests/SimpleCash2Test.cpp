/* 
 * File:   SimpleCash2Test.cpp
 * Author: raitis
 *
 * Created on August 7, 2018, 11:03 AM
 */

#include <stdlib.h>
#include <iostream>
#include <random>
#include "SimpleCash2.h"
#include "Vect3DCsh.h"

/*
 * Simple C++ Test Suite
 */

template<typename T>
void SimpleCash2_take_test(
        SimpleCash2<T>& cash,const T& vect, 
        const std::pair<double,double>& expected,
        const int expected_size){
    
std::pair<double, double> result = cash.take(vect);
    if (expected.first != result.first ||
        expected.second != result.second    
            ) {
        std::cout<<"Error: "<<vect<<std::endl;
        std::cout<<"first expected:result: "<<expected.first<<":"<<result.first<<std::endl;
        std::cout<<"second expected:result: "<<expected.second<<":"<<result.second<<std::endl;
        std::cout << "%TEST_FAILED% time=0 testname=SimpleCash2_take_test (SimpleCash_Test) message=Result differ" << std::endl;
    }
    if(expected_size> -1){
    if(cash.size()!=expected_size){
         std::cout << "%TEST_FAILED% time=0 testname=SimpleCash2_take_test (SimpleCash_Test) message=Bad cash size! expected= "
                 <<expected_size << std::endl;
    
         }    
    }
}



void testTake() {
    SimpleCash2<Vect3DCsh> simpleCash;
    Vect3DCsh vectors[]={
        Vect3DCsh(1.,1.,1.,0.1,0.1,0.1),
         Vect3DCsh(1.,1.,1.,0.1,0.1,0.1), //duplicated
         Vect3DCsh(2.,1.,1.,0.1,0.1,0.1),
        Vect3DCsh(2.,1.2,1.,0.1,0.1,0.1)
    };
    std::pair<double,double> expected[]={
         std::make_pair(vectors[0].result(),vectors[0].result_error()),
         std::make_pair(vectors[1].result(),vectors[1].result_error()),
         std::make_pair(vectors[2].result(),vectors[2].result_error()),
         std::make_pair(vectors[3].result(),vectors[3].result_error()),
    };
    
    for(int i=0; i< sizeof(vectors)/sizeof(Vect3DCsh); i++){
        
     SimpleCash2_take_test(simpleCash,vectors[i],expected[i], -1 );
     
    }
   
    simpleCash._printCash();
    
    if (simpleCash.size() != 3) {
        std::cout << "%TEST_FAILED% time=0 testname=testTake (SimpleCash2Test) message=error size not 3!" << std::endl;
    }
}

template <typename T>
void thread_test_task_1(SimpleCash2<T>& cash){

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
         SimpleCash2_take_test(cash,vectors[i],expected[i], -1 );
    }

}

void test_thread_test_task_1(){

    SimpleCash2<Vect3DCsh> simpleCash;
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
    
    int sz = simpleCash.size();
    std::cout<<"Sz= "<<sz<<std::endl;
    
    simpleCash._printCash();
    
    
    if(simpleCash.size()!=8){
        std::cout << "%TEST_FAILED% time=0 testname=test_thread_test_task_1 (SimpleCash_Test) message=Bad cash size! expected= 8"
                << std::endl;
    }
    
     
}

template <typename T>
void random_gen_task(SimpleCash2<T>& cash, int vectNums){
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
         SimpleCash2_take_test(cash,vectors[i],expected[i], -1 );
    }
    
    //----clean------//
    delete[] vectors;
    delete[] expected;
}

void test_random_gen_tasks(){

    SimpleCash2<Vect3DCsh> simpleCash;
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
    std::cout<<"Sz= "<<sz<<std::endl;
    
    simpleCash._printCash();
    
    
    if(simpleCash.size()!=vectNums){
        std::cout << "%TEST_FAILED% time=0 testname=test_random_gen_tasks (SimpleCash_Test) message=Bad cash size! expected= 8"
                << std::endl;
    }
    
     
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% SimpleCash2Test" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testTake (SimpleCash2Test)" << std::endl;
    testTake();
    std::cout << "%TEST_FINISHED% time=0 testTake (SimpleCash2Test)" << std::endl;

    
    std::cout << "%TEST_STARTED% test_thread_test_task_1 (SimpleCash2Test)" << std::endl;
    test_thread_test_task_1();
    std::cout << "%TEST_FINISHED% time=0 test_thread_test_task_1 (SimpleCash2Test)" << std::endl;
    
     std::cout << "%TEST_STARTED% test_random_gen_tasks (SimpleCash2Test)" << std::endl;
     test_random_gen_tasks();
    std::cout << "%TEST_FINISHED% time=0 test_random_gen_tasks (SimpleCash2Test)" << std::endl;
     
    
    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

