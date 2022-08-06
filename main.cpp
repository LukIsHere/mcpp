#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <dpp/dpp.h>
using namespace std;
// print

//I'm sorry i know it's not pyhton but it's easyer than cout << something << endl; every time i want to log value
string btos(bool value)
{
    if (value == true)
        return "true";
    else if (value == false)
        return "false";
    else
        return "null";
}
void print(string text)
{
    cout << text << endl;
}
void print(int text)
{
    cout << text << endl;
}
void print(bool text)
{
    cout << btos(text) << endl;
}
void print(char text)
{
    cout << btos(text) << endl;
}



//emote taki myk wokół dpp
class emote{
    public:
    string r;
    emote(){

    }
    emote(string emoji){
        string out = "";
        for(int i = 0;i<emoji.length();i++){
            if(emoji.at(i)!='<'&&emoji.at(i)!='>') out +=emoji.at(i);
        }
        r = out;
    }
    emote(dpp::emoji emoji){
        string out = ":";
        out.append(emoji.name);
        out+=':';
        out.append(to_string(emoji.id));
        r = out;
    }
};
string getR(string emoji){
    string out = "";
    for(int i = 0;i<emoji.length();i++){
        if(emoji.at(i)!='<'&&emoji.at(i)!='>') out +=emoji.at(i);
    }
    return out;
}
string getR(dpp::emoji emoji){
    string out = ":";
    out.append(emoji.name);
    out+=':';
    out.append(to_string(emoji.id));
    return out;
}
//reanking wpis

// kolory (terminal)
map<string, string> cm = {
    {"red", "\u001b[31m"},
    {"black", "\u001b[30m"},
    {"green", "\u001b[32m"},
    {"yellow", "\u001b[33m"},
    {"blue", "\u001b[34m"},
    {"magenta", "\u001b[35m"},
    {"cyan", "\u001b[36m"},
    {"white", "\u001b[37m"},
    {"reset", "\u001b[0m"}};
// randomowoćś
int random(int to)
{
    return rand() % to + 1;
}
// funkcje pomocnicze
int64_t getid(string id)
{
    int64_t out = 0;
    int64_t te = 1;
    for (int i = 0; 18 > i; ++i)
    {
        string charr;
        charr.push_back(id.at(17 - i));
        out = stoi(charr) * te + out;
        te = te*10;
    }
    return out;
}
int64_t stoID(dpp::snowflake s){
    return getid(to_string(s));
}
class lista
{
public:
    string root;
    lista()
    {
        root = "[]";
    }
    lista(string in)
    {
        root = in;
    }
    bool include(string value)
    {
        bool out = false;
        string cur = "";
        string anal = nocar();
        for (int i = 0; i < anal.length(); i++)
        {
            if (anal.at(i) == ',')
            {

                if (cur == value)
                {
                    out = true;
                }

                cur = "";
            }
            else
            {
                cur += anal.at(i);
            }
        }
        if (cur == value)
        {
            out = true;
        }
        return out;
    }

