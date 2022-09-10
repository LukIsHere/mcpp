#include "include/world.hpp"
#include "dpp/dpp.h"
#include "lsudms.hpp"
#include <thread>
#include <chrono>
#include "include/console.hpp"

std::map<int64_t,world::world*> gry;
ums::db data("database","usr.txt");
bool end = false;

ums::list supporteds("975773240381276160,1001193922883751977,1009477093177954366,988752879055667200,1008434141487960074,857272269675167764,969499841765990420,942887041526534174,880770095847211038,870291355329499186");

void gameEnd(world::world *w){
    console.log(w->name+" zakończył grę");
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
bool gameExist(int64_t u){
    return (gry.find(u) != gry.end());
}
void delgame(int64_t u){
    if(gameExist(u)){
        
        if(!gry[u]->valid)return
        gameEnd(gry[u]);
        delete gry[u];
        gry.erase(u);
    }
}
int getLang(int64_t dcID){
    if(data.data.find(dcID)==data.data.end()){
        return l_pl;
    }else{
        int lang = data.data[dcID].data.find("lang")->second.gint();
        if(lang==l_pl)return l_pl;
        if(lang==l_en)return l_en;
    }
    return l_pl;
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
    std::thread gmClean([&bot](){
    while(!end){
            std::this_thread::sleep_for(std::chrono::seconds::duration(15));
            console.log(" tick anty afka");
            int64_t u;
            std::map<int64_t,world::world*>::iterator it;
            for(it = gry.begin();it!=gry.end();it++){
                u = it->first;
                if(gry[u]->valid){
                    if(gry[u]->afktick()){
                        gry[u]->finish(gry[u]->name+bylafk.tra[gry[u]->lang]);
                        bot.message_edit(gry[u]->msg.set_content(gry[u]->getDC()));
                        delgame(u);
                    }
                }else{
                    gry.erase(u);
                }
            }
        }
        
    });
    gmClean.detach();
    
    bot.on_log(dpp::utility::cout_logger());
    bot.on_message_create([&bot](const dpp::message_create_t& event){
        int64_t u = event.msg.author.id;
        int lang = getLang(u);
        if(event.msg.content.at(0)=='.'&&event.msg.guild_id==dpp::snowflake(975773240381276160)&&event.msg.channel_id!=dpp::snowflake(985934606559739964)&&event.msg.author.id!=537649475494215690){
            bot.message_delete(event.msg.id,event.msg.channel_id);
            return;
        }
        if(!supporteds.include(std::to_string(int64_t(event.msg.guild_id))))return;
        
        if(ow.include(event.msg.content)){
                console.log(event.msg.author.username+" tworzy grę w overworldzie na serwerze "+std::to_string(+event.msg.guild_id));
                if(gameExist(u)){
                    gry[u]->finish(gry[u]->name + nowagra.tra[lang]);
                    bot.message_edit(gry[u]->msg.set_content(gry[u]->getDC()));
                    delgame(u);
                };
                gry[u] = new world::world(0,0,260,lang);
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
        }
        if(nt.include(event.msg.content)){
                console.log(event.msg.author.username+" tworzy grę w netherze na serwerze "+std::to_string(+event.msg.guild_id));
                if(gameExist(u)){
                    console.log("gra istnieje");
                    gry[u]->finish(gry[u]->name + nowagra.tra[lang]);
                    bot.message_edit(gry[u]->msg.set_content(gry[u]->getDC()));
                    delgame(u);
                };
                gry[u] = new world::world(1,0,260,lang);
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
        }
        if(sow.include(event.msg.content)){
            std::string out = ranking.tra[lang];
            out.append(data.topBy("score").out());
            console.log(event.msg.author.username+" sprawdza ranking");
            event.send(out);
        }
        if(snt.include(event.msg.content)){
            std::string out = ranking.tra[lang];
            out.append(data.topBy("scoren").out());
            console.log(event.msg.author.username+" sprawdza ranking");
            event.send(out);
        }
        if(bow.include(event.msg.content)){
            std::string out = twojnajwynik.tra[lang];
            out.append(std::to_string(data.get(u)->geti("score")));
            console.log(event.msg.author.username+" sprawdza wynik");
            event.reply(out);
        }
        if(bnt.include(event.msg.content)){
            std::string out = twojnajwynik.tra[lang];
            out.append(std::to_string(data.get(u)->geti("scoren")));
            console.log(event.msg.author.username+" sprawdza wynik");
            event.reply(out);
        }
        if(event.msg.content==".dev"){
            event.send("Programista :\n-luk#3380");
        }
        if(event.msg.content==".f3"){
            if(gameExist(u)){
                gry[u]->debug = true;
                bot.message_edit(gry[u]->msg.set_content(gry[u]->getDC()));
            }
        }
        if(event.msg.content==".help"){
            event.send(commands.tra[lang]);
        }
        if(event.msg.content==".lang pl"){
            data.data[u].set("lang",l_pl);
            console.log(event.msg.author.username+" zmienia język na polski");
            event.send("znieniono język na polski");
        }
        if(event.msg.content==".lang en"){
            data.data[u].set("lang",l_en);
            console.log(event.msg.author.username+" zmienia język na angielski");
            event.send("changed language to english");
        }
        if(event.msg.content==".ping")event.reply("pong");
        
    });
    bot.on_button_click([&bot](const dpp::button_click_t &event){
        int64_t u = event.command.member.user_id;
        if(!gameExist(u))return;
        world::world *w = gry[u];
        if(w!=nullptr&&w->valid&&w->msg.channel_id==event.command.channel_id&&w->msg.id == event.command.msg.id){
            if(event.custom_id=="l")w->move(-1,0);
            if(event.custom_id=="r")w->move(1,0);
            if(event.custom_id=="d")w->move(0,-1);
            if(event.custom_id=="stop")w->finish(w->name+zakonczylgre.tra[w->lang]);
            event.reply(dpp::ir_update_message,w->msg.set_content(w->getDC()));
            if(gry[u]->end)delgame(u);
        }

    });
    
    bot.start(false);
}