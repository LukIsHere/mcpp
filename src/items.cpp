#include "items.hpp"


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
        item::item(0,"<:0:1012260493756465162>","?",true),
        item::item(1,"<:1_:1026118250863538208>","iron_ingot",true),
        item::item(2,"<:2_:1026118252226686976>","gold_ingot",true),
        item::item(3,"<:3_:1026118253619191930>","copper_ingot",true),
        item::item(4,"<:4_:1026118255070412891>","diamond",true),
        item::item(5,"<:5_:1026118256525840394>","netherite_ingot",true),
        item::item(6,"<:6_:1026118258069360692>","raw_iron",true),
        item::item(7,"<:7_:1026118259075981383>","raw_gold",true),
        item::item(8,"<:8_:1026118261110222848>","raw_copper",true),
        item::item(9,"<:9_:1026118262670495924>","sweet_berry",true),
        item::item(10,"<:10:1026118264025251980>","bone",true),
        item::item(11,"<:11:1026118265132556471>","fish",true),

    };
    //          
    item::item item::getItem(int id){
        if(id>=sizeof(items) / sizeof(item)) return items[0];
        return items[id];
    };