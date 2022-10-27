#include <cmath>
#include <iostream>

class rng{
    long long int seed;
    long long int mnum;
    public:
        rng(int sed = rand()){
            seed=sed;
            mnum = sed;
            if(seed<1000){
                seed = (sed*1000)+sed;
                mnum = seed;
            }
        };
        long long int getSeed(){
            return seed;
        }
        int r(int to){
            //std::cout << mnum << std::endl;
            mnum = mnum*(mnum+seed);//xxxxaaaaxxxx
            //std::cout << mnum << std::endl;
            mnum = (((mnum%10000000000)-(mnum%100000)))/100000;
            return (mnum%to);
        }
};