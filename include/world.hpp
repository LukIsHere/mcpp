#pragma once
#include <iostream>
#include <string>
#include "blocks.hpp"
#include "emoji.hpp"
#include "dpp/dpp.h"
#include <cmath>
#include "translation.hpp"
#include <array>
#include "skin.hpp"
#include "money.hpp"
#include "inventory.hpp"
#include "ranking.hpp"
#include "DB.hpp"

#define overworld 0
#define nether 1
#define custom 2
#define b_none -1
namespace world{
    class block{
        public:
        int16_t b;
        int16_t prop;
        block(){
            b = 0;
            prop = 0;
        }
        block(int16_t block,int16_t p = 0){
            b = block;
            prop = p;
        }
    };
    class line{
            public:
            block b[10];
            line(){
                b[0] = -3;
            }
            line(int b1,int b2=-2,int b3=-2,int b4=-2,int b5=-2,int b6=-2,int b7=-2,int b8=-2,int b9=-2,int b10=-2){
                b[0] = b1;
                b[1] = b2;
                b[2] = b3;
                b[3] = b4;
                b[4] = b5;
                b[5] = b6;
                b[6] = b7;
                b[7] = b8;
                b[8] = b9;
                b[9] = b10;
            }
    };
    class structure{
            public:
            line s[10];
            int width;
            int heith;
            structure(int w,int h,line l1,line l2=line(),line l3=line(),line l4=line(),line l5=line(),line l6=line(),line l7=line(),line l8=line(),line l9=line(),line l10=line()){
                s[0] = l1;
                s[1] = l2;
                s[2] = l3;
                s[3] = l4;
                s[4] = l5;
                s[5] = l6;
                s[6] = l7;
                s[7] = l8;
                s[8] = l9;
                s[9] = l10;
                width = w;
                heith = h;
            }
    };
    class world{
        public:
            int lang = 0;
            inventory::inventory inv;
            std::atomic<int> afk = 0;
            block *w = nullptr;
            int height;
            int width;
            int playerSkin;
            int score;
            int durability;
            int x,y;
            int WorldT;
            bool debug=false;
            std::atomic<bool> valid;
            dpp::message msg;
            int64_t u;
            std::string name;
            std::atomic<bool> end;
            int id;
            std::string endtxt = "koniec";
            bool front;
            bool down;
            bool left;
            world(int worldType,int skin,int dur,int language,int64_t channel_id,int64_t guild_id,int64_t usr);
            ~world();
            void buttonHandler(const dpp::button_click_t& event);
            void connect(int64_t usr,std::string name);
            //get output
            std::string getWorld();//world to string
            std::string getDC();
            std::string getDcPoints();
            std::string getDcDeath();
            std::string getDcDebug();
            void updateMessage();
            //read world
            blocks::block getBlock(int dx,int dy);
            std::string getBlockEmoji(int dx,int dy);
            int getBlockId(int dx,int dy);
            int getBlockProp(int dx,int dy);
            //debug
            void ToggleDebug();
            bool afktick();
            void log();
            //structure
            void generate(int dx,int dy,structure s);
            //modifi world
            void setBlock(int dx,int dy,int b,int prop = 0);
            void drawCircle(int dx,int dy,int r,int block,int h=1,int w=1);
            void mirrorP(int sx,int sy,int dx,int dy,int block);
            void fill(int dx,int dy,int x2,int y2,int block);
            bool emptyblock(int dx,int dy);
            bool breakblock(int dx,int dy);
            //interaction with world
            void move(int xm,int ym);
            void finish(std::string reason="koniec");
            skins::spair getSkin();
    };
}

