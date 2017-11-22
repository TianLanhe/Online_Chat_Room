#ifndef DATA_CREATOR_HPP
#define DATA_CREATOR_HPP

#include <mutex>
class Data;

class DataCreator{

public:
        static DataCreator* GetInstance();

        Data* GetDefaultData();

private:
        DataCreator(){ }
        static DataCreator* instance;
        static mutex m_mutex;
};

Data* GetDefault(){
    return DataCreator::GetInstance()->GetDefaultData();
}

#endif
