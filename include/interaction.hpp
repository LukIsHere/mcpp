#pragma once
#include "world.hpp"
#include "ranking.hpp"
#include "dpp/dpp.h"
#include "DB.hpp"
#include <thread>
#include <chrono>
#include "logger.hpp"
#include "jpp.hpp"
#include "shop.hpp"

#define i_undefined -1
#define i_world 0
#define i_shop 1

namespace  interaction{
    class interaction{
        private:
            void* ptr = nullptr;
        public:
            int afk;
            int type;
            bool valid = true;
            interaction();
            interaction(world::world* w);
            interaction(shops::shop* s);
            shops::shop& getShop();
            world::world& getWorld();
            ~interaction();


    };
    void addGame(int dimension,const dpp::message_create_t& event,dpp::cluster& bot,int lang,int ussages = 260);
    void addGame(int dimension,const dpp::slashcommand_t& event,dpp::cluster& bot,int lang,int ussages = 260);
    void addShop(const dpp::message_create_t& event,int type,int lang);
    void endGame(world::world& w);
    void toggleDebug(int64_t u);
    void afktick();
    interaction& get(int64_t u);
    bool exist(int64_t u);
    void button(const dpp::button_click_t& event);
}