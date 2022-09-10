#include "include/world.hpp"
#include "include/utility.hpp"
//rudy overworld
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
    ruda(new int[5]{0, 1, 2, 1, 0}, 150, 7, b_stone_iron, b_deepslate_iron, 40),
    ruda(new int[5]{0, 1, 2, 1, 0}, 150, 64, b_stone_iron, b_deepslate_iron, 40),
    ruda(new int[5]{2, 1, 2, 1, 1}, 100, 32, b_stone_copper, b_deepslate_copper, 40),
    ruda(new int[5]{0, 1, 0, 1, 4}, 92, 7, b_stone_lapis, b_deepslate_lapis, 30),
    ruda(new int[5]{1, 2, 3, 4, 1}, 80, 7, b_stone_redstone, b_deepslate_redstone, 45),
    ruda(new int[5]{0, 1, 2, 1, 0}, 150, 64, b_stone_coal, b_deepslate_coal, 45),
    ruda(new int[5]{0, 1, 3, 1, 0}, 100, 7, b_stone_diamond, b_deepslate_diamond, 30),
    ruda(new int[5]{0, 1, 2, 1, 0}, 150, 50, b_stone_gold, b_deepslate_gold, 35),
    ruda(new int[5]{3, 3, 3, 3, 3}, 150, 7, b_stone_emerald, b_deepslate_emerald, 60)};