    void push(string in)
    {
        string anal = nocar();
        if (anal != "")
            anal += ',';
        anal.append(in);
        root = addcar(anal);
    }
    void remove(string value)
    {
        string cur = "";
        string anal = nocar();
        int start = 0;
        int leng = 0;
        int fs;
        int fl;
        for (int i = 0; i < anal.length(); i++)
        {
            if (anal.at(i) == ',')
            {
                if (cur == value)
                {
                    fs = start;
                    fl = leng;
                }
                cur = "";
                start = i + 1;
                leng = 0;
            }
            else
            {
                leng++;
                cur += anal.at(i);
            }
        }
        if (cur == value)
        {
            fs = start;
            fl = leng;
        }
        string out = "";
        if (anal.at(fs + fl) == ',')
        {
            fl++;
        }
        else if (anal.at(fs - 1) == ',')
        {
            fs--;
            fl++;
        }
        for (int i = 0; i < anal.length(); i++)
        {
            if (i < fs || i > fs + fl - 1)
            {
                out += anal.at(i);
            }
        }
        root = addcar(out);
    }
    string getplain()
    {
        return root;
    }
    string get(int elid)
    {
        string cur = "";
        int id = 0;
        string anal = nocar();
        for (int i = 0; i < anal.length(); i++)
        {
            if (anal.at(i) == ',')
            {
                if (id == elid)
                {
                    return cur;
                }
                else
                {
                    cur = "";
                }
                id++;
            }
            else
            {
                cur += anal.at(i);
            }
        }
        if (id == elid)
        {
            return cur;
        }
        return "";
    }
    int size()
    {
        int out = 1;
        string anal = nocar();
        for (int i = 0; i < anal.length(); i++)
        {
            if (anal.at(i) == ',')
            {
                out++;
            }
        }
        return out;
    }

private:
    string nocar()
    {
        string out = "";
        for (int i = 0; i < root.length(); i++)
        {
            if (root.at(i) != '[' && root.at(i) != ']')
            {
                out += root.at(i);
            }
            else
            {
            }
        }
        return out;
    }
    string addcar(string in)
    {
        string out = "";
        out.append("[");
        out.append(in);
        out.append("]");
        return out;
    }
};
// meta data
class metaData
{
public:
    map<string, lista> listam;
    map<string, string> stringm;
    metaData(string input)
    {
        // end - ;
        // lista - name:[value]
        // string - name:value
        int state = 0;
        // 0 - read key
        // 1 - read value
        // 2 - read value(arr)

        string key = "";
        string value = "";
        string anal = nocar(input);
        for (int i = 0; i < anal.length(); i++)
        {

            if (anal.at(i) == ':')
            {
                if (anal.at(i + 1) == '[')
                    state = 2;
                else
                    state = 1;
            }
            else if (anal.at(i) == ']')
            {
                value += anal.at(i);
                state = 1;
            }
            else if (state == 1 && anal.at(i) == ',')
            {
                rawPut(key, value);
                key = "";
                value = "";
                state = 0;
            }
            else if (state != 0)
            {
                value += anal.at(i);
            }
            else
            {
                key += anal.at(i);
            }
        }
        if (state == 1 || state == 2)
            rawPut(key, value);
    }
    void sets(string name, string value)
    {
        stringm.insert(pair<string, string>(name, value));
    }
    void setl(string name, lista value)
    {
        listam.insert(pair<string, lista>(name, value));
    }
    void setl(string name, string value)
    {
        listam.insert(pair<string, lista>(name, lista(value)));
    }
    string *gets(string name)
    {
        return &(stringm[name]);
    }
    lista *getl(string name)
    {
        return &(listam[name]);
    }
    string getall()
    {
        string out = "{";
        bool first = true;
        // string
        map<string, string>::iterator it;
        for (it = stringm.begin(); it != stringm.end(); it++)
        {
            if (first == false)
                out += ',';
            out.append(it->first);
            out += ':';
            out.append(it->second);
            first = false;
        }
        // lista
        map<string, lista>::iterator itlista;
        for (itlista = listam.begin(); itlista != listam.end(); itlista++)
        {
            if (first == false)
                out += ',';
            out.append(itlista->first);
            out += ':';
            out.append(getl(itlista->first)->getplain());
            first = false;
        }
        // out
        out += '}';
        return out;
    }

private:
    void rawPut(string key, string value)
    {

        if (value.at(0) == '[')
        {
            // list
            setl(key, value);
        }
        else
        {
            // string
            sets(key, value);
        }
    }
    string nocar(string in)
    {
        string out = "";
        for (int i = 0; i < in.length(); i++)
        {
            if (in.at(i) != '{' && in.at(i) != '}')
            {
                out += in.at(i);
            }
            else
            {
            }
        }
        return out;
    }
    string addcar(string in)
    {
        string out = "";
        out.append("{");
        out.append(in);
        out.append("}");
        return out;
    }
};
// urzytkownicy
class user
{
    // idDC:nickDC:bestS:rrrr-mm-dd hh.mm.ss:money:{metaData} (9) 691032155643445359:luk#3333:4000:2002-12-02 03.23.00:145:{}
public:
    int64_t id;
    string nick;
    int score;
    string date;
    int money;
    int valid = 0;
    bool empty = false;
    metaData meta = metaData("{}");
    user()
    {
        empty = true;
        usercr("0: :0: :0:{}");
    }
    user(int64_t idd, string nickd, int scored, string dated)
    {
        try
        {
            id = idd;
            nick = nickd;
            score = scored;
            date = dated;
            money = 0;
            valid = 1;
        }
        catch (const std::exception &e)
        {
            valid = 0;
        }
    }
    user(int64_t idd, string nickd, int scored, string dated, int moneyd, string metad)
    {
        try
        {
            id = idd;
            nick = nickd;
            score = scored;
            date = dated;
            money = moneyd;
            meta = metaData(metad);
            valid = 1;
        }
        catch (const std::exception &e)
        {
            valid = 0;
        }
    }
    user(string data)
    {
        usercr(data);
    }
    void usercr(string data)
    {
        try
        {
            string datta[6];
            int indexdata = 0;
            bool rmeta = false;
            cout << data.length() << endl;
            for (int i = 0; data.length() > i; ++i)
            {
                string charr;
                charr.push_back(data.at(i));
                if (charr != ":" || indexdata == 5)
                {
                    datta[indexdata].append(charr);
                }
                else
                {
                    ++indexdata;
                }
            }
            id = getid(datta[0]);
            nick = datta[1];
            score = stoi(datta[2]);
            date = datta[3];
            money = stoi(datta[4]);
            meta = metaData(datta[5]);
            valid = 1;
        }
        catch (...)
        {
            valid = 0;
            cout << "błąd użytkownika : " << data << endl;
        }
    }
    void logout()
    {
        cout << getString() << endl;
    }
    string getString()
    {
        // idDC:nickDC:bestS:rrrr-mm-dd hh.mm.ss:money:{meta}
        string out;
        out.append(to_string(id));
        out.append(":");
        out.append(nick);
        out.append(":");
        out.append(to_string(score));
        out.append(":");
        out.append(date);
        out.append(":");
        out.append(to_string(money));
        out.append(":");
        out.append(meta.getall());

        return out;
    }
};
// ranki
int64_t rankint[25]; // 0-24
// skiny (postacie)
class skine
{
public:
    string emoji;
    int id;
    string name;
    int cost;
    emote r;
    skine(string emojii, int idi, string namei, int costi)
    {
        r = emote(emojii);
        emoji = emojii;
        id = idi;
        name = namei;
        cost = costi;
    }
};
skine skiny[] = {
    skine("<:p00:986984735471443969>", 0, "steve", 0),
    skine("<:p01:986984737337933864>", 1, "alex", 100),
    skine("<:p02:986985585375871117>", 2, "luktvpl", 2000)};
