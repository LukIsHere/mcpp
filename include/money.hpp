#pragma once
#include "DB.hpp"
#include <string>

namespace money{
    int have(int64_t user,int64_t guild);
    void add(int amount,int64_t user,int64_t guild);
    void remove(int amont,int64_t user,int64_t guild);
    bool can(int amont,int64_t user,int64_t guild);
    class moneyMenager{
        public:
            int64_t* money;
            moneyMenager();
            moneyMenager(int64_t user,int64_t guild);
    };
} 