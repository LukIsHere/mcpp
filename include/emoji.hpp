#pragma once
#include <string>
namespace skin{
    class skin{
        public:
        std::string emoji;
        int id;
        std::string name;
        int cost;
        skin(std::string emo,int idd,std::string nam,int costt){
            emoji = emo;
            id = idd;
            name = nam;
            cost = costt;
        }
    };
    
    skin getSkin(int id);
}