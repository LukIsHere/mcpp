#pragma once
#include <map>
#include <string>
#include <iostream>
#include <functional>
#include <thread>
//function<zwrot(argumenty)> func
namespace ums{
    void connect();
    int64_t stoi64(std::string v);
    class list{
        public:
            std::string value;
            list();
            list(std::string v);
            //work with list
            void push(std::string v);
            void remove(std::string v);
            bool include(std::string v);
            void forEach(std::function<void(std::string v)> fun);
            std::string get(int p);
            int size();
            //export
            std::string getS();
    };
    class var{
        public:
            bool exist;
            std::string value;
            var();
            var(std::string v);
            var(int v);
            var(bool v);
            var(list v);
            //get values
            std::string gstr();
            int gint();
            bool gbool();
            list getl();
            //work with values
            void Iadd(int toAdd);
            void Sappend(std::string toAppend);
            void Bnegate();
            void Lpush(std::string v);
            void Lremove(std::string v);
            bool Linclude(std::string v);
            void LforEach(std::function<void(std::string v)> fun);
            //set values
            void set(std::string v);
            void set(int v);
            void set(bool v);
            void set(list v);
    };
    class user{
        public:
            bool exist;
            std::map<std::string,var> data;
            user();
            user(std::string dt);
            //set values
            void set(std::string name,std::string val);
            void set(std::string name,int val);
            void set(std::string name,bool val);
            //work with values
            void Iadd(std::string name,int toAdd);
            void Sappend(std::string name,std::string toAppend);
            void Bnegate(std::string name);
            void Lpush(std::string name,std::string v);
            void Lremove(std::string name,std::string v);
            bool Linclude(std::string name,std::string v);
            void LforEach(std::string name,std::function<void(std::string v)> fun);
            //get valuse
            std::string gets(std::string name);
            int geti(std::string name);
            bool getb(std::string name);
            list getl(std::string name);
            std::string getS();
    };
    class score{
        public:
            int scor = 0;
            std::string name = "";
            score();
            score(int s,std::string n);
    };
    class top{
        public:
            score s[25];
            top(score t);
            void addS(score w);
            std::string out();
    };
    class db{
        public:
            std::string name;
            std::string location;
            bool fopen;
            std::map<int64_t,user> data;
            db();
            db(std::string n,std::string loc);
            void addU(int64_t id,user u);
            void addU(std::string usr);
            void delU(int64_t id);
            int getI(int64_t u,std::string p);
            std::string getS(int64_t u,std::string p);
            bool getB(int64_t u,std::string p);
            ums::list getL(int64_t u,std::string p);
            // save/load data from files
            // id:{"key":"value","key2":"value2"}
            void save();
            void load();
            void backup(std::string name);
            void log();
            //get user pointer
            user *get(int64_t id);
            //top
            top topBy(std::string name);
    };
    
    class cmd{
        public:
            std::string v;
            cmd();
            cmd(std::string value);
            std::string get(int p);
    };

    class settings{
        public:
            std::map<std::string,std::string> data;
            settings(std::string loc);
            std::string getS(std::string name);
            int getI(std::string name);
            bool getB(std::string name);
    };
    class translation{
        public:
            std::map<int,std::map<std::string,std::string>> tr;
            translation();
            void loadLang(int name,std::string file);
            void set(int lang,std::string id,std::string def);
            std::string get(int lang,std::string id);
    };
    
}