#pragma once
#include <string>
#include "DB.hpp"



namespace skins{
    class spair{
        public:
            std::string t;
            std::string b;
            spair(){
                
            };
            spair(std::string top,std::string bottom){
                t = top;
                b = bottom;
            };
            ~spair(){

            }
    };
    class skin{
        public:
            spair emoji[6];
            int id;
            std::string name;
            int cost;
            skin(skins::spair emo1,skins::spair emo2,skins::spair emo3,skins::spair emo4,skins::spair emo5,skins::spair emo6,int idd,std::string nam,int costt);
    };
    bool haveSkin(int id,int64_t user,int64_t guild);
    void giveSkin(int id,int64_t user,int64_t guild);
    void setSkin(int id,int64_t user,int64_t guild);
    int getSetSkin(int64_t user,int64_t guild);
    skin* getSkin(int id);
}
extern const int skinI;