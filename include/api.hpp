#pragma once
#include "jpp.hpp"
#include "httplib/httplib.hpp"
#include <thread>

namespace apis
{
    void SendUpdate(std::string prop,jpp::json& data);
    void SendUpdate(std::string prop,std::string data);
}