#pragma once
#include <string>
#include <functional>
#include "interactinoTemp.hpp"
#include "blocks.hpp"
#include "items.hpp"
#include "jpp.hpp"
#include "dpp/dpp.h"
#include "inventory.hpp"
#include "money.hpp"

#define s_skin 0

namespace shops{
    class shopMeta{
        public:
            int size;
            std::function<bool(int,int64_t,int64_t)> buy;
            std::function<std::string(int,int64_t,int64_t)> page;
            shopMeta(int sized,std::function<bool(int,int64_t,int64_t)> buyf,std::function<std::string(int,int64_t,int64_t)> pagef){
                size = sized;
                buy = buyf;
                page = pagef;
            }
    };
    class shop : public itmp::itmp{
        public:
        int type = 0;
        int page = 0;
        int64_t u;
        int64_t guild;
        dpp::message msg;
        shop(int stype,int64_t usr,int64_t guild_id);
        ~shop();
        void next();
        void prev();
        void buy();
        void sync(dpp::message msgd);
        void buttonHandler(const dpp::button_click_t& event);
    };
    int sell(int64_t u,int64_t g,inventory::drop d);
    void setDb(jpp::jsDB& d,jpp::jsDB& dg);
    void setBot(dpp::cluster& bt);
}
extern const int shopI;