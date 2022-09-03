#include "include/items.hpp"


//int itemIndex = 0; may be buggy
//class item{
        //public:
        //int id;
        //std::string emoji;
        //std::string name;
            item::item::item(int idd,std::string emo,std::string nam,bool stackabled){
                id = idd;
                emoji = emo;
                name = nam;
                stackable = stackabled;
                //itemIndex++;
            };
    //};
    item::item items[] = {

    };
    item::item item::getItem(int id){
        return items[id];
    };