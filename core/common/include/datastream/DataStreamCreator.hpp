#ifndef DATA_STREAM_CREATOR_HPP
#define DATA_STREAM_CREATOR_HPP

class DataStream;

class DataStreamCreator{

public:
	static DataStreamCreator* GetInstance();

	DataStream* GetDefaultDataStream();

private:
	DataStreamCreator(){ }
	static DataStreamCreator* instance;
};

#endif
