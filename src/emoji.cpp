#include "emoji.hpp"

std::string UI[] = {
    "<:0:1022436698937892864>",
    "<:1:1022436718386892830>",
    "<:2:1022436734971162644>",
    "<:3:1022436753950380032>",
    "<:4:1022436773294510140>",
    "<:5:1022436793515257908>",
    "<:6:1022436813345919016>",
    "<:7:1022436834019655680>",
    "<:8:1022436850679422977>",
    "<:9:1022436868073193534>",
    "<:_:1022437306914840586>",
    "<:_:1022437353219960843>",
    "<:k:1022439306964516914>",
    "<:s:1022439349117263903>",
    "<:m:1022438464731500564>"
};
std::string& emoji::getUi(int id){
    if(id>=sizeof(UI)/sizeof(std::string))return UI[0];
    return UI[id];
};