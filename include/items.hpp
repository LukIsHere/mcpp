#pragma once
#include <string>
namespace item{
    class item{
        public:
        int id;
        std::string emoji;
        std::string name;
        bool stackable;
            item(int idd,std::string emo,std::string nam,bool stackabled=true);
    };
    item getItem(int id);
}