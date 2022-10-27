#include "interaction.hpp"


cnsl interactor("interaction");




std::map<int64_t,interaction::interaction*> interactions;
Lock i_mutex;
std::vector<int64_t> toDelete;
std::vector<int64_t> inValid;



void updateMessage(int64_t u){
    if(!interaction::exist(u))return;
    if(interactions[u]->type==i_world){
        world::world* w = &(interactions[u]->getWorld());
        w->updateMessage();
        bot_p->message_edit(w->msg);
    }
    
}
/// @brief deletes interaction
/// @param u user id
void del(int64_t u){
    if(!interaction::exist(u))return;
    delete interactions[u];
    interactions.erase(u);
    interactor.log("usunięto");
}

void interaction::afktick(){
    WriteLock lock(i_mutex);
    interactor.log("afk tick");
    inValid.clear();
    toDelete.clear();
    {
        for(auto it : interactions){
        if((it.second)==nullptr)inValid.push_back(it.first);
            else{
                if(it.second->type==i_world){
                    if(it.second->getWorld().afktick())toDelete.push_back(it.first);
                }
                if(it.second->type==i_shop){
                    if(it.second->getShop().afkTick())toDelete.push_back(it.first);
                }
                if(it.second->type==i_undefined){
                    toDelete.push_back(it.first);
                }
            }
        }
    }
    
    for(auto it : inValid){//nullptrs
        interactions.erase(it);
    }
    for(auto it : toDelete){//afk interaction
        if(interactions[it]->type==i_world){
            del(it);
        }else if(interactions[it]->type==i_shop){
            del(it);
        }else{
            del(it);
        }
        
    }
}
void interaction::toggleDebug(int64_t u){
    ReadLock lock(i_mutex);
    interactions[u]->getWorld().ToggleDebug();
    updateMessage(u);
}
void interaction::addGame(int dimension,const dpp::message_create_t& event,dpp::cluster& bot,int lang,int ussages){
        int64_t u = event.msg.author.id;
        interactor.log(event.msg.author.username+" tworzy grę w overworldzie na serwerze "+std::to_string(+event.msg.guild_id));
        WriteLock(i_mutex);
        if(exist(u)){
            del(u);
        }
        interactions[u] = new interaction(new world::world(dimension,skins::getSetSkin(u,event.msg.guild_id), ussages, lang,event.msg.channel_id,event.msg.guild_id,event.msg.author.id));
        world::world* w = &(interactions[u]->getWorld());
        //w->msg.content = "configMsg "+std::to_string(u)+' '+event.msg.author.username; this i stupid
        w->connect(u,event.msg.author.username);
        bot.message_create(w->msg,[w](const dpp::confirmation_callback_t &t){
            if(t.is_error())return;
            w->msg = t.get<dpp::message>();
        });
        
};
void interaction::addGame(int dimension,const dpp::slashcommand_t& event,dpp::cluster& bot,int lang,int ussages){
        int64_t u = event.command.usr.id;
        interactor.log(event.command.msg.author.username+" tworzy grę w overworldzie na serwerze "+std::to_string(+event.command.msg.guild_id));
        WriteLock lock(i_mutex);
        if(exist(u)){
            del(u);
        }
        
        interactions[u] = new interaction(new world::world(dimension,skins::getSetSkin(u,event.command.guild_id), ussages, lang,event.command.channel_id,event.command.guild_id,event.command.usr.id));
        world::world* w = &(interactions[u]->getWorld());
        //w->msg.content = "configMsg "+std::to_string(u)+' '+event.command.usr.username;
        w->connect(u,event.command.usr.username);
        event.reply(w->msg,[w,event](const dpp::confirmation_callback_t &t){
            event.get_original_response([w](const dpp::confirmation_callback_t &t){
                if(t.is_error())return;
                w->msg = t.get<dpp::message>();
            });
        });
};
void interaction::addShop(const dpp::message_create_t& event,int type,int lang){
        WriteLock lock(i_mutex);
        int64_t u = event.msg.author.id;
        if(exist(u)){
            del(u);
        }
        interactions[u] = new interaction(new shops::shop(type,u,event.msg.guild_id));
        shops::shop* s = &(interactions[u]->getShop());
        bot_p->message_create(s->msg.set_channel_id(event.msg.channel_id),[s](const dpp::confirmation_callback_t &t){
            if(t.is_error())return;
            s->msg = t.get<dpp::message>();
        });
};
void interaction::button(const dpp::button_click_t& event){
        ReadLock lock(i_mutex);
        int64_t u = event.command.member.user_id;
        if(!exist(u))return;
        if(interactions[u]==nullptr)del(u);
        if(interactions[u]->type==i_world){
            world::world *w = &(interactions[u]->getWorld());
            if(w!=nullptr&&w->valid&&w->msg.channel_id==event.command.channel_id&&w->msg.id == event.command.msg.id){
                w->buttonHandler(event);
                if(w->end==true){
                    lock.unlock();
                    WriteLock lockdel(i_mutex);
                    del(u);
                };
            }
        }else if(interactions[u]->type==i_shop){
            shops::shop *s = &(interactions[u]->getShop());
            if(s!=nullptr&&s->msg.channel_id==event.command.channel_id&&s->msg.id == event.command.msg.id){
                s->buttonHandler(event);
            }
        }
        
};

interaction::interaction& interaction::get(int64_t u){
    ReadLock lock(i_mutex);
    
    return *(interactions[u]);
}
bool interaction::exist(int64_t u){
    return (interactions.find(u)!=interactions.end());
}

//interaction class
            interaction::interaction::interaction(){
                type = i_undefined;
            };
            interaction::interaction::interaction(world::world* w){
                type = i_world;
                ptr = w;
            };
            interaction::interaction::interaction(shops::shop* s){
                type = i_shop;
                ptr = s;
            };
            shops::shop& interaction::interaction::getShop(){
                    return *((shops::shop*)ptr);
            };
            world::world& interaction::interaction::getWorld(){
                    return *((world::world*)ptr);
            };
            interaction::interaction::interaction::~interaction(){
                if(type==i_undefined){

                }
                if(type==i_shop){
                    delete (shops::shop*)ptr;
                }
                if(type==i_world){
                    delete (world::world*)ptr;
                }
            };