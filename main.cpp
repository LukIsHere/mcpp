#include "include/world.hpp"
#include "dpp/dpp.h"
#include "lsudms.hpp"
#include <thread>
#include "include/console.hpp"

std::map<int64_t,world::world*> gry;
ums::db data("database","usr.txt");

ums::list supporteds("975773240381276160,1001193922883751977,1009477093177954366,988752879055667200,1008434141487960074,857272269675167764,969499841765990420,942887041526534174,880770095847211038,870291355329499186");

void gameEnd(world::world *w){
    std::string scoreT;
    if(w->WorldT==0)scoreT = "score";
    else if(w->WorldT==1)scoreT = "scoren";
    data.get(w->u)->set("name",w->name);
    int old = data.get(w->u)->geti(scoreT);
    if(old<w->score){
        data.get(w->u)->set(scoreT,w->score);
        data.save();
    }
}
void delgame(int64_t u){
    if(gry[u]!=nullptr){
        gameEnd(gry[u]);
        delete gry[u];
    }
    gry.erase(u);
}

ums::list ow(".start,.start ow,.start overworld");
ums::list nt(".start n,.start nether");
ums::list sow(".ranking,.ranking ow,.ranking overworld");
ums::list snt(".ranking n,.ranking nether");
ums::list tow(".top,.top ow,.top overworld");
ums::list tnt(".top n,.top nether");
ums::list bow(".best,.best ow,.best overworld");
ums::list bnt(".best n,.best nether");



