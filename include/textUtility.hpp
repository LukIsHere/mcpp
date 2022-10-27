#pragma once
#include <string>
#include <vector>

namespace text{
    class cmd{
        public:
        std::vector<std::string> v;
        cmd(std::string cm){
            int pla = 0;
            char c;
            std::string out;
            int cml = cm.length();
            for(int i = 0;i<cml;i++){
                c = cm.at(i);
                if(c==' '){
                    v.push_back(out);
                    out = "";
                    pla++;
                }else out+=c;

            }
            v.push_back(out);

        }
        std::string get(int p){
            return v[p];
        }
        int l(){
            return v.size();
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