#pragma once
#include "blocks.hpp"
#include <iostream>
#include <string>

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

namespace blocks{
	
	//clasess
	class eC{
		public:
			std::string em[16];
			int size=0;
			eC(const char* c){
				em[0] = c;
				size = 1;
			}
			eC(std::string emo1,std::string emo2 = "",std::string emo3 = "",std::string emo4 = "",std::string emo5 = "",std::string emo6 = "",std::string emo7 = "",std::string emo8 = "",std::string emo9 = "",std::string emo10 = "",std::string emo11 = "",std::string emo12 = "",std::string emo13 = "",std::string emo14 = "",std::string emo15 = "",std::string emo16 = ""){
				if(emo1!=""){
					em[size] = emo1;
					size++;
					
				}
				if(emo2!=""){
					em[size] = emo2;
					size++;
					
				}
				if(emo3!=""){
					em[size] = emo3;
					size++;
					
				}
				if(emo4!=""){
					em[size] = emo4;
					size++;
					
				}
				if(emo5!=""){
					em[size] = emo5;
					size++;
					
				}
				if(emo6!=""){
					em[size] = emo6;
					size++;
					
				}
				if(emo7!=""){
					em[size] = emo7;
					size++;
					
				}
				if(emo8!=""){
					em[size] = emo8;
					size++;
					
				}
				if(emo9!=""){
					em[size] = emo9;
					size++;
					
				}
				if(emo10!=""){
					em[size] = emo10;
					size++;
					
				}
				if(emo11!=""){
					em[size] = emo11;
					size++;
					
				}
				if(emo12!=""){
					em[size] = emo12;
					size++;
					
				}
				if(emo13!=""){
					em[size] = emo13;
					size++;
					
				}
				if(emo14!=""){
					em[size] = emo14;
					size++;
					
				}
				if(emo15!=""){
					em[size] = emo15;
					size++;
					
				}
				if(emo16!=""){
					em[size] = emo16;
					size++;
					
				}

			}
	};
	class prop{
	public:
		bool unbreakable;
		bool free2walk;
		bool death;
		prop(bool ub=false,bool f2w=false,bool ded=false);
	};
	class block{
	public:
		std::string name;
		int id;
		int variants;
		std::string *emoji;
		prop props;
		int point;
		int types;
		block(std::string named,int idd,eC emo,prop propsd = prop(),int points = 0);
		std::string getEmoji(int prop=0);
	};
	block get(int id);
	std::string getBlocks();
	
	
	
}