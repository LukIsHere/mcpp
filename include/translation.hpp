#pragma once
#include <string>
#define l_systr 0
#define l_pl 1
#define l_en 2
//texty
#define tr_punkty 0
namespace tr{
    class translation
    {
    public:
        std::string tra[3];
        translation(std::string pl,std::string  en,std::string sysname){
            tra[l_systr] = sysname;
            tra[l_pl] = pl;
            tra[l_en] = en;

        };
    };
    std::string getTR(int id,int lang);
}
#define punkty tr::translation("Punkty :","Points : ","text.points")
#define nowagra tr::translation(" zaczoł nową gre"," has starterd new game","text.nowagra")
#define durabilityKoniec tr::translation(" nie ma użyć"," has no durability","text.durabilityend")
#define umarlw tr::translation(" umarł w "," died in ","text.dieIn")
#define zakonczylgre tr::translation(" zakończył gre"," has ended the game","text.finishgame")
#define bylafk tr::translation(" był afk"," was afk","text.afk")
#define ranking tr::translation("Ranking :\n","Ranking :\n","text.ranking")
#define twojnajwynik tr::translation("Twój najlepszy wynik to : "," Your best score is : ","text.najlepszy wynik")
#define commands tr::translation("Komędy  : \n.lang (pl/en) - zniana języka\n.start (ow/n) - zaczyna grę\n.ranking (ow/n) - pokazuje globalny ranking\n.best (ow/n) - najlepszy wynik\n.top (ow/n) - pokazuje serwerowe top  (nie dostępne)\n.dev - pokazuje twórce bot'a\n","Commands  : \n.lang (pl/en) - changes language\n.start (ow/n) - starts the game\n.ranking (ow/n) - show global ranking\n.best (ow/n) - your best score\n.top (ow/n) - shows best score on server  (not available)\n.dev - creator of a bot'a\n","text.commands")

