#pragma once
#include <string>
#include "interactinoTemp.hpp"
#include "blocks.hpp"
#include "items.hpp"
#include "jpp.hpp"
#include "dpp/dpp.h"

namespace shops{
    class shop : public itmp::itmp{
        public:
        int type = 0;
        int page = 0;
        int64_t u;
        shop(int64_t usr);
        shop(int type,int64_t usr);
        void next();
        void prev();
        void buy();
        std::string message();
    };
    void setDb(jpp::jsDB& d,jpp::jsDB& dg);
    void setBot(dpp::cluster& bt);
}