// bloki
map<string, int> bn;
class blok
{
public:
    int id;
    string emoji;
    string cout;
    int points;
    string name;
    string reaction;
    emote r;
    lista prop;
    blok(int bid, string bemoji, string bcout, int bpoints, string bname,lista propd=lista("[]"))
    {
        r = emote(bemoji);
        prop = propd;
        bn.insert(pair<string, int>(bname, bid));
        id = bid;
        emoji = bemoji;
        name = bname;
        cout = bcout;
        points = bpoints;
        string out = "";
        
    }
};
const blok blocks[34] = {
    blok(0, "<:00:976014562996391936>", "\u001b[42;1mg", 0, "grass"),
    blok(1, "<:01:976014584836128798>", "\u001b[40;2ms", 0, "stone"),
    blok(2, "<:02:976014603182014514>", "\u001b[44ma", 0, "air",lista("[f2w]")),
    blok(3, "<:03:986301020386758656>", "\u001b[41;1mc", 500, "cheast"),
    blok(4, "<:04:976025190741966920>", "\u001b[41;1md", 0, "dirt"),
    blok(5, "<:05:976028310289145916>", "\u001b[41mw", 0, "wood"),
    blok(6, "<:06:976028821142794240>", "\u001b[42;1ml", 0, "leaves"),
    blok(7, "<:07:976747069731667988>", "\u001b[40mc", 5, "coal"),
    blok(8, "<:08:976747112123486239>", "\u001b[44md", 100, "diamond"),
    blok(9, "<:09:976747136509173791>", "\u001b[43mg", 20, "gold"),
    blok(10, "<:10:976747165869297665>", "\u001b[41mn", 0, "netherrack"),
    blok(11, "<:11:976747199310491658>", "\u001b[40mc", 5, "coald"),
    blok(12, "<:12:976747224799272970>", "\u001b[47mi", 25, "irond"),
    blok(13, "<:13:976747252309717093>", "\u001b[42me", 200, "emeraldd"),
    blok(14, "<:14:976747278100475916>", "\u001b[47mi", 25, "iron"),
    blok(15, "<:15:976747301110444042>", "\u001b[41mr", 7, "redstone"),
    blok(16, "<:16:976747345008025620>", "\u001b[40;1md", 0, "deepslate"),
    blok(17, "<:17:976747365719486494>", "\u001b[43mg", 20, "goldn"),
    blok(18, "<:18:976747395742326794>", "\u001b[44;1ml", 5, "lapis"),
    blok(19, "<:19:976747421013012490>", "\u001b[42me", 200, "emerald"),
    blok(20, "<:20:976747440675905550>", "\u001b[47;1mq", 20, "quartz"),
    blok(21, "<:21:976747460452036618>", " \u001b[45mc", 10, "copperd"),
    blok(22, "<:22:976747483327778816>", "\u001b[44;1ml", 5, "lapisd"),
    blok(23, "<:23:976747504311877643>", "\u001b[43mg", 20, "goldd"),
    blok(24, "<:24:976747529930670110>", "\u001b[45mc", 10, "copper"),
    blok(25, "<:25:976747546405920769>", "\u001b[40mb", 0, "bedrock",lista("[unbreakable]")),
    blok(26, "<:26:976747566303686666>", "\u001b[41;1md", 0, "debris"),
    blok(27, "<:27:976747582762151976>", "\u001b[40;1mo", 0, "obsidian"),
    blok(28, "<:28:976747598763417620>", "\u001b[44md", 100, "diamondd"),
    blok(29, "<:29:976747620594749470>", "\u001b[41mr", 7, "redstoned"),
    blok(30, "<:30:976752550713892885>", "\u001b[40mb", 0, "black"),
    blok(31, "<:31:976765562275364934>", "\u001b[41;1mf", 0, "fox"),
    blok(32, "<:32:980055020315758622>", "\u001b[44;1mw", 0, "water",lista("[f2w]")),
    blok(33, "<:33:985931497489973248>", "\u001b[40mb", 0, "barrier",lista("[unbreakable]"))};
