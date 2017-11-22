#ifndef JSON_DATA_HPP
#define JSON_DATA_HPP

#include "../include/data/Data.hpp"
#include "../include/json/json.h"

class JsonData : public Data{
public:
    JsonData(){ }
    JsonData()

private:
    JsonData(const Json::Value& json):m_json(json){ }

public:
    Data* CreateData(){ return new JsonData(); }

    Status Read(ostream&);
    Status Write(istream&) const;

    Status Read(const std::string&);
    Status Write(const std::string&) const;

    Status ReadFromStr(const std::string&);
    Status WriteToStr(const std::string&) const;

    size_type size() const{ return m_json.size(); }
    bool empty() const{ return m_json.empty(); }
    void clear(){ return m_json.clear(); }

    std::string asString() const{ return m_json.asString(); }
    int asInt() const{ return m_json.asInt(); }
    double asDouble() const{ return m_json.asDouble(); }
    bool asBool() const{ return m_json.asBool(); }

    bool isNull() const{ return m_json.isNull(); }
    bool isBool() const{ return m_json.isBool(); }
    bool isInt() const{ return m_json.isInt(); }
    bool isDouble() const{ return m_json.isDouble(); }
    bool isNumeric() const{ return m_json.isNumeric(); }
    bool isString() const{ return m_json.isString(); }
    bool isArray() const{ return m_json.isArray(); }
    bool isObject() const{ return m_json.isObject(); }

    Data* &operator[]( size_type index ){ return new JsonData(m_json[index]); }
    const Data* &operator[]( size_type index ) const{ return new JsonData(m_json[index]); }

    Data* &operator[]( const std::string &key ){ return new JsonData(m_json[key]); }
    const Data* &operator[]( const std::string &key ) const{ return new JsonData(m_json[key]); }

    bool isValidIndex( size_type index ) const{ return m_json.isValidIndex(index); }

    void &append( const Value &value ){ m_json.append(); }

    void removeMember( const std::string &key ){ m_json.removeMember(key); }
    bool isMember( const std::string &key ) const{ m_json.isMember(key); }

public:
    Json::Value& m_json;
};

#endif
