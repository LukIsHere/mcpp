#include "inventory.hpp"

//drop
inventory::drop::drop(int idd,bool blockd,int q){
    id = idd;
    block = blockd;
    quantity = q;
}
//slot
inventory::slot::slot(jpp::json *slot_p){
    slt = slot_p;
    if(!slt->objExist("exist")){
        (*slt)["exist"] = false;
    }
    id = slt->objGet("id");
    qan = slt->objGet("q");
    exist = slt->objGet("exist");
    block = slt->objGet("block");
    if(isEmpty())clear();
};
std::string inventory::slot::getEmoji(){
    if(block->boolGet()==true){
        return blocks::get(id->intGet()).getEmoji();
    }else{
        return item::getItem(id->intGet()).emoji;
    }
    return blocks::get(0).getEmoji();
};
void inventory::slot::set(drop p){
    *block = p.block;
    *qan = p.quantity;
    *id = p.id;
    *exist = true;
};
int inventory::slot::tryAdd(int q){
    int now = qan->intGet();
    if(now+q>64){
        qan->set(64);
        return (now+q)-64;
    }
    qan->set(now-q);
    return 0;
};

void inventory::slot::remove(int qa){
    (*qan)=qan->intGet()-qa;
};
void inventory::slot::clear(){
    (*block) = 0;
    (*qan) = 0;
    (*id) = 0;
    (*exist) = false;
};
bool inventory::slot::isEmpty(){
    return (*exist).boolGet();
};
bool inventory::slot::isBlock(){
    return block->boolGet();
};//true=block false-item
int inventory::slot::getId(){
    return id->intGet();
};
int inventory::slot::q(){
    return qan->intGet();
};
//inventory