#pragma once
#include "DB.hpp"
#include "blocks.hpp"
#include "items.hpp"
#include "jpp.hpp"

namespace inventory{
    class drop{
        public:
            int id;
            bool block;
            int quantity;
            drop(int idd,bool blockd,int q=1);
    };
    class slot{
        private:
            jpp::json* slt;
            jpp::json* block;
            jpp::json* qan;
            jpp::json* id;
            jpp::json* exist;
        public:
            slot(jpp::json *slot_p);
            std::string getEmoji();
            void set(drop p);
            int tryAdd(int q);
            void remove(int q);
            void clear();
            bool isEmpty();
            bool isBlock();//true=block false-item
            int getId();
            int q();
            jpp::json* get();
    };
    class inventory{
            int64_t u;
            int64_t guild;
        public:
            slot slots[36];//0-8 main 9-35 rest
            inventory(int64_t user,int64_t guild);
            std::string toString();
            //modification
            void tryAdd(drop d);
            void add(item::item item,int q = 1);//specyfic item
            void add(blocks::block blok,int q = 1);//specyfic item
            void remove(item::item item,int q=1);//specyfic item
            void remove(blocks::block blok,int q=1);//specyfic item
            void clear();//all
            //read
            int has(item::item);
            int has(blocks::block);
            bool emptySpace();//any empty slot
            bool emptySpace(item::item);
            bool emptySpace(blocks::block);
            //refference
            slot& getSlot(int p);
            //shop
            bool Sell(item::item item,int q = 1);
            bool Sell(blocks::block blok,int q = 1);
            bool Sell(drop d,int q = 1);
            //data
            std::string itemList();
            std::string dcFormat();
    };
    drop StringToDrop();
}
