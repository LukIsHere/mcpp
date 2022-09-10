#include "lsudms.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace  std;
//sprawdza czy biblioteka działa poprawnie
void ums::connect(){
    cout << "lsudms connected" << endl;
}
//konwertuje string na int64_t
int64_t ums::stoi64(string v){
    
    int64_t out = 0;
    int64_t te = 1;
    for (int i = 0; v.length() > i; ++i)
    {
        string charr;
        charr.push_back(v.at(v.length() - 1 - i));
        out = stoi(charr) * te + out;
        te = te*10;
    }
    return out;
}

            //list - przechowuje zbiur wartość
            //string value
            ums::list::list(){
                value = "";
            };
            ums::list::list(string v){
                value = v;
            };
            //work with list
            void ums::list::push(string v){
                value.append(",");
                value.append(v);
            };
            void ums::list::remove(string v){
                string cur = "";
                string anal = value;
                int start = 0;
                int leng = 0;
                int fs;
                int fl;
                for (int i = 0; i < anal.length(); i++)
                {
                    if (anal.at(i) == ',')
                    {
                        if (cur == value)
                        {
                            fs = start;
                            fl = leng;
                        }
                        cur = "";
                        start = i + 1;
                        leng = 0;
                    }
                    else
                    {
                        leng++;
                        cur += anal.at(i);
                    }
                }
                if (cur == value)
                {
                    fs = start;
                    fl = leng;
                }
                string out = "";
                if (anal.at(fs + fl) == ',')
                {
                    fl++;
                }
                else if (anal.at(fs - 1) == ',')
                {
                    fs--;
                    fl++;
                }
                for (int i = 0; i < anal.length(); i++)
                {
                    if (i < fs || i > fs + fl - 1)
                    {
                        out += anal.at(i);
                    }
                }
                value = out;
            };
            bool ums::list::include(string v){
                bool out = false;
                string cur = "";
                string anal = value;
                for (int i = 0; i < anal.length(); i++)
                {
                    if (anal.at(i) == ',')
                    {

                        if (cur == v)
                        {
                            return true;
                        }

                        cur = "";
                    }
                    else
                    {
                        cur += anal.at(i);
                    }
                }
                if (cur == v)
                {
                    return true;
                }
                return false;
            };
            void ums::list::forEach(std::function<void(string v)> fun){
                string cur = "";
                string anal = value;
                for (int i = 0; i < anal.length(); i++)
                {
                    if (anal.at(i) == ',')
                    {
                        fun(cur);
                    }
                    else
                    {
                        cur += anal.at(i);
                    }
                }
                fun(cur);
            };
            string ums::list::get(int p){
                string cur = "";
                int id = 0;
                string anal = value;
                for (int i = 0; i < anal.length(); i++)
                {
                    if (anal.at(i) == ',')
                    {
                        if (id == p)
                        {
                            return cur;
                        }
                        else
                        {
                            cur = "";
                        }
                        id++;
                    }
                    else
                    {
                        cur += anal.at(i);
                    }
                }
                if (id == p)
                {
                    return cur;
                }
                return "";
            };
            int ums::list::size(){
                int out = 1;
                string anal = value;
                for (int i = 0; i < anal.length(); i++)
                {
                    if (anal.at(i) == ',')
                    {
                        out++;
                    }
                }
                return out;
            };
            //export
            string ums::list::getS(){
                return value;
            };



            //var - działa jako kilka wartość
            //bool exist;
            //string value;
            ums::var::var(){
                exist = false;
            };
            ums::var::var(string v){
                value = v;
                exist = true;
            };
            ums::var::var(int v){
                value = to_string(v);
                exist = true;
            };
            ums::var::var(bool v){
                if(v)value = "true";
                else value = "false";
                exist = true;
            };
            ums::var::var(list v){
                value = v.getS();
                exist = true;
            };
            //get values
            string ums::var::gstr(){
                return value;
            };
            int ums::var::gint(){
                try{
                    return stoi64(value);
                }catch(...){

                }
                return -1;
                
            };
            bool ums::var::gbool(){
                return (value=="true");
            };
            ums::list ums::var::getl(){
                return list(value);
            };
            //work with values
            void ums::var::Iadd(int toAdd){
                try
                {
                    value = to_string(stoi(value)+toAdd);
                }
                catch(const std::exception& e)
                {
                }
            };
            void ums::var::Sappend(string toAppend){
                value.append(toAppend);
            };
            void ums::var::Bnegate(){
                if(value=="true") value="false";
                else value = "true";
            };
            void ums::var::Lpush(string v){
                list l = list(value);
                l.push(v);
                value = l.getS();
            };
            void ums::var::Lremove(string v){
                list l = list(value);
                l.remove(v);
                value = l.getS();
            };
            bool ums::var::Linclude(string v){
                return list(value).include(v);
            };
            void ums::var::LforEach(function<void(string v)> fun){
                list(value).forEach(fun);
            };
            //set values
            void ums::var::set(string v){
                value = v;
                exist = true;
            };
            void ums::var::set(int v){
                value = to_string(v);
                exist = true;
            };
            void ums::var::set(bool v){
                if(v)value = "true";
                else value = "false";
                exist = true;
            };
            void ums::var::set(ums::list v){
                value = v.getS();
                exist = true;
            };



            //user - przechowuje wartość
            //bool exist;
            //map<string,var> data;
            ums::user::user(){
                exist = false;
            };
            ums::user::user(string dt){//{"key":"val"}
                
                exist = true;
                char l;
                string key;
                string val;
                bool read = false;
                bool state = false;//true-val false-key
                for(int i = 0;i<dt.length();i++){
                    l = dt.at(i);
                    if(l=='{'||l=='}'){}
                    else if(l==':') state = true;
                    else if(l=='"'){read = !read;}
                    else if(l==','&&!read){
                        state = false;
                        data[key] = val;
                        key = "";
                        val = "";
                    }else{
                        if(state)val+=l;
                        else key+=l;
                    }
                }
                data[key] = val;
            };
            //set values
            void ums::user::set(string name,string val){
                data[name] = var(val);
                exist = true;
            };
            void ums::user::set(string name,int val){
                data[name] = var(val);
                exist = true;
            };
            void ums::user::set(string name,bool val){
                data[name] = var(val);
                exist = true;
            };
            //work with values
            void ums::user::Iadd(string name,int toAdd){
                data[name].Iadd(toAdd);
            };
            void ums::user::Sappend(string name,string toAppend){
                data[name].Sappend(toAppend);
            };
            void ums::user::Bnegate(string name){
                data[name].Bnegate();
            };
            void ums::user::Lpush(string name,string v){
                data[name].Lpush(v);
            };
            void ums::user::Lremove(string name,string v){
                data[name].Lremove(v);
            };
            bool ums::user::Linclude(string name,string v){
                return data[name].Linclude(v);
            };
            void ums::user::LforEach(string name,function<void(string v)> fun){
                data[name].LforEach(fun);
            };
            //get valuse
            string ums::user::gets(string name){
                return data[name].gstr();
            };
            int ums::user::geti(string name){
                return data[name].gint();
            };
            bool ums::user::getb(string name){
                return data[name].gbool();
            };
            ums::list ums::user::getl(string name){
                return data[name].getl();
            };
            string ums::user::getS(){
                string out = "{";
                bool first = true;
                map<string,var>::iterator it;
                for(it = data.begin();it!=data.end();it++){
                    if(!first){
                        out+=',';
                    }
                    first = false;
                    out += '"';
                    out.append(it->first);
                    out += '"';
                    out += ':';
                    out += '"';
                    out.append(it->second.gstr());
                    out += '"';
                }
                out+='}';
                return out;//{"val":"key"}
            }



            //score
            //int scor = 0;
            //string name = 0;
            ums::score::score(){
                name = "";
            };
            ums::score::score(int s,string n){
                scor = s;
                name = n;
            };



            //class top{
            //score s[25];
            ums::top::top(ums::score t){
                for(int i = 0;i<24;i++){
                    s[i]=t;
                }
            };
            bool comp(ums::score a,ums::score b){
                        return a.scor<b.scor;
            }
            void ums::top::addS(ums::score w){
                if(w.scor>s[24].scor){
                    s[24] = w;
                    score temp;
                    for(int i = 23;i>-1;i--){
                        if(s[i].scor<s[i+1].scor){
                            temp = s[i];
                            s[i] = s[i+1];
                            s[i+1] =  temp;
                        }
                    }
                }
            };
            std::string ums::top::out(){
                string o;
                for(int i = 0;i<25;i++){
                    o.append(to_string(i+1));
                    o+='.';
                    o.append(s[i].name);
                    o+=':';
                    o.append(to_string(s[i].scor));
                    o.append("\n");
                }
                return o;
            };


            //db - przechowuje użytkowników
            //string name;
            //map<int64_t,user> data;
            ums::db::db(){
                
            };
            ums::db::db(string n,string loc){
                fopen = false;
                name = n;
                location = loc;
            };
            void ums::db::addU(int64_t id,ums::user u){
                data[id] = u;
            };
            void ums::db::addU(std::string usr){
                string id;
                bool readingData = false;
                string dat;
                char l;
                for(int i = 0;i<usr.length();i++){
                    l = usr.at(i);
                    if(l==':'&&!readingData){
                        readingData = true;
                    }else if(readingData){
                        dat+=l;
                    }else{
                        id+=l;
                    }
                }
                int idd = stoi64(id);
                data[idd] = ums::user(dat);
            };
            void ums::db::delU(int64_t id){
                data.erase(id);
            };
            // save/load data from files
            // id:{"key":"value","key2":"value2"}
            void ums::db::save(){
                string loc = location;
                map<int64_t,user> *m = &data;
                bool *open = &fopen;
                thread save([open,m](string loc){
                    while(*open){};
                    *open = true;
                    string out;
                    fstream file;
                    map<int64_t,user>::iterator it;
                    for(it = m->begin();it!=m->end();it++){
                        
                        out.append(to_string(it->first));
                        out+=":";
                        out.append(it->second.getS());
                        out.append("\n");
                    };
                    file.open(loc,ios::out);
                    if(!file){cout << "nie można zapisać pliku" << endl;}
                    else {
                        file.clear();
                        file << out;
                    }
                    file.close();
                    *open = false;
                },loc);
                save.detach();
            };
            void ums::db::load(){
                    string loc = location;
                    bool *open = &fopen;
                    map<int64_t,user> *m = &data;
                    thread load([open,m](string loc){
                        while(*open){}
                        ifstream of(loc);
                        *open = true;
                        string decode;
                        std::cout << "[baza danych] wczytywanie bazy danych" << std::endl;
                        while (getline(of,decode))
                        {
                            string id;
                            bool readingData = false;
                            string data;
                            char l;
                            for(int i = 0;i<decode.length();i++){
                                l = decode.at(i);
                                if(l==':'&&!readingData){
                                    readingData = true;
                                }else if(readingData){
                                    data+=l;
                                }else{
                                    id+=l;
                                }
                            }//działa
                            int64_t idd = stoi64(id);
                            m->insert(pair<int64_t,user>(idd,user(data)));
                        }
                        std::cout << "[baza danych] wczytano bazę danych" << std::endl;
                        of.close();
                        *open = false;

                    },loc);

                    load.detach();
            };
            void ums::db::backup(string name){
                string loc = name;
                map<int64_t,user> *m = &data;
                thread save([m](string loc){
                    ofstream of(loc);
                    map<int64_t,user>::iterator it;
                    for(it = m->begin();it!=m->end();it++){
                        std::stringstream strr;
                        strr << it->first;
                        of <<  strr.str() << ":" << it->second.getS() << endl;
                    };
                    of.close();
                },loc);
                save.detach();
            };
            void ums::db::log(){
                map<int64_t,user>::iterator it;
                for(it = data.begin();it!=data.end();it++){
                    cout << to_string(it->first) << ":" << it->second.getS() << endl;
                };
            };
            ums::top ums::db::topBy(string name){
                ums::top out = ums::top(ums::score(0,""));
                map<int64_t,user>::iterator it;
                for(it = data.begin();it!=data.end();it++){
                        out.addS(score(it->second.geti(name),it->second.gets("name")));   
                };
                return out;
            };
            //get user pointer
            ums::user * ums::db::get(int64_t id){
                return &(data[id]);
            };



            //cmd - pozwala analizować string pod kontem argumentów
            //string v;
            ums::cmd::cmd(){

            };
            ums::cmd::cmd(string value){
                v = value;
            };
            string ums::cmd::get(int p){
                //to-do fix
                int place = 0;
                string out = "";
                string finded;
                bool found = false;
                for(int i = 0; v.length()>i;i++){
                    if(v.at(i)==' '){
                        if(p==place){
                            return out;
                            place++;
                        }
                        else{
                            place++;
                            out = "";
                        }
                    }else{
                        out+=v.at(i);
                    }
                }
                if(p==place){
                    return out;
                }
                return "";
            };



            //settings
            //map<std::string,std::string> data;
            ums::settings::settings(string loc){

            };
            string ums::settings::getS(string name){
                return name;
            };
            int ums::settings::getI(string name){
                return 0;
            };
            bool ums::settings::getB(string name){
                return true;
            };


            //class translation
            //std::map<int,std::map<std::string,std::string>> tr;
            ums::translation::translation(){

            };
            void ums::translation::loadLang(int name,std::string file){
                //later
            };
            void ums::translation::set(int lang,std::string id,std::string def){
                tr[lang][id] = def;
            };
            string ums::translation::get(int lang,std::string id){
                return tr[lang][id];
            };
