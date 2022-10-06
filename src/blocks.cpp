#include "blocks.hpp"
#include <vector>
#include <initializer_list>

	
	//int blockIndex = 0; may be buggy
	//class prop
		//bool unbreakable;
		//bool free2walk;
		//bool death;
		blocks::prop::prop(bool ub,bool f2w,bool ded){
			unbreakable = ub;
			free2walk = f2w;
			death = ded;
		};
	//class block
	//std::string name;
	//int id;
	//int variants;
	//std::string emoji;
	//prop props;
		blocks::block::block(std::string named,int idd,eC emo,prop propsd,int points){
				name = named;
				id = idd;
				types = emo.size;
				emoji = new std::string[types];
				for(int i = 0;i<emo.size;i++){
					emoji[i] = emo.em[i];
				}
				props = propsd;
				//blockIndex++;
				point = points;
			};
		std::string blocks::block::getEmoji(int prop){
			if(prop>=types) return emoji[0];
			return emoji[prop];
		};
	blocks::block blockl[] = {
		blocks::block("air",b_air,"<:0:1012260493756465162>",blocks::prop(false,true,false)),
		blocks::block("stone",b_stone,"<:0:1012260494880546819>"),
		blocks::block("dirt",b_dirt,"<:0:1012260496675717140>"),
		blocks::block("grass",b_grass,"<:0:1012260498202427422>"),
		blocks::block("snow_grass",b_snow_grass,"<:0:1012260499443953685>"),
		blocks::block("wood",b_wood,"<:0:1012260501104885900>"),
		blocks::block("leaves",b_leaves,"<:0:1012260502463852614>"),
		blocks::block("bedrock",b_bedrock,"<:0:1012260504229646376>",blocks::prop(true,true,false)),
		blocks::block("barrier",b_barier,"<:0:1012260505831878706>",blocks::prop(true,false,false)),
		blocks::block("s_coal",b_stone_coal,"<:0:1012260506830110771>",blocks::prop(false,false,false),5),
		blocks::block("s_copper",b_stone_copper,"<:1:1012260508239413260>",blocks::prop(false,false,false),10),
		blocks::block("s_diamond",b_stone_diamond,"<:1:1012260510093279232>",blocks::prop(false,false,false),100),
		blocks::block("s_emerald",b_stone_emerald,"<:1:1012260511565479977>",blocks::prop(false,false,false),200),
		blocks::block("s_gold",b_stone_gold,"<:1:1012260513247399977>",blocks::prop(false,false,false),20),
		blocks::block("s_iron",b_stone_iron,"<:1:1012260514740576296>",blocks::prop(false,false,false),25),
		blocks::block("s_lapis",b_stone_lapis,"<:1:1012260516711895060>",blocks::prop(false,false,false),5),
		blocks::block("s_redstone",b_stone_redstone,"<:1:1012260518280560660>",blocks::prop(false,false,false),7),
		blocks::block("deepslate",b_deepslate,"<:1:1012260519773745214>"),
		blocks::block("d_coal",b_deepslate_coal,"<:18:1012260521325645844>",blocks::prop(false,false,false),5),
		blocks::block("d_copper",b_deepslate_copper,"<:1:1012260522885906432>",blocks::prop(false,false,false),10),
		blocks::block("d_diamond",b_deepslate_diamond,"<:2:1012260524584611900>",blocks::prop(false,false,false),100),
		blocks::block("d_emerald",b_deepslate_emerald,"<:2:1012260526056808459>",blocks::prop(false,false,false),200),
		blocks::block("d_gold",b_deepslate_gold,"<:2:1012260527625482321>",blocks::prop(false,false,false),20),
		blocks::block("d_iron",b_deepslate_iron,"<:2:1012260528892153958>",blocks::prop(false,false,false),25),
		blocks::block("d_lapis",b_deepslate_lapis,"<:2:1012260530846695444>",blocks::prop(false,false,false),5),
		blocks::block("d_redstone",b_deepslate_redstone,"<:2:1012260532587335690>",blocks::prop(false,false,false),7),
		blocks::block("netherrack",b_netherrack,"<:2:1012260534030184528>"),
		blocks::block("n_gold",b_netherrack_gold,"<:2:1012260535540137984>",blocks::prop(false,false,false),40),
		blocks::block("n_quartz",b_netherrack_quartz,"<:2:1012260537062658068>",blocks::prop(false,false,false),80),
		blocks::block("n_debre",b_netherrack_debre,"<:2:1012260538576805948>",blocks::prop(false,false,false),300),
		blocks::block("glowstone",b_glowstone,"<:3:1012260540040630282>",blocks::prop(false,false,false),30),
		blocks::block("chest",b_chest,"<:3:1012260541726720080>"),
		blocks::block("n_red",b_netherrack_red,"<:3:1012260543442202684>"),
		blocks::block("wood_red",b_wood_red,"<:3:1012260545027653753>"),
		blocks::block("leaves_red",b_leaves_red,"<:3:1012260546755706970>"),
		blocks::block("bush_red",b_bush_red,"<:3:1012260551419760671>"),
		blocks::block("n_blue",b_netherrack_blue,"<:3:1012260553131036683>"),
		blocks::block("wood_blue",b_wood_blue,"<:3:1012260554750038088>"),
		blocks::block("leaves_blue",b_leaves_blue,"<:3:1012260556658462801>"),
		blocks::block("mushroom_blue",b_mushroom_blue,"<:3:1012260558369730600>"),
		blocks::block("mushroom_red",b_mushroom_red,"<:4:1012260560101965834>"),
		blocks::block("soulsand",b_soulsand,"<:4:1012260561817436190>"),
		blocks::block("obsidian",b_obsidian,"<:4:1012260563407077376>"),
		blocks::block("lava",b_lava,"<:4:1012260565009322084>",blocks::prop(false,true,true)),
		blocks::block("water",b_water,"<:4:1012260566414405642>",blocks::prop(false,true,false)),
		blocks::block("wool",b_wool,blocks::eC("<:4515:1022580608683233280>","<:4514:1022580606808375347>","<:4513:1022580605801746462>","<:4512:1022580604149190748>","<:4511:1022580601833926828>","<:4510:1022580599409618995>","<:459:1022580597773832193>","<:458:1022580595974484081>","<:457:1022580594795880478>","<:456:1022580593168498809>","<:455:1022580591440449607>","<:454:1022580590060515378>","<:453:1022580588563157053>","<:452:1022580587120316516>","<:451:1022580585778135040>","<:450:1022580584352059412>"))
	};
	
	//other
	blocks::block blocks::get(int id){
		if(id>=sizeof(blockl) / sizeof(block))return blockl[b_barier];
		return blockl[id];
	}

	std::string blocks::getBlocks(){
		std::string out;
		for(int i = 0;i<45;i++){
            blocks::block b = blocks::get(i);
			out.append("-");
			out.append(std::to_string(b.id));
			out.append(":");
			out.append(b.emoji[0]);
			out.append(":");
			out.append(b.name);
			out.append("\n");
        }
		return out;
	}