#include "include/translation.hpp"

tr::translation translations[] = {
    tr::translation("punkty : ","points : ","text.points")
};
std::string tr::getTR(int id,int lang){
    return translations[id].tra[lang];
};