int64_t tu;
int main(){
    data.load();
    std::ifstream test2("token.txt");
    std::string token;
    getline(test2, token);
    test2.close();
    dpp::cluster bot = dpp::cluster(token, dpp::i_default_intents | dpp::i_message_content | dpp::i_guild_messages | dpp::i_guild_integrations);
    bot.on_log(dpp::utility::cout_logger());
    bot.on_message_create([&bot](const dpp::message_create_t& event){
        if(event.msg.content.at(0)=='.'&&event.msg.guild_id==dpp::snowflake(975773240381276160)&&event.msg.channel_id!=dpp::snowflake(985934606559739964)&&event.msg.author.id!=537649475494215690){
            bot.message_delete(event.msg.id,event.msg.channel_id);
            return;
        }
        if(!supporteds.include(std::to_string(int64_t(event.msg.guild_id))))return;
        int64_t u = event.msg.author.id;
        if(ow.include(event.msg.content)){
                if(gry[u]!=nullptr)delgame(u);
                gry[u] = new world::world(0);
                gry[u]->name = event.msg.author.username;
                dpp::message mess = dpp::message(event.msg.channel_id,gry[u]->getDC());
                dpp::component btns = dpp::component();
                btns.add_component(dpp::component().set_label("").set_type(dpp::cot_button).set_emoji("◀️").set_style(dpp::cos_primary).set_id("l"));
                btns.add_component(dpp::component().set_label("").set_type(dpp::cot_button).set_emoji("🔽").set_style(dpp::cos_primary).set_id("d"));
                btns.add_component(dpp::component().set_label("").set_type(dpp::cot_button).set_emoji("▶️").set_style(dpp::cos_primary).set_id("r"));
                btns.add_component(dpp::component().set_label("").set_type(dpp::cot_button).set_emoji("🛑").set_style(dpp::cos_danger).set_id("stop"));
                mess.add_component(btns);
                mess.set_channel_id(event.msg.channel_id);
                mess = bot.message_create_sync(mess);
                gry[u]->msg = mess;
                gry[u]->u = u;
                std::thread end([&bot](int64_t u){
                    int idea  = gry[u]->id;
                    std::this_thread::sleep_for(std::chrono::minutes(5));
                    if(gry[u]==nullptr)return;
                    if(gry[u]->valid,gry[u]->id==idea){
                        world::world *game = gry[u];
                        gry[u]->finish("konic czasu");
                        bot.message_edit(gry[u]->msg.set_content(gry[u]->getDC()));
                        delgame(u);
                    }
                    
                },u);
                end.detach();
        }
        if(nt.include(event.msg.content)){
                if(gry[u]!=nullptr)delgame(u);
                gry[u] = new world::world(1);
                gry[u]->name = event.msg.author.username;
                dpp::message mess = dpp::message(event.msg.channel_id,gry[u]->getDC());
                dpp::component btns = dpp::component();
                btns.add_component(dpp::component().set_label("").set_type(dpp::cot_button).set_emoji("◀️").set_style(dpp::cos_primary).set_id("l"));
                btns.add_component(dpp::component().set_label("").set_type(dpp::cot_button).set_emoji("🔽").set_style(dpp::cos_primary).set_id("d"));
                btns.add_component(dpp::component().set_label("").set_type(dpp::cot_button).set_emoji("▶️").set_style(dpp::cos_primary).set_id("r"));
                btns.add_component(dpp::component().set_label("").set_type(dpp::cot_button).set_emoji("🛑").set_style(dpp::cos_danger).set_id("stop"));
                mess.add_component(btns);
                mess.set_channel_id(event.msg.channel_id);
                mess = bot.message_create_sync(mess);
                gry[u]->msg = mess;
                gry[u]->u = u;
                std::thread end([&bot](int64_t u){
                    int idea  = gry[u]->id;
                    std::this_thread::sleep_for(std::chrono::minutes(5));
                    if(gry[u]==nullptr)return;
                    if(gry[u]->valid,gry[u]->id==idea){
                        world::world *game = gry[u];
                        gry[u]->finish("konic czasu");
                        bot.message_edit(gry[u]->msg.set_content(gry[u]->getDC()));
                        delgame(u);
                    }
                    
                },u);
                end.detach();
        }
        if(sow.include(event.msg.content)){
            std::string out = "Ranking :\n";
            out.append(data.topBy("score").out());
            event.send(out);
        }
        if(snt.include(event.msg.content)){
            std::string out = "Ranking :\n";
            out.append(data.topBy("scoren").out());
            event.send(out);
        }
        if(bow.include(event.msg.content)){
            std::string out = "Twój najlepszy wynik to :  ";
            out.append(std::to_string(data.get(u)->geti("score")));
            event.reply(out);
        }
        if(bnt.include(event.msg.content)){
            std::string out = "Twój najlepszy wynik to :  ";
            out.append(std::to_string(data.get(u)->geti("scoren")));
            event.reply(out);
        }
        if(event.msg.content==".dev"){
            event.send("Programista :\n-luk#3380");
        }
        if(event.msg.content==".f3"){
            if(gry[u]!=nullptr){
                gry[u]->debug = true;
                bot.message_edit(gry[u]->msg.set_content(gry[u]->getDC()));
            }
        }
        if(event.msg.content==".help"){
            event.send("Komędy  : \n.lang (pl/en) - zniana języka (nie dostępne)\n.start (ow/n) - zaczyna grę\n.ranking (ow/n) - pokazuje globalny ranking\n.best (ow/n) - najlepszy wynik\n.top (ow/n) - pokazuje serwerowe top  (nie dostępne)\n.dev - pokazuje twórce bot'a\n");
        }
        
    });
    bot.on_button_click([&bot](const dpp::button_click_t &event){
        int64_t u = event.command.member.user_id;
        world::world *w = gry[u];
        if(w!=nullptr&&w->valid&&w->msg.channel_id==event.command.channel_id&&w->msg.id == event.command.msg.id){
            if(event.custom_id=="l")w->move(-1,0);
            if(event.custom_id=="r")w->move(1,0);
            if(event.custom_id=="d")w->move(0,-1);
            if(event.custom_id=="stop")w->finish("zakończono gre");
            event.reply(dpp::ir_update_message,w->msg.set_content(w->getDC()));
            if(gry[u]->end)delgame(u);
        }

    });
    
    bot.start(false);
}