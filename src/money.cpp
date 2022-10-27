#include "money.hpp"

int money::have(int64_t user,int64_t guild){
    return db_p->get(user)->objGet(std::to_string(guild))->objGet("money")->intGet();
};
void money::add(int amount,int64_t user,int64_t guild){
    *(db_p->get(user)->objGet(std::to_string(guild))->objGet("money")->intGetP()) += amount;
};
void money::remove(int amont,int64_t user,int64_t guild){
    *(db_p->get(user)->objGet(std::to_string(guild))->objGet("money")->intGetP()) -= amont;
};
bool money::can(int amont,int64_t user,int64_t guild){
    return have(user,guild)>=amont;
};