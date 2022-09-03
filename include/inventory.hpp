#pragma once
#include "blocks.hpp"
#include "items.hpp"

namespace inventory{
    class slot{
        bool empty;
        bool block;//true=block false-item
        int id;
        int q;
        //to-do
    };
    class inventory{
        slot slots[36];//0-8 main 9-35 rest
        inventory();
        inventory(std::string data);
        std::string toString();
        //modification
        void set(int sid,slot);//specyfic slot
        void swap(int sid1,int sid2);
        void add(item::item item,int q = 1);//specyfic item
        void add(blocks::block blok,int q = 1);//specyfic item
        void add(slot slot);//specyfic item
        void remove(item::item item,int q=1);//specyfic item
        void remove(blocks::block blok,int q=1);//specyfic item
        void remove(slot slot,int q=1);//specyfic item
        void remove(int sid,int q=1);//specyfic slot
        void clear(item::item item);//specyfic item
        void clear(blocks::block blok);//specyfic item
        void clear(slot slot);//specyfic item
        void clear(int sid);//specyfic slot
        void clear();//all
        //read
        int getEmpty();//-1=none
        void getWith(item::item item);//specyfic item -1=none
        void getWith(blocks::block blok);//specyfic item -1=none
        void getwith(slot slot);//specyfic item -1=none
        bool have(item::item item,int q=1);//specyfic item
        bool have(blocks::block blok,int q=1);//specyfic item
        bool have(slot slot,int q=1);//specyfic item
        int hm(item::item item);//specyfic item
        int hm(blocks::block blok);//specyfic item
        int hm(slot slot);//specyfic item
        slot get(int sid);//specyfic slot
        //get asset
        std::string getEmoji(int sid);//specyfic slot
    };
}
