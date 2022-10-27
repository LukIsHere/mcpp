#include "blocks.hpp"
#include <vector>
#include <initializer_list>
#include "items.hpp"

// int blockIndex = 0; may be buggy
// class prop
// bool unbreakable;
// bool free2walk;
// bool death;
blocks::prop::prop(bool ub, bool f2w, bool ded)
{
	unbreakable = ub;
	free2walk = f2w;
	death = ded;
};
// class block
// std::string name;
// int id;
// int variants;
// std::string emoji;
// prop props;
blocks::block::block(std::string named, int idd, std::vector<std::string> emo, prop propsd, int points, drop d)
{
	name = named;
	id = idd;
	types = emo.size();
	emoji = emo;
	props = propsd;
	drops = d;
	// blockIndex++;
	point = points;
	if (d.type == d_none)
	{
		d.type = d_block;
		d.id = id;
	}
};
blocks::block::block(std::string named, int idd, std::string emo, prop propsd, int points, drop d)
{
	name = named;
	id = idd;
	types = 1;
	emoji.push_back(emo);
	props = propsd;
	drops = d;
	// blockIndex++;
	point = points;
};
std::string blocks::block::getEmoji(int prop)
{
	if (prop >= types)
		return emoji[0];
	return emoji[prop];
};

blocks::drop::drop()
{
	type = d_none;
	id = 0;
}
blocks::drop::drop(int typed, int idd)
{
	type = typed;
	id = idd;
}

