#ifndef DATA_STRUCTURE_BASE_H
#define DATA_STRUCTURE_BASE_H

#define OK 0
#define ERROR 1
#define OVERFLOW -2
#define INFEASIBLE -1

typedef int Status;

#define BEFORE_CHECK_RESULT()	\
	Status __status;

#define CHECK_RESULT(func)		\
	if((__status = func)!=OK){	\
		return __status;		\
	}							\

#define AFTER_CHECK_RESULT()	\
	return OK

#define CHECK_OVERFLOW(var)		\
	if(!var){					\
		return OVERFLOW;		\
	}

#define CHECK_ERROR(exp)		\
	if(!(exp))					\
		return ERROR

#define BEFORE_SEND_MSG(ostream)\
	std::ostream& __out = ostream

#define CHECK_RESULT_BY_MSG(func,msg_s,msg_f)	\
	if((__status = func)!=OK){			\
		__out << (msg_f) << std::endl;	\
		return __status;				\
	}else{								\
		__out << (msg_s) << std::endl;	\
	}

#define CHECK_RESULT_BY_MSG2(func,msg_f) 	\
	if((__status = func)!=OK){			\
		__out << (msg_f) << std::endl;	\
		return __status;				\
	}

#define CHECK_ERROR_BY_MSG(exp,msg_s,msg_f)	\
	if(!(exp)){						\
		__out << (msg_f) << std::endl;	\
		return ER;					\
	}else{							\
		__out << (msg_s) << std::endl;	\
	}

#define CHECK_ERROR_BY_MSG2(exp,msg_f)	\
	if(!(exp)){							\
		__out << (msg_f) << std::endl;	\
		return ER;						\
	}


#endif
