#include "DefaultConfigureReader.hpp"
#include <fstream>
using namespace  std;

#define SEPERATOR ','
#define COMMENT '#'

int DefaultConfigureReader::_convInt(const string& str){
    int ret;
    try{
        string::size_type index;
        if(str.find_first_not_of("0123456789+-") == string::npos &&
                (index = str.find_first_of('+')) == str.find_last_of('+') && (index == 0 || index == string::npos) &&
                (index = str.find_first_of('-')) == str.find_last_of('-') && (index == 0 || index == string::npos))
            ret = stoi(str);
    }catch(...){
        ret = 0;
    }
    return ret;
}

double DefaultConfigureReader::_convDouble(const string& str){
    int ret;
    try{
        string::size_type index;
        if(str.find_first_not_of("0123456789.+-") == string::npos &&
                str.find_first_of('.') == str.find_last_of('.') &&
                (index = str.find_first_of('+')) == str.find_last_of('+') && (index == 0 || index == string::npos) &&
                (index = str.find_first_of('-')) == str.find_last_of('-') && (index == 0 || index == string::npos))
            ret = stod(str);
    }catch(...){
        ret = 0;
    }
    return ret;
}

int DefaultConfigureReader::getInt(const string& key){
    return _convInt(m_map[key]);
}

double DefaultConfigureReader::getDouble(const string& key){
    return _convDouble(m_map[key]);
}

string DefaultConfigureReader::getString(const string& key){
    return m_map[key];
}

bool DefaultConfigureReader::getBool(const string &key){
    string k = m_map[key];
    for(string::size_type i=0;i<k.size();++i)
        if(k[i] >= 'A' && k[i] <= 'Z')
            k[i] += 32;
    return ((k == "true") || getInt(key) != 0);
}

#define myvecget(type,name,conv) type DefaultConfigureReader::get##name(const string& key){      \
    type ret;                         \
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

vector<string> DefaultConfigureReader::getVectorString(const string& key){
    vector<string> ret;
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

void DefaultConfigureReader::_updateMap(){
    ifstream in(m_file);
    if(in){
        string line;
        string key;
        string value;
        while(getline(in,line)){
            _removeComment(line);
            _trim(line);
            if(!line.empty() && line.find('=') != string::npos && line[0] != '='){
                key = _split(line)[0];
                _trim(key);
                value = _split(line)[1];
                _trim(value);
                m_map[key] = value;
            }
        }
    }
}

void DefaultConfigureReader::_removeComment(string& line){
    string::size_type index;
    if((index = line.find(COMMENT)) != string::npos)
        line = string(line.begin(),line.begin() + index);
}

void DefaultConfigureReader::_trim(string& line){
    if(line.empty())
        return;

    line.erase(0,line.find_first_not_of(" \t\r\v\n"));
    line.erase(line.find_last_not_of(" \t\r\v\n") + 1);
}

vector<string> DefaultConfigureReader::_split(const string& line){
    string::size_type index;
    if(line.empty() || (index = line.find('=')) == string::npos)
        return vector<string>();

    vector<string> ret;
    ret.push_back(line.substr(0,index));
    ret.push_back(line.substr(index+1));
    return ret;
}
