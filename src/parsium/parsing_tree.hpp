#pragma once

#include <memory>
#include <string>
#include <vector>

namespace parsium {

class MckeemanItem;
class MckeemanRule;

class MckeemanAlternative {
public:
    std::vector<MckeemanRule> items_;
};

class MckeemanRule {
public:
    std::string rule_;
    std::string data_;

    std::vector<MckeemanAlternative> alternatives_;
};

}