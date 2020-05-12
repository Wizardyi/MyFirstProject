/**
 * ============================================================
 * @file   reload_msg.hpp
 * @author jim (jim@taomee.com)
 * @date   2013-01-28 19:04:03
 *
 * Last-Updated: 2013-06-13 15:14:42
 *           By: jim
 *     Update #: 72
 *
 * 
 * @brief  
 * 
 * ============================================================
 */


#ifndef _CRELOAD_MSG_H_
#define _CRELOAD_MSG_H_
#include <libtaomee++/proto/proto_base.h>
#include <map>
#include <string>
#include <assert.h>

#define CREATE_SESSION_MSG_BEGIN()				\
	if (false){										


#define CREATE_SESSION_MSG(msg_t)				\
	} else if (this->msg_type==#msg_t){			\
	this->msg=new (this->msg)msg_t();			\
	ret=true;


#define	CREATE_SESSION_MSG_END()				\
	}											

	
class Creload_cmsg_base
{
protected:
	///消息的名称 如 session_login_flag_t
	std::string msg_type;
	
	///消息的指针
	Cmessage * msg;
public:
    Creload_cmsg_base(){
		this->msg=NULL;
	}

	Cmessage * get(){
		return msg;
	}

	virtual ~Creload_cmsg_base(){
		if(this->msg){
			delete this->msg;
		}
	}

	void set(Cmessage* a_msg){
		//原有的释放
		if(this->msg){
			delete this->msg;
		}
		this->msg=a_msg;
		
		if( this->msg){
			this->msg_type=this->msg->_get_type_id();
			//如果没有注册就是直接core
			int ret=this->reset_msg();
			if (!ret){
				DEBUG_LOG("NOFIND SESSION:%s NEED DEFINE TO: reset_msg",this->msg_type.c_str());
				assert(this->reset_msg()&& this->msg_type );
			}
		}
	}
	
	virtual bool reset_msg() = 0;
};

#endif /* _CRELOAD_MSG_H_ */

