#pragma once

namespace parsium {
namespace mckeeman {

struct RuleBuilder;

class ZString8 {
    char* characters = "\0";
};

template<typename T>
struct Property {
    ZString8 name;
    T value;
};  

class AlternativeMetadataBuilder {
    

public:
};

}}
