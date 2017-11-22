#ifndef DATA_HPP
#define DATA_HPP

#include "../DataStructureBase.hpp"
#include <string>
#include <memory>

class istream;
class ostream;

typedef std::shared_ptr<Data> data_ptr;

class Data{
    friend ostream& operator<<(ostream&,const Data&);
    friend istream& operator>>(istream&,Data&);

public:
    typedef unsigned long size_type;

public:
    Data( int value );
    Data( unsigned int value );
    Data( double value );
    Data( const std::string &value );
    ~Data(){ }

    virtual Data* CreateData() const = 0;

    virtual Status Read(ostream&) = 0;
    virtual Status Write(istream&) const = 0;

    virtual Status Read(const std::string&) = 0;
    virtual Status Write(const std::string&) const = 0;

    virtual Status ReadFromStr(const std::string&) = 0;
    virtual Status WriteToStr(const std::string&) const = 0;

    virtual size_type size() const = 0;
    virtual bool empty() const = 0;
    virtual void clear() = 0;

    virtual std::string asString() const = 0;
    virtual int asInt() const = 0;
    virtual double asDouble() const = 0;
    virtual bool asBool() const = 0;

    virtual bool isNull() const = 0;
    virtual bool isBool() const = 0;
    virtual bool isInt() const = 0;
    virtual bool isDouble() const = 0;
    virtual bool isNumeric() const = 0;
    virtual bool isString() const = 0;
    virtual bool isArray() const = 0;
    virtual bool isObject() const = 0;

    virtual Data* &operator[]( size_type index ) = 0;
    virtual const Data* &operator[]( size_type index ) const = 0;

    virtual Data* &operator[]( const std::string &key ) = 0;
    virtual const Data* &operator[]( const std::string &key ) const = 0;

    virtual bool isValidIndex( size_type index ) const = 0;

    virtual void &append( const Value &value ) = 0;

    virtual void removeMember( const std::string &key ) = 0;
    virtual bool isMember( const std::string &key ) const = 0;
};

ostream& operator<<(ostream& out,const Data& datastr){
    datastr.Write(out);
    return out;
}

istream& operator>>(istream& in,Data& datastr){
    datastr.Read(in);
    return in;
}

#endif
