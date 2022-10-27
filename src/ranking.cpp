#include "ranking.hpp"
#include <map>
#include "iostream"

//globalny ranking
Lock Rank_mutex;
jpp::rank owr;
jpp::rank ntr;

//lokany ranking
std::map<int64_t,jpp::rank> owL;
std::map<int64_t,jpp::rank> ntL;

void rankings::init(){
    owr = db_p->getRanking("score");
    ntr = db_p->getRanking("scoren");
    //later stuff
    dbGuilds_p->loop([](jpp::user *u){
        owL[u->id]= jpp::rank(*(u->data->objGet("ranking")));
        ntL[u->id]= jpp::rank(*(u->data->objGet("rankingn")));
    });
}
void rankings::save(){
    for(auto p : owL){
        dbGuilds_p->get(p.first)->objGet("ranking")->set(p.second.expo());
    }
    for(auto p : ntL){
        dbGuilds_p->get(p.first)->objGet("rankingn")->set(p.second.expo());
    }
}


std::string rankings::get(int dimension){
    ReadLock lock(Rank_mutex);
    if(dimension==0){
        return owr.get();
    }
    if(dimension==1){
        return ntr.get();
    }
    return "";
};
std::string rankings::get(int dimension,int64_t server){
    ReadLock lock(Rank_mutex);
    if(dimension==0){
        return owL[server].get();
    }
    if(dimension==1){
        return ntL[server].get();
    }
    return "";
};
void rankings::addScore(jpp::place p,int dimension,int64_t server,int64_t u){
    WriteLock lock(Rank_mutex);
    jpp::json *usr = db_p->get(u);
    if(dimension==0){
        if(usr->objGet("score")->intGet()<p.score){
            usr->objGet("score")->set(p.score);
            usr->objGet("name")->set(p.name);
        }
        owL[server].add(p);
        owr.add(p);
    }
    if(dimension==1){
        if(usr->objGet("scoren")->intGet()<p.score){
            usr->objGet("scoren")->set(p.score);
            usr->objGet("name")->set(p.name);
        }
        ntL[server].add(p);
        ntr.add(p);
    }
};
void rankings::updateGist(){
    std::thread([](){
        ReadLock lock(Rank_mutex);
        jpp::json rankinggi;
        rankinggi["o"] = owr.expo();
        rankinggi["n"] = ntr.expo();
        lock.unlock();
        rankinggi["o"].arrLoop([](jpp::json *u){
            if(u->objGet("id")->intGet()!=0){
                std::this_thread::sleep_for(std::chrono::seconds(4));
                u->objGet("avatar")->set(bot_p->user_get_sync(u->objGet("id")->intGet()).get_avatar_url(4096));
            }
            
        });
        
        rankinggi["n"].arrLoop([](jpp::json *u){
            if(u->objGet("id")->intGet()!=0){
                std::this_thread::sleep_for(std::chrono::seconds(4));
                u->objGet("avatar")->set(bot_p->user_get_sync(u->objGet("id")->intGet()).get_avatar_url(4096));
            }
        });
        apis::SendUpdate("ranking",rankinggi);
        std::cout << "gist zaktualizowany" << std::endl;
    }).detach();
};