//class world{
        //public:
            //int *w;
            //int height;
            //int width;
            //int playerSkin;
            //int score;
            //int durability;
            //int x,y;
            //bool valid;
            //bool end;
            world::world::world(){
                valid = false;
                w = nullptr;
            }
            world::world::world(int worldType,int skin,int dur,int language){
                lang = language;
                afk = 0;
                end = false;
                valid = true;
                score = 0;
                WorldT = worldType;
                playerSkin = skin;
                durability = dur;
                id=rand();
                //world generation
                switch (worldType)
                {
                case 0:{//overworld
                        width = 64;
                        height = 192;
                        w = new int16_t[192*64];
                        // bedrock 0-7
                        int help = utility::random(7);
                        int help2 = 0;
                        for (int ix = 0; ix < 64; ++ix)
                        {
                            help2 = utility::random(5);
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
                                setBlock(ix, iy, b_bedrock);
                            }
                        }
                        // deepslate
                        help = utility::random(7);
                        for (int ix = 0; ix < 64; ++ix)
                        {
                            help2 = utility::random(7);
                            if (help2 == 2 && help + 1 <= 7)
                                help = help + 1;
                            if (help2 == 1 && help - 1 >= 1)
                                help = help - 1;
                            for (int iy = 0; iy < help + 64; ++iy)
                            {
                                if (getBlockId(ix, iy) == b_air)
                                    setBlock(ix, iy, b_deepslate);
                            }
                        }
                        // stone + trawa +  drzewa +  woda + spawn
                        help = utility::random(24);
                        for (int ix = 0; ix < 64; ++ix)
                        {
                            help2 = utility::random(7);
                            if (help2 == 2 && help + 1 <= 24)
                                help = help + 1;
                            if (help2 == 1 && help - 1 >= 1)
                                help = help - 1;
                            for (int iy = 64; iy < help + 128; ++iy)
                            {
                                if (getBlockId(ix, iy) == b_air)
                                    setBlock(ix, iy, b_stone);
                            }
                            int fixed = help + 128;
                            if (fixed > 135)
                            {
                                setBlock(ix, fixed + 0, b_dirt);
                                setBlock(ix, fixed + 1, b_dirt);
                                setBlock(ix, fixed + 2, b_grass);
                                if (ix == 32)x = 32;
                                    
                                if (utility::random(9) == 7)
                                {
                                    setBlock(ix, fixed + 3, b_wood);
                                    setBlock(ix, fixed + 4, b_leaves);
                                    setBlock(ix - 1, fixed + 4, b_leaves);
                                    setBlock(ix + 1, fixed + 4, b_leaves);
                                    setBlock(ix, fixed + 5, b_leaves);
                                    if (ix == 32)x = 32;
                                        
                                }
                            }
                            else
                            {
                                setBlock(ix, fixed + 0, b_dirt);
                                setBlock(ix, fixed + 1, b_dirt);
                                setBlock(ix, fixed + 2, b_dirt);
                                if (ix == 32)x= 32;
                                    
                                for (int iy = 128; iy < 135 + 4; ++iy)
                                {
                                    
                                    if (getBlockId(ix, iy) == b_air)
                                        setBlock(ix, iy, b_water);
                                }
                            }
                        }
                        // rudy
                        for (int i = 0; i < 9; ++i)
                        {
                            for (int ir = 0; ir < rudy[i].count; ++ir)
                            {
                                int tx = utility::random(62);
                                int ty = utility::random(rudy[i].ymax - rudy[i].ymin) + rudy[i].ymin;
                                int v = rudy[i].variants[utility::random(5) - 1];
                                for (int pi = 0; pi < 8; ++pi)
                                {
                                    int ttx = rud[v][pi][0] + tx;
                                    int tty = rud[v][pi][1] + ty;
                                    if (getBlockId(ttx, tty) == b_stone)
                                        setBlock(ttx, tty, rudy[i].idn);
                                    if (getBlockId(ttx, tty) == b_deepslate)
                                        setBlock(ttx, tty, rudy[i].idd);
                                }
                            }
                        }
                        y=191;
                        move(0,-1);
                }break;
                case 1:{//nether
                        width = 64;
                        height = 128;
                        w = new int16_t[128*64];
                        
                        //fill netherrack
                        for (int seti = 0; seti < 128; seti++) {
                        for(int sx = 0;sx<64;sx++){
                            setBlock(sx,seti,b_netherrack);
                            }
                        }
                        //lava lake
                        for(int i = 0;i<utility::random(4)+3;i++)drawCircle(utility::random(63),utility::random(100)+10,7,b_air,utility::random(2),utility::random(2)+1);
                        for(int ix = 0;ix<64;ix++){
                        for(int iy = 0;iy<25;iy++){
                            if(getBlockId(ix,iy)==b_air)setBlock(ix,iy,b_lava);
                        }
                        }
                        int tx;
                        int ty;
                        //lava dots
                        for(int i = 0;i<utility::random(100);i++){
                        ty = utility::random(127);
                        tx = utility::random(63);
                        if(getBlockId(tx,ty)==b_netherrack)setBlock(tx,ty,b_lava);
                        }
                        bool red = true;
                        if(utility::random(2)==2)red=false;
                        //grass and trees
                        for(int ix = 0;ix<64;ix++){
                        for(int iy = 0;iy<128;iy++){
                            if(red){
                            if(getBlockId(ix,iy)==b_netherrack){
                                if(getBlockId(ix,iy+1)==b_air){
                                setBlock(ix,iy,b_netherrack_red);
                                if(utility::random(7)==3){
                                    setBlock(ix,iy+1,b_wood_red);
                                    setBlock(ix,iy+2,b_leaves_red);
                                    setBlock(ix+1,iy+2,b_leaves_red);
                                    setBlock(ix,iy+3,b_leaves_red);
                                    setBlock(ix-1,iy+2,b_leaves_red);
                                }
                                }
                            }
                            }else{
                            if(getBlockId(ix,iy)==b_netherrack){
                                if(getBlockId(ix,iy+1)==b_air){
                                setBlock(ix,iy,b_netherrack_blue);
                                if(utility::random(7)==3){
                                    setBlock(ix,iy+1,b_wood_blue);
                                    setBlock(ix,iy+2,b_leaves_blue);
                                    setBlock(ix+1,iy+2,b_leaves_blue);
                                    setBlock(ix,iy+3,b_leaves_blue);
                                    setBlock(ix-1,iy+2,b_leaves_blue);
                                }
                                }
                            }
                            }
                            
                            if(getBlockId(ix,iy)==b_netherrack){
                            if(utility::random(10)==4)
                            if(getBlockId(ix,iy-1)==b_air){
                                for(int i = 0;i<utility::random(3);i++){
                                for(int i2 = 0;i2<utility::random(3);i2++){
                                    setBlock(ix+i,iy-i2,b_glowstone);//glowstone
                                }
                                }
                            }
                            }
                        }
                        }
                        //quartz
                        for(int i = 0;i<25;i++){
                        tx = utility::random(63);
                        ty = utility::random(127);
                        for(int ix = 0;ix<utility::random(5);ix++){
                            for(int iy = 0;iy<utility::random(5);iy++){
                            if(getBlockId(tx+ix,ty+iy)==b_netherrack&&!(utility::random(20)==3))setBlock(tx+ix,ty+iy,b_netherrack_quartz);
                            }
                        }
                        }
                        //debre
                        for(int i = 0;i<25;i++){
                        tx = utility::random(63);
                        ty = utility::random(127);
                        for(int ix = 0;ix<utility::random(2);ix++){
                            for(int iy = 0;iy<utility::random(2);iy++){
                            if(getBlockId(tx+ix,ty+iy)==b_netherrack&&!(utility::random(20)==3))setBlock(tx+ix,ty+iy,b_netherrack_debre);
                            }
                        }
                        }
                        //gold
                        for(int i = 0;i<25;i++){
                        tx = utility::random(63);
                        ty = utility::random(127);
                        for(int ix = 0;ix<utility::random(7);ix++){
                            for(int iy = 0;iy<utility::random(7);iy++){
                            if(getBlockId(tx+ix,ty+iy)==b_netherrack&&!(utility::random(10)==3))setBlock(tx+ix,ty+iy,b_netherrack_gold);
                            }
                        }
                        }
                        //bedrock
                        for(int i = 0;i<64;i++){
                            setBlock(i,0,b_bedrock);
                            setBlock(i,127,b_bedrock);
                        }
                        x = 32;
                        y = 126;
                        setBlock(32,126,b_air);
                        setBlock(32,125,b_netherrack);
                }break;
                case 2:{//custom
                        width = 9;
                        height = 9;
                        w = new int16_t[9*9];
                }break;
                default:{
                        valid = false;
                        w = nullptr;
                }break;
                }
            };
            world::world::world(std::string form){
                //to-do  (later update)
            };//string to world
            world::world::~world(){
                delete [] w;
            };
            void world::world::connect(dpp::message ms,int64_t usr){
                msg=ms;
                u=usr;
            };
            //output functions
            std::string world::world::getWorld(){
                //to-do  (later update)
                return "";
            };//world to string
            std::string world::world::getDC(){
                std::string out = punkty.tra[lang];
                if(w==nullptr){
                    return "świat uległ korupcji";
                }
                out.append(std::to_string(score));
                out.append("\n");
                if(debug&&!end){
                    out.append("x:");
                    out.append(std::to_string(x));
                    out.append("y:");
                    out.append(std::to_string(y));
                    out.append("d:");
                    out.append(std::to_string(durability));
                    out.append("\n");
                }
                for(int iy = 0;iy<9;iy++){
                    for(int ix = 0;ix<9;ix++){
                        int iiy = y + 4 - iy;
                        int iix = x + ix - 4;
                        if (iix==x&&iiy==y)
                        {
                            out.append(skin::getSkin(playerSkin).emoji);
                        }
                        else
                        {
                            out.append(getBlock(iix,iiy).emoji);
                        }
                    }
                    out.append("\n");
                }
                if(end){
                    out.append(endtxt);
                }
                return out;
            };//normal world
            //debug
            void world::world::log(){
                for(int iy=0;iy<height;iy++){
                    for(int ix=0;ix<width;ix++){
                        //if(getBlockId(ix,iy)==0)std::cout << ":white_large_square:";
                        //else std::cout << ":black_large_square:";
                        std::cout << getBlockId(ix,iy) << ":";
                    }
                    std::cout << std::endl;
                }
            };
            //read world
            blocks::block world::world::getBlock(int dx,int dy){
                return blocks::get(getBlockId(dx,dy));
            };
            int world::world::getBlockId(int dx,int dy){
                if(dx<0||dx>=width||dy<0||dy>=height) return b_barier;
                return w[(height-1-dy)*width+dx];
            };
            //modifi world
            void world::world::setBlock(int dx,int dy,blocks::block block){
                setBlock(dx,dy,block.id);
            };
            void world::world::setBlock(int dx,int dy,int block){
                if(dx<0||dx>=width||dy<0||dy>=height)return;
                w[((height-dy)-1)*width+dx] = block;
            };
            void world::world::drawCircle(int dx,int dy,int r,int block,int h,int w){
                
                int ax = dx;
                int ay = dy;
                int ar = r;
                for(int i = 0;i<ar;i++){
                int sqrtemp = round(sqrt(ar*ar-i*i));
                for(int wi = 0;wi<round(w);wi++){
                    for(int hi = 0;hi<round(h);hi++){
                    mirrorP(ax,ay,round(i*w)+wi,round(sqrtemp*h)+hi,block);
                    for(int iyfill = 0;iyfill<round(sqrtemp*h)+hi;iyfill++){
                    mirrorP(ax,ay,round(i*w)+wi,(round(sqrtemp*h)+hi)-iyfill,block);
                    }
                    mirrorP(ax,ay,round(sqrtemp*w)+wi,round(i*h)+hi,block);
                    for(int ixfill = 0;ixfill<round(sqrtemp*w)+wi;ixfill++){
                    mirrorP(ax,ay,(round(sqrtemp*w)+wi)-ixfill,round(i*h)+hi,block);
                    }
                    }
                }
                
                
                }
                setBlock(ax,ay,block);
            };
            void world::world::mirrorP(int sx,int sy,int dx,int dy,int block){
                setBlock(sx+dx,sy+dy,block);
                setBlock(sx+dx,sy-dy,block);
                setBlock(sx-dx,sy+dy,block);
                setBlock(sx-dx,sy-dy,block);
            };
            void world::world::fill(int dx,int dy,int x2,int y2,int block){
                for(int ix=0;ix<dx-x2;ix++){
                    for(int iy=0;iy<dy-y2;iy++){
                        setBlock(dx+ix,dy+iy,block);
                    }
                }
            };
            bool world::world::afktick(){
                if(afk>1)return true;
                afk++;
                return false;
            }
            //interaction with world
            void world::world::move(int xm,int ym){
                afk = 0;
                if(end||!valid)return;
                int tx = x+xm;
                int ty = y+ym;
                blocks::block t = getBlock(tx,ty);
                if(t.props.unbreakable)return;
                if(t.props.death){
                    finish(name+umarlw.tra[lang]+t.name);
                }
                if(t.props.free2walk){

                }else{
                    score += t.point;
                    setBlock(tx,ty,b_air);
                    durability-=1;
                    if(durability<0)finish(durabilityKoniec.tra[lang]);
                }
                x=tx;
                y=ty;
                if(getBlock(x,y-1).props.death){
                    finish(name+umarlw.tra[lang]+getBlock(x,y-1).name);
                    return;
                }
                if(getBlock(x,y-1).props.free2walk)move(0,-1);
                
            };
            void world::world::finish(std::string reason){
                endtxt = reason;
                end = true;
            };
    //};
