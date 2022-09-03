#pragma once
#include <string>
#define l_systr 0
#define l_pl 1
#define l_en 2
//texty
#define tr_punkty 0
namespace tr{
    class translation
    {
    public:
        std::string tra[3];
        translation(std::string pl,std::string  en,std::string sysname){
            tra[l_systr] = sysname;
            tra[l_pl] = pl;
            tra[l_en] = en;

        };
    };
    std::string getTR(int id,int lang);
}