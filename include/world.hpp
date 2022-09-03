#pragma once
#include <iostream>
#include <string>
#include "blocks.hpp"
#include "emoji.hpp"
#include "dpp/dpp.h"
#include <cmath>
#define overworld 0;
#define nether 1;
#define custom 2;
namespace world{
    
    class world{
        public:
            int16_t *w = nullptr;
            int height;
            int width;
            int playerSkin;
            int score;
            int durability;
            int x,y;
            int WorldT;
            bool debug=false;
            bool valid;
            dpp::message msg;
            int64_t u;
            std::string name;
            bool end;
            int id;
            std::string endtxt = "koniec";
            world();
            world(int worldType,int skin=0,int dur=260);
            world(std::string form);//string to world
            ~world();
            void connect(dpp::message ms,int64_t usr);
            //get output
            std::string getWorld();//world to string
            std::string getDC();
            //read world
            blocks::block getBlock(int dx,int dy);
            int getBlockId(int dx,int dy);
            //debug
            void log();
            //modifi world
            void setBlock(int dx,int dy,blocks::block block);
            void setBlock(int dx,int dy,int block);
            void drawCircle(int dx,int dy,int r,int block,int h=1,int w=1);
            void mirrorP(int sx,int sy,int dx,int dy,int block);
            void fill(int dx,int dy,int x2,int y2,int block);
            //interaction with world
            void move(int xm,int ym);
            void finish(std::string reason="koniec");
    };
}

