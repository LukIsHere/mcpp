#include "main.hpp"
#include "DB.hpp"
bool debbuging = false;

cnsl dppc("dpp");
cnsl console("main");

jpp::jsDB db("db.txt");
jpp::jsDB dbGuild("guilds.txt");

bool end = false;

jpp::json supported("[1022966663597002832,869911963608698880,891765066767163422,822411547083145226,975773240381276160,1001193922883751977,1009477093177954366,988752879055667200,1008434141487960074,857272269675167764,969499841765990420,942887041526534174,880770095847211038,870291355329499186]");

bool checkLegal(std::string name)
{
    char a;
    for (int i = 0; i < name.length(); i++)
    {
        a = name.at(i);
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
    dpp::message msg("");
    msg.add_embed(dpp::embed().set_title(title).set_description(description).set_color(rand() % 16777215));
    return msg;
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
    bot_p = &bot;
    db_p = &db;
    dbGuilds_p = &dbGuild;
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
                               // std::this_thread::sleep_for(std::chrono::seconds(15));
                               std::this_thread::sleep_for(std::chrono::hours(24));
                               std::string backup = std::to_string(time(0));
                               console.log("tworzenie kopi zapasowej : " + backup);
                               db.optimize();
                               db.backup(backup);
                               rankings::save();
                               dbGuild.optimize();
                               dbGuild.backup("G" + backup);
                           }
                       });
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
                            
                              //"configMsg "+std::to_string(u)+' '+event.command.msg.author.username

                              if (debbuging && event.msg.author.id != 537649475494215690 && event.msg.author.id != 938784319508471849)
                                  return;
                              int64_t u = event.msg.author.id;
                              text::cmd cm(event.msg.content);
                              std::string first = cm.get(0);
                              std::string second = cm.get(1);
                              std::string third = cm.get(2);
                              int cmd_lenght = cm.l();
                              int lang = getLang(u);
                              /*try{
                                  if(cm.l()==2){
                                      if(cm.get(0)==".skin"){
                                          std::string n = cm.get(1);
                                          int s = stoi(n);
                                          event.reply(skins::getSkin(stoi(n))->emoji->t+"\n"+skins::getSkin(stoi(n))->emoji->b);
                                          db.get(u)->objGet("skin")->set(s);
                                      }
                                  }
                              }catch(...){

                              }*/
                              // anty spam on dc server
                              if (event.msg.content.at(0) == '.' && event.msg.guild_id == dpp::snowflake(975773240381276160) && event.msg.channel_id != dpp::snowflake(985934606559739964) && event.msg.author.id != 537649475494215690)
                              {
                                  bot.message_delete(event.msg.id, event.msg.channel_id);
                                  return;
                              }

                              if (!supported.arrInclude(event.msg.guild_id))
                                  return;

                              if (first == ".start" || first == "!test")
                              {
                                  if (second == "n" || second == "nether")
                                      interaction::addGame(1, event, bot, lang);
                                  else if (second == "o" || second == "overworld" || second == "")
                                      interaction::addGame(0, event, bot, lang);
                                  else
                                      event.reply(SimpleEmbed("Error :", badarg.tra[lang]));
                              }
                              if (first == ".ranking")
                              {
                                  if (second == "n" || second == "nether")
                                  {
                                      console.log(event.msg.author.username + " sprawdza ranking");
                                      event.send(SimpleEmbed("Ranking :", rankings::get(nether)));
                                  }
                                  else if (second == "o" || second == "overworld" || second == "")
                                  {
                                      console.log(event.msg.author.username + " sprawdza ranking");
                                      event.send(SimpleEmbed("Ranking :", rankings::get(overworld)));
                                  }
                              }
                              if (first == ".top")
                              {
                                  if (second == "n" || second == "nether")
                                  {
                                      console.log(event.msg.author.username + " sprawdza ranking");
                                      event.send(SimpleEmbed("Top :", rankings::get(nether,event.msg.guild_id)));
                                  }
                                  else if (second == "o" || second == "overworld" || second == "")
                                  {
                                      console.log(event.msg.author.username + " sprawdza ranking");
                                      event.send(SimpleEmbed("Top :", rankings::get(overworld,event.msg.guild_id)));
                                  }
                              }
                              if (first == ".best")
                              {
                                  if (second == "o" || second == "overworld" || second == "")
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
                                              event.reply(SimpleEmbed("Error :", badarg.tra[lang]));
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
                                              event.reply(SimpleEmbed("Error :", badarg.tra[lang]));
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
                                      event.reply(SimpleEmbed("Error :", badarg.tra[lang]));
                                  }
                              }
                              if (event.msg.content == ".dev")
                              {
                                  event.send(SimpleEmbed("Dev : ", "luk#3380"));
                              }
                              if (event.msg.content == ".f3")
                              {
                                  if (interaction::exist(u))
                                  {
                                      interaction::toggleDebug(u);
                                  }
                              }
                              if (event.msg.content == ".help")
                              {
                                  event.send(SimpleEmbed(pomoc.tra[lang], commands.tra[lang]));
                              }
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
                                      event.send(SimpleEmbed("Error :", badarg.tra[lang]));
                                  }
                              }
                              if (first == ".skin")
                              {
                                  if (cmd_lenght == 1)
                                  {
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
                                      out3 += '\n';
                                      out2 += '\n';
                                      event.send(SimpleEmbed("Skiny", out2 + out3 + out));
                                  }
                                  else
                                  {
                                      if (second == "give" && event.msg.author.id == dpp::snowflake(537649475494215690))
                                      {
                                          try
                                          {
                                              skins::giveSkin(std::stoll(third), u, event.msg.guild_id);
                                          }
                                          catch (...)
                                          {
                                              event.send(SimpleEmbed("Error :", badarg.tra[lang]));
                                          }
                                      }
                                      else if (second == "set")
                                      {
                                          try
                                          {
                                              skins::setSkin(std::stoll(third), u, event.msg.guild_id);
                                          }
                                          catch (...)
                                          {
                                              event.send(SimpleEmbed("Error :", badarg.tra[lang]));
                                          }
                                      }
                                      else if (second == "now")
                                      {
                                          try
                                          {
                                              int i = skins::getSetSkin(u, event.msg.guild_id);
                                              event.send(SimpleEmbed("Skiny", skins::getSkin(i)->emoji[0].t + '\n' + skins::getSkin(i)->emoji[0].b));
                                          }
                                          catch (...)
                                          {
                                              event.send(SimpleEmbed("Error :", badarg.tra[lang]));
                                          }
                                      }
                                  }
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
                              }
                          });
    bot.on_slashcommand([&bot](const dpp::slashcommand_t &event)
                        {
        int64_t u = event.command.usr.id;
        int lang = getLang(u);
        std::string first = event.command.get_command_name();
        //if(!supported.arrInclude(event.command.msg.guild_id))return;
        //std::cout << first << std::endl;
        if(first=="start"){
                std::string second = std::get<std::string>(event.get_parameter("dimension"));
                if(second=="nether")interaction::addGame(1,event,bot,lang);
                else if(second=="overworld"||second=="")interaction::addGame(0,event,bot,lang);
                else event.reply(SimpleEmbed("Error :",badarg.tra[lang]));
        }
        if(first=="ranking"){
            std::string second = std::get<std::string>(event.get_parameter("dimension"));
            if(second=="nether"){
                console.log(event.command.msg.author.username+" sprawdza ranking");
                event.reply(SimpleEmbed("Ranking :",rankings::get(nether)));
            }else if(second=="overworld"||second==""){
                console.log(event.command.msg.author.username+" sprawdza ranking");
                event.reply(SimpleEmbed("Ranking :",rankings::get(overworld)));
            }
        }
        if (first == ".top")
                              {
                                std::string second = std::get<std::string>(event.get_parameter("dimension"));
                                  if (second == "nether")
                                  {
                                      console.log(event.command.msg.author.username + " sprawdza ranking");
                                      event.reply(SimpleEmbed("Top :", rankings::get(nether,event.command.guild_id)+"\n(lokalne)"));
                                  }
                                  else if (second == "overworld")
                                  {
                                      console.log(event.command.msg.author.username + " sprawdza ranking");
                                      event.reply(SimpleEmbed("Top :", rankings::get(overworld,event.command.guild_id)+"\n(lokalne)"));
                                  }
                              }
        if(first=="best"){
            std::string second = std::get<std::string>(event.get_parameter("dimension"));
            if(second=="overworld"||second==""){
                /*if(cmd_lenght==3){
                    try{

                        std::string out = third+topwynik.tra[lang];
                        out.append(std::to_string(db.get(std::stoll(text::txtToId(third)))->objGet("score")->intGet()));
                        console.log(event.msg.author.username+" sprawdza wynik");
                        event.reply(SimpleEmbed("Best",out));
                    }catch(...){
                        event.reply(SimpleEmbed("Error :",badarg.tra[lang]));
                    }
                }else{*/
                    std::string out = twojnajwynik.tra[lang];
                    out.append(std::to_string(db.get(u)->objGet("score")->intGet()));
                    console.log(event.command.msg.author.username+" sprawdza wynik");
                    event.reply(SimpleEmbed("Best",out));
                //}
                
            }else if(second=="nether"){
                /*if(cmd_lenght==3){
                    try{

                        std::string out = third+topwynik.tra[lang];
                        out.append(std::to_string(db.get(std::stoll(text::txtToId(third)))->objGet("score")->intGet()));
                        console.log(event.msg.author.username+" sprawdza wynik");
                        event.reply(SimpleEmbed("Best",out));
                    }catch(...){
                        event.reply(SimpleEmbed("Error :",badarg.tra[lang]));
                    }
                }else{*/
                    std::string out = twojnajwynik.tra[lang];
                    out.append(std::to_string(db.get(u)->objGet("scoren")->intGet()));
                    console.log(event.command.msg.author.username+" sprawdza wynik");
                    event.reply(SimpleEmbed("Best",out));
                //}
                
            }else{
                event.reply(SimpleEmbed("Error :",badarg.tra[lang]));
            }
            
        }
        if(first=="dev"){
            event.reply(SimpleEmbed("Dev : ","luk#3380"));
        }
        if(first=="f3"){
            if(interaction::exist(u)){
                interaction::toggleDebug(u);
            }
        }
        if(first=="help"){
            event.reply(SimpleEmbed(pomoc.tra[lang],commands.tra[lang]));
        }
        if(first=="lang"){
            std::string second = std::get<std::string>(event.get_parameter("lang"));
            if(second=="pl"){
                db.get(u)->objGet("lang")->set(l_pl);
                console.log(event.command.msg.author.username+" zmienia język na polski");
                event.reply(SimpleEmbed("Info","znieniono język na polski"));
            }else  if(second=="en"){
                db.get(u)->objGet("lang")->set(l_en);
                console.log(event.command.msg.author.username+" zmienia język na angielski");
                event.reply(SimpleEmbed("Info","changed language to english"));
            }else{
                event.reply(SimpleEmbed("Error :",badarg.tra[lang]));
            }
            
        }
        if(first=="skin"){
            std::string second = std::get<std::string>(event.get_parameter("opt"));
            
                if(second=="give"&&event.command.msg.author.id==dpp::snowflake(537649475494215690)){
                    try{
                        std::string third = std::get<std::string>(event.get_parameter("skin"));
                        skins::giveSkin(std::stoll(third),u,event.command.msg.guild_id);
                    }catch(...){
                        event.reply(SimpleEmbed("Error :",badarg.tra[lang]));
                    }
                    
                }else if(second=="set"){
                    try{
                        std::string third = std::get<std::string>(event.get_parameter("skin"));
                        skins::setSkin(std::stoll(third),u,event.command.msg.guild_id);
                        int i = skins::getSetSkin(u,event.command.msg.guild_id);
                        event.reply(SimpleEmbed("Skiny",skins::getSkin(i)->emoji[0].t+'\n'+skins::getSkin(i)->emoji[0].b));
                    }catch(...){
                        event.reply(SimpleEmbed("Error :",badarg.tra[lang]));
                    }
                }else if(second=="now"){
                    try{
                        int i = skins::getSetSkin(u,event.command.msg.guild_id);
                        event.reply(SimpleEmbed("Skiny",skins::getSkin(i)->emoji[0].t+'\n'+skins::getSkin(i)->emoji[0].b));
                    }catch(...){
                        event.reply(SimpleEmbed("Error :",badarg.tra[lang]));
                    }
                }else {
                std::string out;
                std::string out2;
                std::string out3;
                for(int i = 0;i<10;i++){
                    if(skins::haveSkin(i,u,event.command.msg.guild_id)){
                    out.append(emoji::getUi(i));
                    out2.append(skins::getSkin(i)->emoji[0].t);
                    out3.append(skins::getSkin(i)->emoji[0].b);
                    }
                }
                out3+='\n';
                out2+='\n';
                event.reply(SimpleEmbed("Skiny",out2+out3+out));
            }
        } });
    bot.on_button_click(interaction::button);
    bot.on_ready([&bot](const dpp::ready_t &event)
                 {
        if (dpp::run_once<struct register_bot_commands>()) {
            
                dpp::slashcommand start_cmd("start", "zaczyna grę", bot.me.id);
                start_cmd.add_option(
                        dpp::command_option(dpp::co_string, "dimension", "wymiar", true).
                            add_choice(dpp::command_option_choice("overworld", std::string("overworld"))).
                            add_choice(dpp::command_option_choice("nether", std::string("nether")))
                        );
                bot.global_command_create(start_cmd);
                dpp::slashcommand ranking_cmd("ranking", "pokazuje ranking", bot.me.id);
                ranking_cmd.add_option(
                        dpp::command_option(dpp::co_string, "dimension", "wymiar", true).
                            add_choice(dpp::command_option_choice("overworld", std::string("overworld"))).
                            add_choice(dpp::command_option_choice("nether", std::string("nether")))
                        );
                bot.global_command_create(ranking_cmd);
                dpp::slashcommand best_cmd("best", "pokazuje najlepszy", bot.me.id);
                best_cmd.add_option(
                        dpp::command_option(dpp::co_string, "dimension", "wymiar", true).
                            add_choice(dpp::command_option_choice("overworld", std::string("overworld"))).
                            add_choice(dpp::command_option_choice("nether", std::string("nether")))
                        );
                bot.global_command_create(best_cmd);
                dpp::slashcommand dev_cmd("dev", "pokezuje autora bota", bot.me.id);
                bot.global_command_create(dev_cmd);
                dpp::slashcommand help_cmd("help", "komendy", bot.me.id);
                bot.global_command_create(help_cmd);
                dpp::slashcommand lang_cmd("lang", "zmienia język", bot.me.id);
                lang_cmd.add_option(
                        dpp::command_option(dpp::co_string, "lang", "język", true).
                            add_choice(dpp::command_option_choice("pl", std::string("pl"))).
                            add_choice(dpp::command_option_choice("en", std::string("en")))
                        );
                bot.global_command_create(lang_cmd);
                dpp::slashcommand skin_cmd("skin", "skin", bot.me.id);
                skin_cmd.add_option(
                        dpp::command_option(dpp::co_string, "opt", "język", true).
                            add_choice(dpp::command_option_choice("now", std::string("now"))).
                            add_choice(dpp::command_option_choice("set", std::string("set")))
                        );
                skin_cmd.add_option(
                        dpp::command_option(dpp::co_string, "skin", "język",false).
                            add_choice(dpp::command_option_choice("alex", std::string("0"))).
                            add_choice(dpp::command_option_choice("steve", std::string("9")))
                        );
                bot.global_command_create(skin_cmd);
            
            
        } });
    bot.start(false);
}
