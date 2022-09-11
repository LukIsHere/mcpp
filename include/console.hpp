#pragma  once
#include <string>
#include <iostream>
class cnsl{
    public:
    std::string last;
    bool first = true;
    int times = 1;
        cnsl(){
            std::cout << "[main] console log aktywny" << std::endl;
        }
        template<typename T>
        void log(T cos){
            std::stringstream str;
            str << cos;
            if(str.str()==last){
                times++;
            }else{
                if(first){}
                else std::cout << "x" << times << std::endl;
                std::cout << "[silnik] " << cos << " ";
                times = 1;
                first = false;
                last = str.str();
            }
            
        }
};
cnsl  console;


