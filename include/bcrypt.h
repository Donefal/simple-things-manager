#pragma once

#include <string>

namespace Bcrypt {

    std::string generateHash(const std::string & password , unsigned rounds = 10 );

    bool validatePassword(const std::string & password, const std::string & hash);

}


