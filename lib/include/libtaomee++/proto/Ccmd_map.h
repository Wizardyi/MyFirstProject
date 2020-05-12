/*
 * =====================================================================================
 *
 *       Filename:  a.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/10/2011 11:55:09 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  jim (xcwen), jim@taomee.com
 *        Company:  taomee
 *
 * =====================================================================================
 */
#ifndef  CCMD_MAP_H
#define  CCMD_MAP_H
#include <string.h>
#include <stdio.h>
#include <map>
#include <assert.h>
#include <libtaomee++/proto/proto_base.h>
extern "C" {
#include <libtaomee/log.h>
}

/**
 *Ccmdmap:
 * 命令--私有结构
 */

template <class _Tp > 
class Ccmd_map{
	public:
		typedef _Tp  T_ITEM  ;
		std::map< uint32_t ,T_ITEM > cmdmap ;
	private:	
	public:
		typedef typename std::map<uint32_t,T_ITEM >::iterator  iterator;
		Ccmd_map()
		{
		}
		inline void initlist(T_ITEM * p_item_list, int count ){
             
            std::vector<T_ITEM>  item_list( p_item_list, p_item_list+count );
            this->initlist(item_list );
		}

		inline void initlist(std::vector<T_ITEM>& item_list){
			for (int i=0;i<item_list.size();i++ ){
				uint32_t cmdid=item_list[i].cmdid ;
				assert( cmdid!=0 );
                assert(this->cmdmap.find(cmdid)==this->cmdmap.end() );
                
                
				this->cmdmap[cmdid]= item_list[i];
			}
		}


		inline T_ITEM * getitem(uint32_t cmdid){
			if (this->cmdmap.find(cmdid)!=this->cmdmap.end() ){
				return  &this->cmdmap[cmdid];
			}else{
				return  NULL;
			}
		}
};

template <class _Tp > 
struct Ccmd{
	public:
		typedef _Tp  T_Func;
		uint32_t cmdid;
		Cmessage* proto_pri_msg;
		uint32_t  md5_tag; //md5值
		uint32_t  bind_bitmap;
		T_Func   func;
};

#include <libtaomee++/utils/tcpip.h>
#include <libtaomee++/proto/proto_util.h>

//支持连接后端的类, _Tp : 
template <class _Tp > 
class Cconnect_client
{
private:
	typedef _Tp  T_Func;
	int fd;
	std::string server_conf;
	bool is_hex_cmd;
	const char * cmd_str( uint32_t cmdid ){
		static char cmd[128];
		if ( this->is_hex_cmd ){
			sprintf(cmd,"%04X", cmdid);
		}else{
			sprintf(cmd,"%u", cmdid);
		}
		return cmd;
	}
	Ccmd< T_Func > * getitem( uint32_t cmdid ){
		 return this->cmd_map.getitem( cmdid );
	}

	Ccmd_map< Ccmd< T_Func > >  cmd_map;
public:
	void init_cmd_map( Ccmd< T_Func >* p_cmd_list,uint32_t cmd_count  ){
		this->cmd_map.initlist(p_cmd_list,cmd_count );
	}
	int get_fd(){
		return this->fd;
	}

	//是否fd相等
	bool eq_fd(int  test_fd ){
		return this->fd==test_fd;
	}

	void  set_disconnected(){
		this->fd=-1;
	}

	
    Cconnect_client( const char * addr,bool is_hex_cmd_flag=true ){
		this->server_conf=addr;
		this->is_hex_cmd=is_hex_cmd_flag;
		this->fd=-1;
	}
	int send_msg( char * head_buf , Cmessage * c_in ){
		if (this->fd== -1) {
			this->connect();
			if ((this->fd== -1) ) {
				DEBUG_LOG( "send to  %s failed: fd=%d ", this->server_conf.c_str() , fd);
				return 0;
			}else{
			}
		}
		int ret=net_send_msg(fd, (char*)head_buf, c_in   );
		return ret;
	}


	bool get_cmd_info( uint32_t cmdid, Ccmd<  T_Func>   **  pp_cmd_item ,char * buf,  uint32_t buf_len )
	{
		Ccmd<  T_Func> * p_cmd_item =this->cmd_map.getitem(cmdid );
		if (!p_cmd_item){
			KDEBUG_LOG(0, "err: pkglen error, cmdid=%s, bodylen=%u",  cmd_str(cmdid),buf_len  );
			return false;
		}
		bool unpack_ret=  p_cmd_item->
			proto_pri_msg->read_from_buf_ex( buf,buf_len  );
		if (unpack_ret){
			*pp_cmd_item= p_cmd_item;
		}else{
			*pp_cmd_item= NULL;
			KDEBUG_LOG(0, "err: pkglen error, cmdid=%s, bodylen=%u",cmd_str(cmdid),buf_len  );
		}
		return unpack_ret;
	}
	int connect()
	{
		//this->server_conf.c_str(), 0, 65535, 1
		const char* service_name = this->server_conf .c_str()  ;
		uint32_t svr_id=0;
		int bufsz=65535;
		int timeout=1;
		stru_ip_port ip_port;
		int ret=unpack_addr(service_name ,  &ip_port  );
		int ret_fd;
		if(ret==0){
			this->fd=connect_to_svr(ip_port.addr,ip_port.port, bufsz,timeout);
		}else{
			this->fd=connect_to_service(service_name,svr_id, bufsz,timeout);
		}
		if (this->fd!=-1){//回调
			this->on_connect();
		}

		return ret;
	}
	virtual void on_connect(){}

};




#endif  /* CCMD_MAP_H */
