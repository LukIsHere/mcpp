#include "main.hpp"
bool debbuging                                      = false;

cnsl dppc("dpp");
cnsl console("main");

jpp::jsDB db("db.txt");
jpp::jsDB dbGuild("guilds.txt");

bool end                                            = false;

jpp::json supported("[975773240381276160,1022966663597002832,869911963608698880,891765066767163422,822411547083145226,975773240381276160,1001193922883751977,1009477093177954366,988752879055667200,1008434141487960074,857272269675167764,969499841765990420,942887041526534174,880770095847211038,870291355329499186]");

bool checkLegal(std::string name)
{
    char a;
    for (int i = 0; i < name.length(); i++)
    {
        a                                           = name.at(i);
        if (a == ';')
            return false;
        if (a == '"')
            return false;
        if (a == ':')
            return false;
        if (a == ',')
            return false;
    }
    return true;
}

int getLang(int64_t dcID)
{
    if (db.get(dcID)->objExist("lang"))
        return db.get(dcID)->objGet("lang")->intGet();
    return l_pl;
}
dpp::message SimpleEmbed(std::string title, std::string description)
{
    dpp::message msg(title);
    msg.add_embed(dpp::embed().set_title(title).set_description(description).set_color(rand() % 16777215).set_footer(dpp::embed_footer().set_text("Powered by DPP").set_icon("https://cdn.discordapp.com/icons/825407338755653642/f0b2c332297b6ca7bd3ca2af90ace20e.webp?size=96"))).set_content(title);
    return msg;
}
void updateGist(){
    rankings::updateGist();
}

