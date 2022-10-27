#include "items.hpp"

// int itemIndex = 0; may be buggy
// class item{
// public:
// int id;
// std::string emoji;
// std::string name;
items::item::item(int idd, std::string emo, std::string nam,int val,bool stackabled)
{
    id = idd;
    emoji = emo;
    name = nam;
    stackable = stackabled;
    value = val;
    // itemIndex++;
};
//};
const items::item iteml[] = {
    items::item(0, "<:0:1012260493756465162>", "?",0, true),
    items::item(1, "<:1:1026118250863538208>", "iron_ingot",25, true),
    items::item(2, "<:2:1026118252226686976>", "gold_ingot",20, true),
    items::item(3, "<:3:1026118253619191930>", "copper_ingot",10, true),
    items::item(4, "<:4:1026118255070412891>", "diamond",100, true),
    items::item(5, "<:5:1026118256525840394>", "netherite_ingot",300, true),
    items::item(6, "<:6:1026118258069360692>", "raw_iron",25, true),
    items::item(7, "<:7:1026118259075981383>", "raw_gold",20, true),
    items::item(8, "<:8:1026118261110222848>", "raw_copper",10, true),
    items::item(9, "<:9:1026118262670495924>", "sweet_berry",0, true),
    items::item(10, "<:0:1026118264025251980>", "bone",0, true),
    items::item(11, "<:1:1026118265132556471>", "fish",0, true),
    items::item(12, "<:2:1028381851179548812>", "redstone",7, true),
    items::item(13, "<:3:1028381852920201306>", "lapis",5, true),
    items::item(14, "<:4:1028385205993607178>", "quartz",80, true),
    items::item(15,"<:5:1033679835735793714>","emerald",200,true),
    items::item(16,"<:6:1033680941866033172>","coal",5,true)
};
//
const items::item &items::get(int id)
{
    if (id >= sizeof(iteml) / sizeof(item))
        return iteml[0];
    return iteml[id];
};
std::string items::getEmoji(int id)
{
    return get(id).emoji;
}