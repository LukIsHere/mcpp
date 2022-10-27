#include "api.hpp"

void apis::SendUpdate(std::string prop,jpp::json& data){
    std::string dataa = data.raw();
    std::thread([prop,dataa](){
        httplib::Client cli("localhost:8080");
        jpp::json reqe;
        reqe.objGet("name")->set(prop);
        reqe["data"].decode(dataa);
        cli.Post("/bruh",reqe.raw(),"application/json");
    }).detach();
    
}
void apis::SendUpdate(std::string prop,std::string data){
    std::thread([prop,data](){
        httplib::Client cli("localhost:8080");
        jpp::json reqe;
        reqe.objGet("name")->set(prop);
        reqe["data"].set(data);
        cli.Post("/bruh",reqe.raw(),"application/json");
    }).detach();
}