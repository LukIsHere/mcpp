#pragma once
#include <string>

#define i_none 0
#define i_iron_ingot 1
#define i_gold_ingot 2
#define i_copper_ingot 3
#define i_diamond 4
#define i_netherite_ingot 5
#define i_raw_iron 6
#define i_raw_gold 7
#define i_raw_copper 8
#define i_sweet_berry 9
#define i_bone 10
#define i_fish 11
#define i_redstone 12
#define i_lapis 13
#define i_quartz 14
#define i_emerald 15
#define i_coal 16
namespace items
{
    class item
    {
    public:
        int id;
        std::string emoji;
        std::string name;
        bool stackable;
        int value;
        item(int idd, std::string emo, std::string nam,int val,bool stackabled = true);
    };
    const item &get(int id);
    std::string getEmoji(int id);
}

extern const items::item iteml[];