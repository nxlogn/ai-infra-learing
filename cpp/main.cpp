#include <iostream>
#include <random>

int main() { 
    std::mt19937 mt1{123}; 
    std::cout<<mt1();
}
