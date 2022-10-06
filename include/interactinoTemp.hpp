#pragma once
#include <atomic>
namespace itmp
{
    class itmp{
        public:
            int afk = 0;
            itmp(){
                
            }
            bool afkTick(){
                afk++;
                if(afk>3){
                    return true;
                }
                return false;
            }
            void rAfk(){
                afk = 0;
            }

    };
}
