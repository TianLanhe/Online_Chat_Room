#include "JsonData.hpp"

Status JsonData::Read(istream&){
    return OK;
}

Status JsonData::Write(ostream&) const{
    return OK;
}

Status JsonData::Read(const std::string&){
    return OK;
}

Status JsonData::Write(const std::string&) const{
    return OK;
}

Status JsonData::ReadFromStr(const std::string&){
    return OK;
}

Status JsonData::WriteToStr(std::string&) const{
    return OK;
}
