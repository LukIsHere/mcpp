#include "shop.hpp"
#include "DB.hpp"
#include "skin.hpp"
#include "inventory.hpp"
#include <iostream>
#include "DB.hpp"


// extern dpp::cluster* bot;
// extern jpp::jsDB* db;
// extern jpp::jsDB* dbGuilds;

const shops::shopMeta shopList[] = {
    shops::shopMeta(9,[](int page,int64_t u,int64_t g){
        int cost = skins::getSkin(page)->cost;
        int have = money::have(u,g);
        
        std::cout << cost << ":" << have << ":" << g << std::endl;
        if(have>=cost&&!skins::haveSkin(page,u,g)){
            money::remove(cost,u,g);
            skins::giveSkin(page,u,g);
            return true;
        }
        return false;
    },[](int page,int64_t u,int64_t g){
        std::string out;
        bool have = skins::haveSkin(page,u,g);
        std::string air = blocks::getEmoji(b_air);
        std::string dirt = blocks::getEmoji(b_dirt);
        std::string grass = blocks::getEmoji(b_grass);
        std::string havee;
        if(have){
            havee = "✅";
        }else{
            havee = "❌";
        }
        out.append("bal : "+std::to_string(money::have(u,g))+"$\n");
        out.append(skins::getSkin(page)->name+" : "+std::to_string(skins::getSkin(page)->cost)+"$"+"\n");
        out.append(air+air+air+air+air+"\n");
        out.append(air+air+skins::getSkin(page)->emoji[0].t+air+air+"\n");
        out.append(air+air+skins::getSkin(page)->emoji[0].b+air+air+"\n");
        out.append(air+grass+grass+grass+air+"\n");
        out.append(grass+dirt+havee+dirt+grass+"\n");
        return out;
    })
};
 
 const int shopI = sizeof(shopList)/sizeof(shops::shopMeta);

//shop class
        shops::shop::shop(int stype,int64_t usr,int64_t guild_id){
            page = 0;
            type = stype;
            u = usr;
            guild = guild_id;
            msg.set_content("shop");
            msg.add_embed(dpp::embed().set_title("shop").set_footer(dpp::embed_footer().set_text("Powered by DPP").set_icon("https://cdn.discordapp.com/icons/825407338755653642/f0b2c332297b6ca7bd3ca2af90ace20e.webp?size=96")));
            msg.embeds[0].set_description(shopList[type].page(page,u,guild));
            dpp::component btns = dpp::component();
            btns.add_component(dpp::component().set_label("").set_type(dpp::cot_button).set_emoji("◀️").set_style(dpp::cos_primary).set_id("p"));
            btns.add_component(dpp::component().set_label("").set_type(dpp::cot_button).set_emoji("🪙").set_style(dpp::cos_primary).set_id("buy"));
            btns.add_component(dpp::component().set_label("").set_type(dpp::cot_button).set_emoji("▶️").set_style(dpp::cos_primary).set_id("n"));
            msg.add_component(btns);
        };
        shops::shop::~shop(){
            bot_p->message_delete(msg.id,msg.channel_id);
        };
        void shops::shop::next(){
            afk = 0;
            if(page+1>=shopList[type].size)return;
            page++;
            msg.embeds[0].set_description(shopList[type].page(page,u,guild));
        };
        void shops::shop::prev(){
            afk = 0;
            if(page-1<0)return;
            page--;
            msg.embeds[0].set_description(shopList[type].page(page,u,guild));
        };
        void shops::shop::buy(){
            afk = 0;
            std::cout << "kupuje" << std::endl;
            shopList[type].buy(page,u,guild);
            msg.embeds[0].set_description(shopList[type].page(page,u,guild));
        };
        void shops::shop::sync(dpp::message msgd){
            msg = msgd;
        };
        void shops::shop::buttonHandler(const dpp::button_click_t& event){
            if(event.custom_id=="p")prev();
            if(event.custom_id=="buy")buy();
            if(event.custom_id=="n")next();
            event.reply(dpp::ir_update_message,msg);
        };
//other functions
int shops::sell(int64_t u,int64_t g,inventory::drop d){
    if(d.block){
        int v = blocks::get(d.id).point*d.quantity;
        money::add(v,u,g);
        return v;
    }else{
        int v = items::get(d.id).value*d.quantity;
        money::add(v,u,g);
        return v;
    }
}