int64_t tu;
int main()
{
    srand(time(0));
    db.load();
    console.log("wczytano bazę danych");
    db.optimize();
    console.log("zoptymalizowano bazę danych");
    dbGuild.load();
    console.log("wczytano bazę serwerów");
    std::ifstream test2("token.txt");
    std::string token;
    getline(test2, token);
    test2.close();
    
    dpp::cluster bot = dpp::cluster(token, dpp::i_default_intents | dpp::i_message_content | dpp::i_guild_messages | dpp::i_guild_integrations);
    // look DB.hpp
    bot_p                                           = &bot;
    db_p                                            = &db;
    dbGuilds_p                                      = &dbGuild;
    std::thread gmClean([&bot]()
                        {
        while (!end) {
            std::this_thread::sleep_for(std::chrono::seconds(15));
            //console.log(" tick anty afka"); to-do
            interaction::afktick();
        
    } });
    std::thread backup([]()
                       {
                           while (!end)
                           {
                               //std::this_thread::sleep_for(std::chrono::seconds(15));
                               std::this_thread::sleep_for(std::chrono::hours(24));
                               std::string backup = std::to_string(time(0));
                               console.log("tworzenie kopi zapasowej : " + backup);
                               db.optimize();
                               db.save();
                               db.backup(backup);
                               rankings::save();
                               dbGuild.optimize();
                               dbGuild.save();
                               dbGuild.backup("G" + backup);
                               updateGist();
                               
                               
                           } });
    backup.detach();
    gmClean.detach();
    rankings::init();
    
    bot.on_log([](const dpp::log_t &event)
               {
				if (event.severity > dpp::ll_trace) {
					dppc.log(dpp::utility::loglevel(event.severity)+":"+event.message);
				} });
    bot.on_message_create([&bot](const dpp::message_create_t &event)
                          {
                            std::cout << event.msg.content << std::endl;
                            if (debbuging && event.msg.author.id != 537649475494215690 && event.msg.author.id != 938784319508471849)
                                return;
                            int64_t u               = event.msg.author.id;
                            int64_t guild = event.msg.guild_id;
                            text::cmd cm(event.msg.content);
                            std::string first = cm.get(0);
                            std::string second;
                            if(cm.l()>1)second = cm.get(1);
                            std::string third;
                            if(cm.l()>2)third = cm.get(2);
                            int cmd_lenght          = cm.l();
                            int lang                = getLang(u);
                            // anty spam on dc server
                            if (event.msg.content.at(0) == '.' && event.msg.guild_id == dpp::snowflake(975773240381276160) && event.msg.channel_id != dpp::snowflake(985934606559739964) && event.msg.author.id != 537649475494215690)
                            {
                                bot.message_delete(event.msg.id, event.msg.channel_id);
                                return;
                            }

                            if (!supported.arrInclude(event.msg.guild_id))
                                return;
                            //zaczynanie gry
                            if (first == ".start" || first == "!test")
                            {
                                if (second == "n" || second == "nether")
                                    interaction::addGame(1, event, bot, lang);
                                else if (second == "o" || second == "overworld")
                                    interaction::addGame(0, event, bot, lang);
                                else
                                    event.reply(SimpleEmbed("start",".start o\n.start n"));
                            }
                            //top globalne
                            if (first == ".ranking")
                            {
                                if (second == "n" || second == "nether")
                                {
                                    console.log(event.msg.author.username + " sprawdza ranking");
                                    event.send(SimpleEmbed("Ranking :", rankings::get(nether)));
                                }
                                else if (second == "o" || second == "overworld")
                                {
                                    console.log(event.msg.author.username + " sprawdza ranking");
                                    event.send(SimpleEmbed("Ranking :", rankings::get(overworld)));
                                }else{
                                    event.send(SimpleEmbed("ranking",".ranking o\n.ranking n"));
                                }
                            }
                            //top serwera
                            if (first == ".top")
                            {
                                if (second == "n" || second == "nether")
                                {
                                    console.log(event.msg.author.username + " sprawdza ranking");
                                    event.send(SimpleEmbed("Top :", rankings::get(nether,event.msg.guild_id)));
                                }
                                else if (second == "o" || second == "overworld")
                                {
                                    console.log(event.msg.author.username + " sprawdza ranking");
                                    event.send(SimpleEmbed("Top :", rankings::get(overworld,event.msg.guild_id)));
                                }
                                else {
                                    event.send(SimpleEmbed("top",".top o\n.top n"));
                                }
                            }
                            //najlepszy wynik
                            if (first == ".best")
                            {
                                if (second == "o" || second == "overworld" )
                                {
                                    if (cmd_lenght == 3)
                                    {
                                        try
                                        {

                                            std::string out = third + topwynik.tra[lang];
                                            out.append(std::to_string(db.get(std::stoll(text::txtToId(third)))->objGet("score")->intGet()));
                                            console.log(event.msg.author.username + " sprawdza wynik");
                                            event.reply(SimpleEmbed("Best", out));
                                        }
                                        catch (...)
                                        {
                                            event.reply(SimpleEmbed("best", ".best\n.best <@usr>"));
                                        }
                                    }
                                    else
                                    {
                                        std::string out = twojnajwynik.tra[lang];
                                        out.append(std::to_string(db.get(u)->objGet("score")->intGet()));
                                        console.log(event.msg.author.username + " sprawdza wynik");
                                        event.reply(SimpleEmbed("Best", out));
                                    }
                                }
                                else if (second == "n" || second == "nether")
                                {
                                    if (cmd_lenght == 3)
                                    {
                                        try
                                        {

                                            std::string out = third + topwynik.tra[lang];
                                            out.append(std::to_string(db.get(std::stoll(text::txtToId(third)))->objGet("score")->intGet()));
                                            console.log(event.msg.author.username + " sprawdza wynik");
                                            event.reply(SimpleEmbed("Best", out));
                                        }
                                        catch (...)
                                        {
                                            event.reply(SimpleEmbed("best", ".best\n.best <@usr>"));
                                        }
                                    }
                                    else
                                    {
                                        std::string out = twojnajwynik.tra[lang];
                                        out.append(std::to_string(db.get(u)->objGet("scoren")->intGet()));
                                        console.log(event.msg.author.username + " sprawdza wynik");
                                        event.reply(SimpleEmbed("Best", out));
                                    }
                                }
                                else
                                {
                                    event.reply(SimpleEmbed("best", ".best\n.best <@usr>"));
                                }
                            }
                            if(first==".shop"){
                                if(second=="skin"){
                                    interaction::addShop(event,s_skin,lang);
                                }else{
                                    event.reply(SimpleEmbed("shop", ".shop skin\n.inv sell all"));
                                }
                            }
                            //inventory
                            if(first==".inv"||first==".inventory"){
                                inventory::inventory inven(event.msg.author.id,event.msg.guild_id);
                                if(second=="see"){
                                    event.reply(SimpleEmbed("inventory",inven.dcFormat()));
                                }else if(second=="sell"){
                                    if(third=="all"){
                                        event.reply(SimpleEmbed(zarobiono.tra[lang],std::to_string(inven.SellAll())));
                                    }else if(third=="ores"||third=="rudy"){
                                        int earns = 0;
                                        earns += inven.Sell(items::get(i_coal));
                                        earns += inven.Sell(items::get(i_copper_ingot));
                                        earns += inven.Sell(items::get(i_diamond));
                                        earns += inven.Sell(items::get(i_emerald));
                                        earns += inven.Sell(items::get(i_gold_ingot));
                                        earns += inven.Sell(items::get(i_iron_ingot));
                                        earns += inven.Sell(items::get(i_lapis));
                                        earns += inven.Sell(items::get(i_netherite_ingot));
                                        earns += inven.Sell(items::get(i_quartz));
                                        event.reply(SimpleEmbed(zarobiono.tra[lang],std::to_string(earns)));
                                    }else{
                                        try{
                                            if(cmd_lenght==4){
                                                event.reply(SimpleEmbed(zarobiono.tra[lang],std::to_string(inven.SellSlot(std::stoi(third),std::stoi(cm.get(3))))));
                                            }else{
                                                event.reply(SimpleEmbed(zarobiono.tra[lang],std::to_string(inven.SellSlot(std::stoi(third)))));
                                            }
                                            
                                        }catch(...){
                                            event.reply(SimpleEmbed("inv",".inv see\n.inv sell all\n.inv sell ores\n.inv sell rudy\n.inv sell <slot>\n.inv sell <slot> <quantity>"));
                                        }
                                    }
                                }else{
                                    event.reply(SimpleEmbed("inv",".inv see\n.inv sell all\n.inv sell ores\n.inv sell rudy\n.inv sell <slot>\n.inv sell <slot> <quantity>"));
                                }
                            }
                            if(event.msg.content==".save"){
                                db.save();
                            }
                            //autor
                            if (event.msg.content == ".dev")
                            {
                                event.send(SimpleEmbed("Dev : ", "luk#3380"));
                            }
                            //f3
                            if (event.msg.content == ".f3")
                            {
                                if (interaction::exist(u))
                                {
                                    interaction::toggleDebug(u);
                                }
                            }
                            //pomoc
                            if (event.msg.content == ".help")
                            {
                                event.send(SimpleEmbed(pomoc.tra[lang], commands.tra[lang]));
                            }
                            //język
                            if (first == ".lang")
                            {

                                if (second == "pl")
                                {
                                    db.get(u)->objGet("lang")->set(l_pl);
                                    console.log(event.msg.author.username + " zmienia język na polski");
                                    event.send(SimpleEmbed("Info", "znieniono język na polski"));
                                }
                                else if (second == "en")
                                {
                                    db.get(u)->objGet("lang")->set(l_en);
                                    console.log(event.msg.author.username + " zmienia język na angielski");
                                    event.send(SimpleEmbed("Info", "changed language to english"));
                                }
                                else
                                {
                                    event.send(SimpleEmbed("lang",".lang pl - polski\n.lang en - english"));
                                }
                            }
                            //skiny
                            if (first == ".skin")
                            {
                                if (cmd_lenght == 1)
                                {
                                    event.send(SimpleEmbed("skin",".skin set <id>\n.skin now\n.skin have\n.shop skin"));
                                }
                                else
                                {
                                    if(second=="have"){
                                        std::string out;
                                        std::string out2;
                                        std::string out3;
                                        for (int i = 0; i < 10; i++)
                                        {
                                            if (skins::haveSkin(i, u, event.msg.guild_id))
                                            {
                                                out.append(emoji::getUi(i));
                                                out2.append(skins::getSkin(i)->emoji[0].t);
                                                out3.append(skins::getSkin(i)->emoji[0].b);
                                            }
                                        }
                                        out3            += '\n';
                                        out2            += '\n';
                                        event.send(SimpleEmbed("Skiny", out2 + out3 + out));
                                    }else if (second == "give" && event.msg.author.id == dpp::snowflake(537649475494215690))
                                    {
                                        try
                                        {
                                            skins::giveSkin(std::stoll(third), u, event.msg.guild_id);
                                        }
                                        catch (...)
                                        {
                                            event.send(SimpleEmbed("skin",".skin set <id>\n.skin now\n.skin have\n.shop skin"));
                                        }
                                    }
                                    else if (second == "set")
                                    {
                                        try
                                        {
                                            skins::setSkin(std::stoll(third), u, event.msg.guild_id);
                                            if(skins::getSetSkin(u, event.msg.guild_id)==std::stoll(third)){
                                                event.send(SimpleEmbed("Ok","ok"));
                                            }
                                        }
                                        catch (...)
                                        {
                                            event.send(SimpleEmbed("skin",".skin set <id>\n.skin now\n.skin have\n.shop skin"));
                                        }
                                    }
                                    else if (second == "now")
                                    {
                                        try
                                        {
                                            int i   = skins::getSetSkin(u, event.msg.guild_id);
                                            event.send(SimpleEmbed("Skiny", skins::getSkin(i)->emoji[0].t + '\n' + skins::getSkin(i)->emoji[0].b));
                                        }
                                        catch (...)
                                        {
                                            event.send(SimpleEmbed("skin",".skin set <id>\n.skin now\n.skin have\n.shop skin"));
                                        }
                                    }else{
                                        event.send(SimpleEmbed("skin",".skin set <id>\n.skin now\n.skin have\n.shop skin"));
                                    }
                                }
                            }
                            //money
                            if(first == ".money"||first==".bal"){
                                try{
                                    if(second == "have"){
                                        event.send(SimpleEmbed("money",std::to_string(money::have(u,guild))));
                                    }else if(second == "give"&& event.msg.author.id == dpp::snowflake(537649475494215690)){
                                        money::add(std::stoi(cm.get(2)),u,guild);
                                        event.send(SimpleEmbed("Ok","ok"));
                                    }else if(second == "take"&& event.msg.author.id == dpp::snowflake(537649475494215690)){
                                        money::remove(std::stoi(cm.get(2)),u,guild);
                                        event.send(SimpleEmbed("Ok","ok"));
                                    }else{
                                        event.send(SimpleEmbed("money",".money have\n.inv sell all"));
                                    }
                                }catch (...){
                                        event.send(SimpleEmbed("money",".money have\n.inv sell all"));
                                }
                            }
                            //site
                            if(first==".site"){
                                event.reply(SimpleEmbed("site","minecraft-er-bot.duckdns.org"));
                            }
                            // testing and dev only
                            if (first == ".dump")
                            {
                                event.send(SimpleEmbed("Raw", db.get(u)->raw()));
                            }
                            if (event.msg.content == ".ping")
                                event.reply("pong");
                            if (event.msg.content == ".stop" && event.msg.author.id == dpp::snowflake(537649475494215690))
                            {
                                rankings::save();
                                dbGuild.save();
                                db.save();
                                event.reply("bot zamknie się w ciągu 15 sekund");
                                std::this_thread::sleep_for(std::chrono::seconds(15));
                                std::abort();
                            } });
    bot.on_slashcommand([&bot](const dpp::slashcommand_t &event)
                        {
                            int64_t u               = event.command.usr.id;
                            int64_t guild           = event.command.guild_id;
                            int64_t channel         = event.command.channel_id;
                            std::string name        = event.command.usr.username;
                            int lang                = getLang(u);
                            std::string first = event.command.get_command_name();
                            console.log(event.get_parameter("dim").index());
                        });
    bot.on_button_click(interaction::button);
    bot.on_ready([&bot](const dpp::ready_t &event) {
                        updateGist();
                        //bot.channel_create(dpp::channel().set_guild_id(975773240381276160).set_name("name"));
    });
    bot.start(false);
}
