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
#define punkty tr::translation("Punkty : ","Points : ","text.points")
#define nowagra tr::translation(" zaczoł nową gre"," has starterd new game","text.nowagra")
#define durabilityKoniec tr::translation(" nie ma użyć"," has no durability","text.durabilityend")
#define umarlw tr::translation(" umarł w "," died in ","text.dieIn")
#define zakonczylgre tr::translation(" zakończył gre"," has ended the game","text.finishgame")
#define bylafk tr::translation(" był afk"," was afk","text.afk")
#define ranking tr::translation("Ranking :\n","Ranking :\n","text.ranking")
#define twojnajwynik tr::translation("Twój najlepszy wynik to : "," Your best score is : ","text.najlepszy wynik")
#define topwynik tr::translation(" najlepszy wynik : "," best score : ","text.top wynik")
#define commands tr::translation("Komędy  : \n.lang - zniana języka\n.start - zaczyna grę\n.ranking - pokazuje globalny ranking\n.best - najlepszy wynik\n.top - pokazuje serwerowe top\n.dev - pokazuje twórce bot'a\n.skin - skiny\n.shop - sklep\n.inv - ekwipunek\n.money - pieniądze\n.site - strona internetowa\npo więcej informacji poprostu wpisz komęde","Commands  : \n.lang - change the language\n.start - starts the game\n.ranking - global ranking\n.best - best score\n.top - top on this server\n.dev - the creator of the bot\n.skin - skins\n.shop - shop\n.inv - inventory\n.money - balance\n.site - website\nfor more informations just type the command","text.commands")
#define theEnd tr::translation(" Koniec :","The end :","text.end")
#define badarg tr::translation("złe argumenty","bad arguments","text.badargs")
#define pomoc tr::translation("Pomoc","Help","text.help")
#define zarobiono tr::translation("you've earned","zarobiłeś","text.earn")

