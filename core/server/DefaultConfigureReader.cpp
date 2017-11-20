#include "DefaultConfigureReader.hpp"

using namespace  std;

#define SEPERATOR ','

#define myconv(type,name,conv,ret) type DefaultConfigureReader::_conv##name(const string& key){  \
    type r; \
    try{    \
        r = conv(m_map[key]);   \
    }catch(...){    \
        r = ret;    \
    }       \
    return r;       \
}

myconv(int,Int,stoi,0)

myconv(double,Double,stod,0.0)

int DefaultConfigureReader::getInt(const string& key){
    return _convInt(m_map[key]);
}

double DefaultConfigureReader::getDouble(const string& key){
    return _convDouble(m_map[key]);
}

string DefaultConfigureReader::getString(const string& key){
    return m_map[key];
}

#define myvecget(type,name,conv) myget(type,name){      \
    type r;                         \
    string str = getString(key);    \
                                    \
    if(!str.empty()){               \
        string::const_iterator cit = str.begin();           \
        string::const_iterator cur;                         \
        for (cur = str.begin(); cur != str.end(); ++cur) {  \
            if (*cur == SEPERATOR) {                        \
                ret.push_back(conv(string(cit, cur)));      \
                cit = cur;                                  \
                ++cit;                                      \
            }                                               \
        }                                                   \
        ret.push_back(conv(string(cit, cur)));              \
    }                               \
    return ret;                     \
}

myvecget(vector<int>,VectorInt,_convInt)

myvecget(vector<double>,VectorDouble,_convDouble)

myget(vector<string>,VectorString){
    vector<string> r;
    string str = getString(key);

    if(!str.empty()){
        string::const_iterator cit = str.begin();
        string::const_iterator cur;
        for (cur = str.begin(); cur != str.end(); ++cur) {
            if (*cur == SEPERATOR) {
                ret.push_back(string(cit, cur));
                cit = cur;
                ++cit;
            }
        }
        ret.push_back(string(cit, cur));
    }
    return ret;
}