// rudy dane
int rud[6][8][2] =
    {
        {{0, 0}, {0, 1}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}, // 0
        {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}, // 1
        {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {0, 2}, {0, 0}, {0, 0}, {0, 0}}, // 2
        {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}, // 3
        {{1, 0}, {0, 1}, {2, 1}, {3, 1}, {0, 2}, {1, 2}, {2, 2}, {1, 3}}, // 4
        {{1, 0}, {1, 1}, {1, 2}, {0, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}  // 5
};
class ruda
{
public:
    int variantsCount = 5;
    int variants[5];
    int ymin;
    int ymax;
    int idn;
    int idd;
    int count;
    ruda(int vari[5], int yma, int ymi, int in, int id, int coun)
    {
        count = coun;
        try
        {
            for (int i = 0; i < 5; ++i)
            {
                variants[i] = vari[i];
            }
        }
        catch (...)
        {
        }
        ymax = yma;
        ymin = ymi;
        idn = in;
        idd = id;
    }
};
ruda rudy[9] = {
    ruda(new int[5]{0, 1, 2, 1, 0}, 150, 7, bn["iron"], bn["irond"], 40),
    ruda(new int[5]{0, 1, 2, 1, 0}, 150, 64, bn["iron"], bn["irond"], 40),
    ruda(new int[5]{2, 1, 2, 1, 1}, 100, 32, bn["copper"], bn["copperd"], 40),
    ruda(new int[5]{0, 1, 0, 1, 4}, 92, 7, bn["lapis"], bn["lapisd"], 30),
    ruda(new int[5]{1, 2, 3, 4, 1}, 80, 7, bn["redstone"], bn["redstoned"], 45),
    ruda(new int[5]{0, 1, 2, 1, 0}, 150, 64, bn["coal"], bn["coald"], 45),
    ruda(new int[5]{0, 1, 3, 1, 0}, 100, 7, bn["diamond"], bn["diamondd"], 30),
    ruda(new int[5]{0, 1, 2, 1, 0}, 150, 50, bn["gold"], bn["goldd"], 35),
    ruda(new int[5]{3, 3, 3, 3, 3}, 150, 7, bn["emerald"], bn["emeraldd"], 60)};
// intacctancja gry
class instancja
{
public:
    int id = 1000;
    int x = 32;
    int y = 128;
    int  mapa[192][64];          // id bloków
    int skin = 0; // id skinów
    int score = 0;
    bool end = false;
    bool valid = false;
    int type = 1;
    int height;
    int width;
    int moves = 0;
    int64_t user;
    string nick;
    int durability = 999999;
    lista challanges;
    dpp::message msg;
    instancja(){
        valid = false;
        end = true;
    }
    instancja(int64_t userd,string nicke,int skind = 0,int typed=1,int durabilityd=99999,lista challangesd=lista())//0-own (9x9) 1-normal 
    { // konstruktor
        id  = rand();
        valid = true;
        nick = nicke;
        user = userd;
        challanges = challangesd;
        durability = durabilityd;
        skin = skind;
        type = typed;
        switch(typed){
            case 0:
            height = 9;
            width = 9;
            break;
            case 1:
            height = 192;
            width = 64;
            // powietrze
            for (int iy = 0; iy < 192; ++iy)
            {
                for (int ix = 0; ix < 64; ++ix)
                {
                    int iiy = 191 - iy;
                    SetBlock(ix, iy, 2);
                }
            }
            // bedrock 0-7
            int help = random(7);
            int help2 = 0;
            for (int ix = 0; ix < 64; ++ix)
            {
                help2 = random(5);
                if (help2 == 1 && help + 2 <= 7)
                    help = help + 2;
                if (help2 == 2 && help + 1 <= 7)
                    help = help + 1;
                if (help2 == 1 && help - 2 >= 1)
                    help = help - 2;
                if (help2 == 1 && help - 1 >= 1)
                    help = help - 1;
                for (int iy = 0; iy < help; ++iy)
                {

                    SetBlock(ix, iy, bn["bedrock"]);
                }
            }
            // deepslate
            help = random(7);
            for (int ix = 0; ix < 64; ++ix)
            {
                help2 = random(7);
                if (help2 == 2 && help + 1 <= 7)
                    help = help + 1;
                if (help2 == 1 && help - 1 >= 1)
                    help = help - 1;
                for (int iy = 0; iy < help + 64; ++iy)
                {
                    if (GetBlockID(ix, iy) == 2)
                        SetBlock(ix, iy, bn["deepslate"]);
                }
            }
            // stone + trawa +  drzewa +  woda + spawn
            help = random(24);
            for (int ix = 0; ix < 64; ++ix)
            {
                help2 = random(7);
                if (help2 == 2 && help + 1 <= 24)
                    help = help + 1;
                if (help2 == 1 && help - 1 >= 1)
                    help = help - 1;
                for (int iy = 64; iy < help + 128; ++iy)
                {
                    if (GetBlockID(ix, iy) == 2)
                        SetBlock(ix, iy, bn["stone"]);
                }
                int fixed = help + 128;
                if (fixed > 135)
                {
                    SetBlock(ix, fixed + 0, bn["dirt"]);
                    SetBlock(ix, fixed + 1, bn["dirt"]);
                    SetBlock(ix, fixed + 2, bn["grass"]);
                    if (ix == 32)
                        SetSpawn(x, fixed + 3);
                    if (random(9) == 7)
                    {
                        SetBlock(ix, fixed + 3, bn["wood"]);
                        SetBlock(ix, fixed + 4, bn["leaves"]);
                        SetBlock(ix - 1, fixed + 4, bn["leaves"]);
                        SetBlock(ix + 1, fixed + 4, bn["leaves"]);
                        SetBlock(ix, fixed + 5, bn["leaves"]);
                        if (ix == 32)
                            SetSpawn(x, fixed + 6);
                    }
                }
                else
                {
                    SetBlock(ix, fixed + 0, bn["dirt"]);
                    SetBlock(ix, fixed + 1, bn["dirt"]);
                    SetBlock(ix, fixed + 2, bn["dirt"]);
                    if (ix == 32)
                        SetSpawn(x, fixed + 3);
                    for (int iy = 128; iy < 135 + 4; ++iy)
                    {
                        if (GetBlockID(ix, iy) == 2)
                            SetBlock(ix, iy, bn["water"]);
                    }
                }
            }
            // rudy
            for (int i = 0; i < 9; ++i)
            {
                for (int ir = 0; ir < rudy[i].count; ++ir)
                {
                    int tx = random(62);
                    int ty = random(rudy[i].ymax - rudy[i].ymin) + rudy[i].ymin;
                    int v = rudy[i].variants[random(5) - 1];
                    for (int pi = 0; pi < 8; ++pi)
                    {
                        int ttx = rud[v][pi][0] + tx;
                        int tty = rud[v][pi][1] + ty;
                        if (GetBlockID(ttx, tty) == bn["stone"])
                            SetBlock(ttx, tty, rudy[i].idn);
                        if (GetBlockID(ttx, tty) == bn["deepslate"])
                            SetBlock(ttx, tty, rudy[i].idd);
                    }
                }
            }
        break;
        }
        
        // render konsola
        // conout();
        // cout << DcOutp(0);
    }
    
    void setMSG(dpp::message msgd){
        msg = msgd;
    }
    void build(string mapS){
        //to-do
    }
    string getbuildS(){
        //to-do
        return "non";
    }
    void finish()
    {
        end = true;
    }
    void SetSpawn(int xv, int yv)
    {
        for (int i = 0; i < 4; ++i)
        {
            x = xv;
            y = yv;
        };
    }
    void SetBlock(int x, int y, int block)
    {
        if(x<0||x>=width||y<0||y>=height) return;
        try
        {
            int b = block + 1;
            mapa[y][x] = b;
        }
        catch (...)
        {
        }
    }
    blok GetBlock(int x, int y)
    {
        if(x<0||x>=width||y<0||y>=height) return blocks[33];
        try
        {
            if (mapa[y][x] == 0)
                return blocks[33];
            else
                return blocks[mapa[y][x] - 1];
        }
        catch (...)
        {
            return blocks[33];
        }
    }
    int GetBlockID(int x, int y)
    {
        if(x<0||x>=width||y<0||y>=height) return 33;
        try
        {
            if (mapa[y][x] == 0)
                return 33;
            else
                return mapa[y][x] - 1;
        }
        catch (...)
        {
            return 33;
        }
    }
    void conout()
    {
        cout << endl;
        for (int iy = 0; iy < 192; ++iy)
        {
            for (int ix = 0; ix < 64; ++ix)
            {

                int iiy = 191 - iy;
                cout
                    << GetBlock(ix, iiy).cout;
            }
            cout << "\u001b[0m" << endl;
        }
        cout << endl;
    }
    void conouts(int xl, int yl)
    {
        cout << "Punkty : " << score << endl;
        for (int iy = 0; iy < 9; ++iy)
        {
            for (int ix = 0; ix < 9; ++ix)
            {

                int iiy = yl + 4 - iy;
                int iix = xl + ix - 4;
                if (iix==x&&iiy==y)
                {
                    cout << "\u001b[46mp";
                }
                else
                {
                    cout
                        << GetBlock(xl + ix - 4, iiy).cout;
                }
            }
            cout << "\u001b[0m" << endl;
        }
        cout << endl;
    }
    void conoutsp()
    {
        conouts(x, y);
    }
    // move
    void move(int xm, int ym)
    {
        if (!GetBlock(x + xm, y + ym).prop.include("unbreakable"))
        {
            moves++;
            x += xm;
            y += ym;
            score = score + GetBlock(x, y).points;
            if (!GetBlock(x, y).prop.include("f2w"))
            {
                SetBlock(x, y, bn["air"]);
            }
            if (GetBlock(x, y - 1).prop.include("f2w"))
            {
                move(0, -1);
            }
            if (GetBlock(x, y - 1).id == bn["bedrock"])
                finish();
        }
    }
    string DcOut(int xl, int yl)
    {
        string out = "punkty : " + to_string(score) + "\n";
        for (int iy = 0; iy < 9; ++iy)
        {
            for (int ix = 0; ix < 9; ++ix)
            {
                int iiy = yl + 4 - iy;
                int iix = xl + ix - 4;
                if (iix==x&&iiy==y)
                {
                    out.append(skiny[skin].emoji);
                }
                else
                {
                    out.append(GetBlock(iix, iiy).emoji);
                }
            }
            out.append("\n");
        }
        out.append("\n");
        return out;
    }
    string DcOutp()
    {
        return DcOut(x, y);
    }
    string DcOutEnd(){
        string out = "Koniec Gry.<@";
        out.append(to_string(user));
        out.append(">zdobył punktów : ");
        out.append(to_string(score));
        return out;
    }
    // discord out
    // msg container - map
    // player container - map (in future)
};
map<int64_t, instancja> sescje;
// dane użytkowników load/save
map<int64_t, user> usersData;
//ranking
class rankk{
    public:
    int s = 0;
    string n = "brak";
    rankk(){

    }
    rankk(int score,string name){
        s = score;
        n = name;
    }
    string st(){
        string out = ". ";
        out.append(n);
        out.append(" : ");
        out.append(to_string(s));
        return out;
    }
};
map<int,rankk> ranking;//0-24 ranking 25-help spot
void addToRank(rankk usr){// 2000
    if(ranking[24].s<usr.s){
        int pl = 24;//set minimum spot
        for(int i = 23;0<=i;i--){
            if(ranking[i].s<usr.s)pl=i;//if heigher set spot higher
        }
        for(int i = 24;i>=pl;i--){ //loop from 24 to place
            ranking[i+1] = ranking[i]; //move lover in rank
            if(i==pl){
                ranking[pl] = usr; //set in place
            }
        }
        
    }   
}
class cmd{
    public:
    string cont;
    cmd(string text){
        cont  = text;
    }
    string get(int p){

        return "cuś";
    }
};
string logRank(){
    string out = "Ranking :\n";
    for(int i = 0;i<25;i++){
        out.append(to_string(i+1));
        out.append(ranking[i].st());
        out.append("\n");
    }
    return out;
}
void reloadRank(){
    ranking = map<int,rankk>();
    map<int64_t, user>::iterator it;
   for (it = usersData.begin(); it != usersData.end(); it++)
    {
        addToRank(rankk(it->second.score,it->second.nick));   
    } 
}
void loadUSERS()
{
    string tt;
    ifstream test2("data.txt");
    while (getline(test2, tt))
    {
        user u = user(tt);
        cout << u.id << endl;
        print(u.getString());
        usersData[u.id] = u;
    }
    reloadRank();
    test2.close();
    logRank();
}
void saveUSERS()
{
    ofstream test("data.txt");
    map<int64_t, user>::iterator it;
    for (it = usersData.begin(); it != usersData.end(); it++)
    {
        cout << it->second.getString() << endl;
        test << it->second.getString() << endl;
        
    }
    test.close();
}
// ranking
void gend(int64_t usr,string nick,int score,lista data = lista("[]"),instancja gla = instancja()){
    if(usersData[usr].valid){//user istnieje
        if(usersData[usr].score<score){
            usersData[usr].score=score;
            reloadRank();
        }
    } else{//nie istnieje
        usersData[usr] = user(usr,nick,score,"0000-00-00 00.00.00",0,"{}");
        reloadRank();
    }
    saveUSERS();
}


//nwm
string l = "l";
string r = "r";
string d = "d";
string stop = "stop";
// główna funkcja
lista uiEmoji = lista("[r_,l_,d_,stop]");
int main()
{
    
    loadUSERS();
    srand(time(0));
    print(logRank());
    string tt;
    ifstream test2("token.txt");
    string token;
    getline(test2, token);
    test2.close();
    
    dpp::cluster bot = dpp::cluster(token, dpp::i_default_intents | dpp::i_message_content | dpp::i_guild_messages | dpp::i_guild_integrations);
    bot.on_log(dpp::utility::cout_logger());
    bot.on_message_create([&bot](const dpp::message_create_t &event){

    });
    bot.on_button_click([&bot](const dpp::button_click_t &event){
        int64_t u = event.command.member.user_id;
        if(sescje[u].valid&&sescje[u].msg.channel_id==event.command.channel_id&&sescje[u].msg.id == event.command.msg.id){
            instancja *game = &(sescje[event.command.member.user_id]);
            //cout << event.custom_id << endl;
            if(event.custom_id=="l")game->move(-1,0);
            if(event.custom_id=="r")game->move(1,0);
            if(event.custom_id=="d")game->move(0,-1);
            if(event.custom_id=="stop")game->finish();
            if(!game->end){
                event.reply(dpp::ir_update_message,game->msg.set_content(game->DcOutp()));

            }else{
                string nick = game->nick;
                int score = game->score;
                gend(u,nick,score,lista(),*game);
                event.reply(dpp::ir_update_message,game->msg.set_content(game->DcOutEnd()));
                sescje.erase(event.command.member.user_id);
            }
        }

    });
    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "test"||event.command.get_command_name() == "start") {
            const int64_t sender = int64_t(event.command.usr.id);
            sescje.insert(pair<int64_t,instancja>(sender,instancja(sender,event.command.usr.username,0,1,9999,lista())));
            dpp::message mess = dpp::message(event.command.channel_id,sescje[sender].DcOutp());
            dpp::component btns = dpp::component();
            btns.add_component(dpp::component().set_label("").set_type(dpp::cot_button).set_emoji("◀️").set_style(dpp::cos_primary).set_id(l));
            btns.add_component(dpp::component().set_label("").set_type(dpp::cot_button).set_emoji("🔽").set_style(dpp::cos_primary).set_id(d));
            btns.add_component(dpp::component().set_label("").set_type(dpp::cot_button).set_emoji("▶️").set_style(dpp::cos_primary).set_id(r));
            btns.add_component(dpp::component().set_label("").set_type(dpp::cot_button).set_emoji("🛑").set_style(dpp::cos_danger).set_id(stop));
            mess.add_component(btns);
            mess.set_channel_id(event.command.channel_id);
            mess = bot.message_create_sync(mess);
            sescje[sender].setMSG(mess);
            thread end([&bot,&sender](){
                int idea  = sescje[sender].id;
                this_thread::sleep_for(chrono::minutes(5));
                if(sescje[sender].valid,sescje[sender].id==idea){
                    instancja *game = &(sescje[sender]);
                    gend(game->user,game->nick,game->score,lista(),*game);
                    bot.message_edit(sescje[sender].msg.set_content(sescje[sender].DcOutEnd()));
                    sescje.erase(sender);
                }
                
            });
            end.detach(); 
        }
        if (event.command.get_command_name() == "ranking"){
            event.reply(logRank());
        }
        if (event.command.get_command_name() == "best"){
            if(usersData[event.command.usr.id].valid){
                string out = "Twój najlepszy wynik to : ";
                out.append(to_string(usersData[event.command.usr.id].score));
                event.reply(out);
            }else{
                event.reply("brak najlepszego wyniku w bazie danych");
            }
        }
        if(event.command.get_command_name() == "autor"){
            event.reply("Twórcą bot'a jest luktvpl#3144.");
        }
        if(event.command.get_command_name() == "help"){
            event.reply("Dostępne komędy : \n/start - zaczyna gre\n/ranking - pokazuje ranking\n/best - pokazuje najlepszy wynik\n/autor - pokazuje autora bot'a \n/help - pokazuje dostępne komędy");
        }


    });
    bot.on_message_create([&bot](const dpp::message_create_t& event){
        string cont = event.msg.content;
        if (cont == ".test"||cont == ".start") {
            const int64_t sender = int64_t(event.msg.author.id);
            sescje.insert(pair<int64_t,instancja>(sender,instancja(sender,event.msg.author.username,0,1,9999,lista())));
            dpp::message mess = dpp::message(event.msg.channel_id,sescje[sender].DcOutp());
            dpp::component btns = dpp::component();
            btns.add_component(dpp::component().set_label("").set_type(dpp::cot_button).set_emoji("◀️").set_style(dpp::cos_primary).set_id(l));
            btns.add_component(dpp::component().set_label("").set_type(dpp::cot_button).set_emoji("🔽").set_style(dpp::cos_primary).set_id(d));
            btns.add_component(dpp::component().set_label("").set_type(dpp::cot_button).set_emoji("▶️").set_style(dpp::cos_primary).set_id(r));
            btns.add_component(dpp::component().set_label("").set_type(dpp::cot_button).set_emoji("🛑").set_style(dpp::cos_danger).set_id(stop));
            mess.add_component(btns);
            mess.set_channel_id(event.msg.channel_id);
            mess = bot.message_create_sync(mess);
            sescje[sender].setMSG(mess);
            thread end([&bot,&sender](){
                int idea  = sescje[sender].id;
                this_thread::sleep_for(chrono::minutes(5));
                if(sescje[sender].valid,sescje[sender].id==idea){
                    instancja *game = &(sescje[sender]);
                    gend(game->user,game->nick,game->score,lista(),*game);
                    bot.message_edit(sescje[sender].msg.set_content(sescje[sender].DcOutEnd()));
                    sescje.erase(sender);
                }
                
            });
            end.detach(); 
        }
        if (cont == ".ranking"){
            event.reply(logRank());
        }
        if (cont == ".best"){
            if(usersData[event.msg.author.id].valid){
                string out = "Twój najlepszy wynik to : ";
                out.append(to_string(usersData[event.msg.author.id].score));
                event.reply(out);
            }else{
                event.reply("brak najlepszego wyniku w bazie danych");
            }
        }
        if(cont == ".autor"){
            event.reply("Twórcą bot'a jest luktvpl#3144.");
        }
        if(cont == ".help"){
            event.reply("Dostępne komędy : \n/.tart - zaczyna gre\n.ranking - pokazuje ranking\n.best - pokazuje najlepszy wynik\n.autor - pokazuje autora bot'a \n.help - pokazuje dostępne komędy");
        }
    });
    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(
                dpp::slashcommand("test", "nie tykać", bot.me.id)
            );
            bot.global_command_create(
                dpp::slashcommand("start", "zaczyna gre", bot.me.id)
            );
            bot.global_command_create(
                dpp::slashcommand("ranking", "podaje ranking", bot.me.id)
            );
            bot.global_command_create(
                dpp::slashcommand("best", "podaje najlepszy wynik", bot.me.id)
            );
            bot.global_command_create(
                dpp::slashcommand("autor", "podaje najlepszy wynik", bot.me.id)
            );
            bot.global_command_create(
                dpp::slashcommand("help", "podaje najlepszy wynik", bot.me.id)
            );
        }
    });
    saveUSERS();
    bot.start(false);
    
}