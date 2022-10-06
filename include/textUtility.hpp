#pragma once
#include <string>

namespace text{
    class cmd{
        public:
        std::string v;
        cmd(std::string cm){
            v = cm;
        }
        std::string get(int p){
            int pla = 0;
            char c;
            std::string out;
            for(int i = 0;i<v.length();i++){
                c = v.at(i);
                if(c==' '){
                    
                    if(p==pla){
                        return out;
                    }
                    out = "";
                    pla++;
                }else out+=c;

            }
            if(p==pla){
                return out;
            }
            return "";

        }
        int l(){
            int pla = 0;
            char c;
            for(int i = 0;i<v.length();i++){
                c = v.at(i);
                if(c==' '){
                    pla++;
                }

            }
            pla++;
            return pla;
        }


    };
    std::string txtToId(std::string txt){
        std::string out;
        int l = txt.length();
        char now;
        for(int i = 0;i<l;i++){
            now = txt.at(i);
            if(now!='<'&&now!='@'&&now!='>')out += now;
        }
        return out;
    }
}