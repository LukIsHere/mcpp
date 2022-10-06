#pragma once
#include <string>
#include "DB.hpp"
#include "world.hpp"

namespace rankings{
    std::string get(int dimension);
    std::string get(int dimension,int64_t server);
    void save();
    void addScore(jpp::place p,int dimension,int64_t server,int64_t u);
    void init();
}
