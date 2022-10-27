#include "inventory.hpp"
#include "shop.hpp"
#include <iostream>
//drop
inventory::drop::drop(int idd,bool blockd,int q,int va){
    id = idd;
    block = blockd;
    quantity = q;
    v = va;
}
inventory::drop::drop(items::item& i,int q){
    id = i.id;
    block = false;
    quantity = q;
    v = 0;
};
inventory::drop::drop(blocks::block& b,int va,int q){
    id = b.id;
    block = true;
    quantity = q;
    v = va;
};
inventory::drop::drop(const items::item& i,int q){
    id = i.id;
    block = false;
    quantity = q;
    v = 0;
};
inventory::drop::drop(const blocks::block& b,int va,int q){
    id = b.id;
    block = true;
    quantity = q;
    v = va;
};
//slot
inventory::slot::slot(){

}
inventory::slot::slot(jpp::json *slot_p){
    slt = slot_p;
    if(!slt->objExist("q")){
        id = slt->objGet("id");
        qan = slt->objGet("q");
        v = slt->objGet("v");
        block = slt->objGet("block");
        clear();
    }else{
        id = slt->objGet("id");
        qan = slt->objGet("q");
        v = slt->objGet("v");
        block = slt->objGet("block");
    }
    
    
    
    
};
std::string inventory::slot::getEmoji(){
    if(block->boolGet()==true){
        return blocks::getEmoji(id->intGet());
    }else{
        return items::getEmoji(id->intGet());
    }
    return blocks::getEmoji(0);
};
bool inventory::slot::is(drop p){
    return (block->boolGet() == p.block&&id->intGet() == p.id&&v->intGet() == p.v);
}
void inventory::slot::set(drop p){
    block->set(p.block);
    qan->set(p.quantity);
    id->set(p.id);
    v->set(p.v);
};
inventory::drop inventory::slot::expot(){
    return drop(id->intGet(),block->boolGet(),qan->intGet(),v->intGet());
};
int inventory::slot::tryAdd(int q){
    int now = qan->intGet();
    if(now+q>64){
        qan->set(64);
        return (now+q)-64;
    }
    qan->set(now+q);
    return 0;
};

int inventory::slot::remove(int qa){
    int aq = qan->intGet();
    if(aq-qa<=0){
        clear();
        return qa-aq;
    }else{
        qan->set(aq-qa);
        return 0;
    }
};
void inventory::slot::clear(){
    block->set(false);
    qan->set(0);
    id->set(0);
    v->set(0);
};

bool inventory::slot::isEmpty(){
    return qan->intGet()==0;
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
void inventory::inventory::loopInv(std::function<void(slot&,int)> f){
    for(int i = 0;i<36;i++){
        f(slots[i],i);
    }
}
inventory::inventory::inventory(int64_t user,int64_t guild_id){
    u = user;
    guild = guild_id;
    jpp::json* inv_p = db_p->get(user)->objGet(std::to_string(guild))->objGet("inv");
    for(int i = 0;i<36;i++){
        slots[i] = inv_p->arrGet(i);
    }
};
//helper
int inventory::inventory::whereSpacefor(drop d){
    int slt = -1;
    loopInv([&d,&slt](slot& s,int i){
        if(s.is(d)){
            if(s.q()<64){
                slt = i;
            }
        }
        if(s.isEmpty()){
            if(slt==-1){
                slt = i;
            }
        }
    });
    return slt;
};
//modification
void inventory::inventory::add(drop d){
    int toAdd = d.quantity;
    
    loopInv([&toAdd,&d](slot& s,int i){//slots with item
        if(toAdd==0)return;
        if(s.is(d))toAdd = s.tryAdd(toAdd);
    });
    loopInv([&toAdd,&d](slot& s,int i){//empty slots
        if(toAdd==0)return;
        if(s.isEmpty()){
            d.quantity=0;
            s.set(d);
            toAdd = s.tryAdd(toAdd);
        }
    });
};
void inventory::inventory::remove(drop d){
    int toDel = d.quantity;
    loopInv([toDel,&d](slot& s,int i){
        if(toDel==0)return;
        if(s.is(d)){
            s.remove(toDel);
        }
    });
};//specyfic item
void inventory::inventory::clear(){
    loopInv([](slot& s,int i){
        s.clear();
    });
};//all
//read
int inventory::inventory::has(drop d){
    int out = 0;
    loopInv([&out,&d](slot& s,int i){
        if(s.is(d)){
            out+=s.q();
        }
    });
    return out;
};
bool inventory::inventory::emptySpace(){
    bool out = false;
    loopInv([&out](slot& s,int i){
        if(out)return;
        if(s.isEmpty()){
            out = true;
        }
    });
    return out;
};//any empty slot
bool inventory::inventory::emptySpace(drop d){
    int needed = d.quantity;
    loopInv([&needed,&d](slot& s,int i){
        if(needed==0)return;
        if(s.is(d)){
            if(s.q()==64){
                return;
            }
            if(needed<64-s.q()){
                needed = 0;
                return;
            }else{
                needed-=64-s.q();
            }
        }
    });
    if(needed==0)return true;
    loopInv([&needed,&d](slot& s,int i){
        if(s.isEmpty()){
            if(needed-64<0){
                needed=0;
            }else{
                needed-=64;
            }
        }
    });
    if(needed==0)return true;
    return false;
};
//take
bool inventory::inventory::take(drop d){
    for(int i = 0;i<36;i++){
        if(slots[i].is(d)){
            slots[i].remove(1);
            return true;
        }
    }
    return false;
};
//refference
inventory::slot& inventory::inventory::getSlot(int p){
    return slots[p];
};
//shop
int inventory::inventory::Sell(drop d){
    
    int have = has(d);
    d.quantity = have;
    remove(d);
    return shops::sell(u,guild,d);
    
};
int inventory::inventory::SellSlot(int s,int q){
    drop tosell = slots[s].expot();
    if(tosell.quantity>=q){
        tosell.quantity=q;
        slots[s].remove(q);
    }else{
        return 0;
    }
    int ear = shops::sell(u,guild,tosell);
    return ear;
};
int inventory::inventory::SellSlot(int s){
    drop tosell = slots[s].expot();
    int ear = shops::sell(u,guild,tosell);
    slots[s].clear();
    return ear;
};
int inventory::inventory::SellAll(){
    int ear = 0;
    for(int i = 0;i<36;i++){
        if(!slots[i].isEmpty()){
            ear += shops::sell(u,guild,slots[i].expot());
            slots[i].clear(); 
        }
        
    }
    return ear;
}
//data
std::string inventory::inventory::itemList(){
    return "";
};
std::string inventory::inventory::dcFormat(){
    std::string out;
    loopInv([&out](slot& s,int i){
        if(!s.isEmpty())
        out.append(std::to_string(i)+". "+s.getEmoji()+" : "+std::to_string(s.q())+'\n');
    });
    return out;
};