const blocks::block blockl[] = {
	blocks::block("air", b_air, "<:0:1012260493756465162>",blocks::prop(false, true, false),0,blocks::drop(d_none,b_air)),
	blocks::block("stone", b_stone, "<:0:1012260494880546819>",blocks::prop(false, false, false),0,blocks::drop(d_block,b_cobblestone)),
	blocks::block("dirt", b_dirt, "<:0:1012260496675717140>"),
	blocks::block("grass", b_grass, "<:0:1012260498202427422>",blocks::prop(false, false, false),0,blocks::drop(d_block,b_dirt)),
	blocks::block("snow_grass", b_snow_grass, "<:0:1012260499443953685>",blocks::prop(false, false, false),0,blocks::drop(d_block,b_dirt)),
	blocks::block("wood", b_wood, "<:0:1012260501104885900>"),
	blocks::block("leaves", b_leaves, "<:0:1012260502463852614>"),
	blocks::block("bedrock", b_bedrock, "<:0:1012260504229646376>", blocks::prop(true, true, false)),
	blocks::block("barrier", b_barier, "<:0:1012260505831878706>", blocks::prop(true, false, false)),
	blocks::block("s_coal", b_stone_coal, "<:0:1012260506830110771>", blocks::prop(false, false, false), 5,blocks::drop(d_item,i_coal)),
	blocks::block("s_copper", b_stone_copper, "<:1:1012260508239413260>", blocks::prop(false, false, false), 10,blocks::drop(d_item,i_raw_copper)),
	blocks::block("s_diamond", b_stone_diamond, "<:1:1012260510093279232>", blocks::prop(false, false, false), 100,blocks::drop(d_item,i_diamond)),
	blocks::block("s_emerald", b_stone_emerald, "<:1:1012260511565479977>", blocks::prop(false, false, false), 200,blocks::drop(d_item,i_emerald)),
	blocks::block("s_gold", b_stone_gold, "<:1:1012260513247399977>", blocks::prop(false, false, false), 20,blocks::drop(d_item,i_raw_gold)),
	blocks::block("s_iron", b_stone_iron, "<:1:1012260514740576296>", blocks::prop(false, false, false), 25,blocks::drop(d_item,i_raw_iron)),
	blocks::block("s_lapis", b_stone_lapis, "<:1:1012260516711895060>", blocks::prop(false, false, false), 5,blocks::drop(d_item,i_lapis)),
	blocks::block("s_redstone", b_stone_redstone, "<:1:1012260518280560660>", blocks::prop(false, false, false), 7,blocks::drop(d_item,i_redstone)),
	blocks::block("deepslate", b_deepslate, "<:1:1012260519773745214>",blocks::prop(false, false, false),0,blocks::drop(d_block,b_cobbledeepslate)),
	blocks::block("d_coal", b_deepslate_coal, "<:18:1012260521325645844>", blocks::prop(false, false, false), 5,blocks::drop(d_item,i_coal)),
	blocks::block("d_copper", b_deepslate_copper, "<:1:1012260522885906432>", blocks::prop(false, false, false), 10,blocks::drop(d_item,i_raw_copper)),
	blocks::block("d_diamond", b_deepslate_diamond, "<:2:1012260524584611900>", blocks::prop(false, false, false), 100,blocks::drop(d_item,i_diamond)),
	blocks::block("d_emerald", b_deepslate_emerald, "<:2:1012260526056808459>", blocks::prop(false, false, false), 200,blocks::drop(d_item,i_emerald)),
	blocks::block("d_gold", b_deepslate_gold, "<:2:1012260527625482321>", blocks::prop(false, false, false), 20,blocks::drop(d_item,i_raw_gold)),
	blocks::block("d_iron", b_deepslate_iron, "<:2:1012260528892153958>", blocks::prop(false, false, false), 25,blocks::drop(d_item,i_raw_iron)),
	blocks::block("d_lapis", b_deepslate_lapis, "<:2:1012260530846695444>", blocks::prop(false, false, false), 5,blocks::drop(d_item,i_lapis)),
	blocks::block("d_redstone", b_deepslate_redstone, "<:2:1012260532587335690>", blocks::prop(false, false, false), 7,blocks::drop(d_item,i_redstone)),
	blocks::block("netherrack", b_netherrack, "<:2:1012260534030184528>",blocks::prop(false, false, false),0,blocks::drop(d_block,b_netherrack)),
	blocks::block("n_gold", b_netherrack_gold, "<:2:1012260535540137984>", blocks::prop(false, false, false), 40),
	blocks::block("n_quartz", b_netherrack_quartz, "<:2:1012260537062658068>", blocks::prop(false, false, false), 80),
	blocks::block("n_debre", b_netherrack_debre, "<:2:1012260538576805948>", blocks::prop(false, false, false), 300),
	blocks::block("glowstone", b_glowstone, "<:3:1012260540040630282>", blocks::prop(false, false, false), 30),
	blocks::block("chest", b_chest, "<:3:1012260541726720080>",blocks::prop(false, false, false),0,blocks::drop(d_none,0)),
	blocks::block("n_red", b_netherrack_red, "<:3:1012260543442202684>",blocks::prop(false, false, false),0,blocks::drop(d_block,b_netherrack)),
	blocks::block("wood_red", b_wood_red, "<:3:1012260545027653753>"),
	blocks::block("leaves_red", b_leaves_red, "<:3:1012260546755706970>",blocks::prop(false, false, false),0,blocks::drop(d_none,0)),
	blocks::block("bush_red", b_bush_red, "<:3:1012260551419760671>",blocks::prop(false, false, false),0,blocks::drop(d_none,0)),
	blocks::block("n_blue", b_netherrack_blue, "<:3:1012260553131036683>",blocks::prop(false, false, false),0,blocks::drop(d_block,b_netherrack)),
	blocks::block("wood_blue", b_wood_blue, "<:3:1012260554750038088>"),
	blocks::block("leaves_blue", b_leaves_blue, "<:3:1012260556658462801>",blocks::prop(false, false, false),0,blocks::drop(d_none,0)),
	blocks::block("mushroom_blue", b_mushroom_blue, "<:3:1012260558369730600>"),
	blocks::block("mushroom_red", b_mushroom_red, "<:4:1012260560101965834>"),
	blocks::block("soulsand", b_soulsand, "<:4:1012260561817436190>"),
	blocks::block("obsidian", b_obsidian, "<:4:1012260563407077376>"),
	blocks::block("lava", b_lava, "<:4:1012260565009322084>", blocks::prop(false, true, true)),
	blocks::block("water", b_water, "<:4:1012260566414405642>", blocks::prop(false, true, false)),
	blocks::block("wool", b_wool, {"<:4:1022580608683233280>", "<:4:1022580606808375347>", "<:4:1022580605801746462>", "<:4:1022580604149190748>", "<:4:1022580601833926828>", "<:4:1022580599409618995>", "<:4:1022580597773832193>", "<:4:1022580595974484081>", "<:4:1022580594795880478>", "<:4:1022580593168498809>", "<:4:1022580591440449607>", "<:4:1022580590060515378>", "<:4:1022580588563157053>", "<:4:1022580587120316516>", "<:4:1022580585778135040>", "<:4:1022580584352059412>"}),
	blocks::block("cobbledeepslate", b_cobbledeepslate, "<:4:1035255821925363802>"),
	blocks::block("cobblestone", b_cobblestone, "<:4:1035255820067274762>")
	};

// other
const blocks::block &blocks::get(int id)
{
	if (id >= sizeof(blockl) / sizeof(block))
		return blockl[b_barier];
	return blockl[id];
}

std::string blocks::getEmoji(int id, int prop){
	return get(id).emoji[prop];
}