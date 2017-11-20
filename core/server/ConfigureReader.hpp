#ifndef CONFIGURE_READER_HPP
#define CONFIGURE_READER_HPP

#include <string>
#include <vector>

#define get(type,name) type get##name(const std::string&)
#define pure_get(type,name) virtual get(type,name) = 0

class ConfigureReader{
public:
    ~ConfigureReader(){}

    virtual GetConfigureFile() = 0;
    virtual void SetConfigureFile(conststd::string&) = 0;

    virtual bool Contains(const std::string&) = 0;

    pure_get(int,Int);
    pure_get(double,Double);
    pure_get(std::string,String);

    pure_get(std::vector<int>,VectorInt);
    pure_get(std::vector<double>,VectorDouble);
    pure_get(std::vector<std::string>,VectorString);
};

#endif
