#ifndef DEFAULT_CONFIGURE_READER_HPP
#define DEFAULT_CONFIGURE_READER_HPP

#include "ConfigureReader.hpp"
#include <map>

#define conver(type,name) type _conv##name(const std::string&)

class DefaultConfigureReader : public ConfigureReader{
public:
    DefaultConfigureReader(const std::string& str = std::string());
    ~DefaultConfigureReader(){}

    GetConfigureFile(){ return m_file; }
    void SetConfigureFile(conststd::string&){
        m_file = file;
        m_map.clear();
        _updateMap();
    }

    bool Contains(const std::string& key){ return m_map.find(key) != m_map.end(); }

    get(int,Int);
    get(double,Double);
    get(std::string,String);

    get(std::vector<int>,VectorInt);
    get(std::vector<double>,VectorDouble);
    get(std::vector<std::string>,VectorString);

private:
    void _updateMap();

    conver(int,Int);
    conver(double,Double);

    std::string m_file;
    std::map<string,string> m_map;
};

#endif
