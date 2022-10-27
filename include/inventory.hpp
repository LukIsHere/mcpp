#pragma once
#include "DB.hpp"
#include "blocks.hpp"
#include "items.hpp"
#include "jpp.hpp"
#include <functional>

namespace inventory{
    class drop{
        public:
            int id;
            bool block;
            int quantity;
            int v;
            drop(int idd,bool blockd,int q=1,int va = 0);
            drop(items::item& i,int q = 1);
            drop(blocks::block& b,int va = 0,int q =1);
            drop(const items::item& i,int q = 1);
            drop(const blocks::block& b,int va = 0,int q =1);
    };
    class slot{
        private:
            jpp::json* slt = nullptr;
            jpp::json* block = nullptr;
            jpp::json* qan = nullptr;
            jpp::json* id = nullptr;
            jpp::json* v = nullptr;
            jpp::json* exist = nullptr;
        public:
            slot();
            slot(jpp::json *slot_p);
            std::string getEmoji();
            void set(drop p);
            bool is(drop p);
            int tryAdd(int q);
            int remove(int q);
            void clear();
            bool isEmpty();
            bool isBlock();//true=block false-item
            int getId();
            int q();
            drop expot();
            jpp::json* get();
    };
    class inventory{
            int64_t u;
            int64_t guild;
            int whereSpacefor(drop d);
            void loopInv(std::function<void(slot&,int)>f);
        public:
            slot slots[36];//0-8 main 9-35 rest
            inventory(int64_t user,int64_t guild_id);
            //modification
            void add(drop item);//specyfic item
            void remove(drop d);//specyfic item
            void clear();//all
            //read
            int has(drop d);
            bool emptySpace();//any empty slot
            bool emptySpace(drop d);
            //take
            bool take(drop d);//geting block from eq
            //refference
            slot& getSlot(int p);
            //shop
            int Sell(drop d);
            int SellSlot(int s,int q);
            int SellSlot(int s);
            int SellAll();
            //data
            std::string itemList();
            std::string dcFormat();
    };
    drop StringToDrop();
}
