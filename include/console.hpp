#pragma  once
#include <string>
#include <iostream>
class cnsl{
    public:
        cnsl(){

        }
        template<typename T>
        void log(T cos){
            std::cout << cos << std::endl;
        }
};
cnsl  console;


