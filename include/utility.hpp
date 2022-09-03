#pragma once
#include <cstdlib>
#include <string>
#include <iostream>

namespace utility{
    int random(int to){
    return rand() % to+1;
    }
    void  startFunctione(){
        srand((unsigned int)time(0));
    }
    int HexToInt(std::string hex){
        //to-do
        return 0;
    }
    std::string IntToHex(int i){
        //to-do
        return "";
    }
}

