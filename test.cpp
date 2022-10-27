#include <iostream>
#include "include/RNG.hpp"

int main(){
    rng rnd(199);
    for(int i = 0;i<20;i++){
        std::cout << rnd.r(10) << std::endl;
    }
}