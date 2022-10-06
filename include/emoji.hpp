#pragma once
#include <string>

#define ui_0 0
#define ui_1 1
#define ui_2 2
#define ui_3 3
#define ui_4 4
#define ui_5 5
#define ui_6 6
#define ui_7 7
#define ui_8 8
#define ui_9 9
#define ui_plus 10
#define ui_minus 11
#define ui_kup 12
#define ui_sprzedaj 13
#define ui_money 14


//              

namespace emoji
{

       class emoji{
            public:
                std::string emoj;
                emoji(std::string emo){
                    emoj = emo;
                }
       };
       std::string& getUi(int id);
       
}
