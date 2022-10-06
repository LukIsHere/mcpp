#pragma once
#include "jpp.hpp"
#include <string>
#include "inventory.hpp"

namespace user{
        class userPtr{
                public:
                    inventory::inventory inv;
                    int64_t* money;
                    jpp::json* user;
                    userPtr(jpp::json *usr);
                    //money
                    int64_t MoneyGet();
                    void MoneyAdd();
                    void MoneyRemove();
                    bool MoneyHas();
                    //skin
                    int getSkin();
                    void setSkin();
                    //destructor
                    ~userPtr();//save inventory
        };
}
