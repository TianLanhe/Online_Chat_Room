#include "../include/data/DataCreator.hpp"
#include "JsonData.hpp"

DataCreator* DataCreator::instance = NULL;
mutex DataCreator::m_mutex = mutex();

DataCreator* DataCreator::GetInstance(){
    if(instance == NULL){
        m_mutex.lock();
        if(instance == NULL){
            instance = new DataCreator();
        }
        m_mutex.unlock();
    }
    return instance;
}

Data* DataCreator::GetDefaultData(){
    return new JsonData();
}
