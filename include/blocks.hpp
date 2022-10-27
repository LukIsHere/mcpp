#pragma once
#include "items.hpp"
#include <iostream>
#include <string>
#include <string_view>
#include "vector"

#define b_air 0
#define b_stone 1
#define b_dirt 2
#define b_grass 3
#define b_snow_grass 4
#define b_wood 5
#define b_leaves 6
#define b_bedrock 7
#define b_barier 8
#define b_stone_coal 9
#define b_stone_copper 10
#define b_stone_diamond 11
#define b_stone_emerald 12
#define b_stone_gold 13
#define b_stone_iron 14
#define b_stone_lapis 15
#define b_stone_redstone 16
#define b_deepslate 17
#define b_deepslate_coal 18
#define b_deepslate_copper 19
#define b_deepslate_diamond 20
#define b_deepslate_emerald 21
#define b_deepslate_gold 22
#define b_deepslate_iron 23
#define b_deepslate_lapis 24
#define b_deepslate_redstone 25
#define b_netherrack 26
#define b_netherrack_gold 27
#define b_netherrack_quartz 28
#define b_netherrack_debre 29
#define b_glowstone 30
#define b_chest 31
#define b_netherrack_red 32
#define b_wood_red 33
#define b_leaves_red 34
#define b_bush_red 35
#define b_netherrack_blue 36
#define b_wood_blue 37
#define b_leaves_blue 38
#define b_mushroom_blue 39
#define b_mushroom_red 40
#define b_soulsand 41
#define b_obsidian 42
#define b_lava 43
#define b_water 44
#define b_wool 45
#define b_cobbledeepslate 46
#define b_cobblestone 47

#define d_none 0
#define d_item 1
#define d_block 2

namespace blocks
{

	// clasess
	class prop
	{
	public:
		bool unbreakable;
		bool free2walk;
		bool death;
		prop(bool ub = false, bool f2w = false, bool ded = false);
	};
	class drop
	{
	public:
		int type;
		int id;
		drop();
		drop(int typed, int idd);
	};
	class block
	{
	public:
		std::string name;
		int id;
		int variants;
		std::vector<std::string> emoji;
		prop props;
		int point;
		int types;
		drop drops;
		block(std::string named, int idd, std::vector<std::string> emo, prop propsd = prop(), int points = 0, drop d = drop());
		block(std::string named, int idd, std::string emo, prop propsd = prop(), int points = 0, drop d = drop());
		std::string getEmoji(int prop = 0);
	};
	const block &get(int id);
	std::string getEmoji(int id, int prop = 0);

}
extern const blocks::block blockl[];