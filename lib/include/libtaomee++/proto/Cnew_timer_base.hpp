/**
 * ============================================================
 * @file   Cnew_Ctimer.hpp
 * @author jim (jim@taomee.com)
 * @date   2013-01-31 20:50:33
 *
 * Last-Updated: 2013-06-14 15:28:20
 *           By: jim
 *     Update #: 130
 *
 * 
 * @brief  定时器
 * 
 * ============================================================
 */
#ifndef _CNEW_CTIMER_BASE_H_
#define _CNEW_CTIMER_BASE_H_


#include <time.h>
#include <sys/time.h>
#include <assert.h>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <libtaomee++/proto/proto_base.h>
#ifdef __cplusplus
extern "C"
{
#endif
#include <libtaomee/log.h>
#ifdef __cplusplus
}
#endif
/** 
 * 实现原理 
 * 
 * 
 */
class Ctime_val {
public:
	struct timeval tv;
    Ctime_val(){
	}
    Ctime_val(struct timeval a_tv){
		this->tv=a_tv;
	}
	Ctime_val(uint32_t seconds,uint32_t useconds){
		this->tv.tv_sec=seconds;
		this->tv.tv_usec=useconds;
	}
	bool operator==(const Ctime_val &t1)const{
		return (this->tv.tv_sec==t1.tv.tv_sec) && (this->tv.tv_usec ==t1.tv.tv_usec);
		
	} 
	bool operator<(const Ctime_val &t1)const{
		if (this->tv.tv_sec<t1.tv.tv_sec) {
			return true;
		}else  if (this->tv.tv_sec==t1.tv.tv_sec) {
			return this->tv.tv_usec< t1.tv.tv_usec;
		}else{
			return false;
		}
	}
	bool operator<=(const Ctime_val &t1)const{
		if (this->tv.tv_sec<t1.tv.tv_sec) {
			return true;
		}else  if (this->tv.tv_sec==t1.tv.tv_sec) {
			return this->tv.tv_usec<= t1.tv.tv_usec;
		}else{
			return false;
		}
	} 
	void  change_usec ( time_t  change_usecs ) {
#define MAX_USEC  1000000
		this->tv.tv_usec+=change_usecs;
		if (this->tv.tv_usec <0){
			int change_tv_sec=  this->tv.tv_usec/MAX_USEC -1; 
			this->tv.tv_sec+=change_tv_sec;	
			this->tv.tv_usec+=(-change_tv_sec)*MAX_USEC;
		}else{
			this->tv.tv_sec+=this->tv.tv_usec/MAX_USEC ;	
			this->tv.tv_usec=this->tv.tv_usec%MAX_USEC ;	
		}
	}
	
	
	
    ~Ctime_val(){}
};

template < typename RELOAD_MSG_T   >
class Ctimer_obj_base  ;



template < typename RELOAD_MSG_T   >
class Cfunction_list  {
	typedef   void (*timer_func_base_t )(Ctimer_obj_base<RELOAD_MSG_T> *,Cmessage *args_msg,void * buf ,int buflen);
	static const uint32_t max_function_count=1000;
	timer_func_base_t function_list[max_function_count ];
public:
    Cfunction_list(){
		
		this->init();
	}
	inline void init(){
		memset(&this->function_list,0,sizeof(this->function_list));
	}
	bool add_function(uint32_t id, timer_func_base_t event_func  ){
		if (id<this->max_function_count){
			//DEBUG_LOG("init add function id=%d",id);
			this->function_list[id]	=event_func;
			return true;
		}else{
			return false;
		}
	}
	inline timer_func_base_t get_function(uint32_t id){
		if (id<this->max_function_count){
			return this->function_list[id];
		}else{
			return NULL;
		}
	}
};


template < typename RELOAD_MSG_T   >
class Ctimer_node {
private:
	//是否处于活动状态,即可执行状态
	bool  is_active;
	int function_id;
	Ctimer_obj_base<RELOAD_MSG_T> * p_owner;

	RELOAD_MSG_T   arg;
	std::string buf;
public:

	Ctimer_node(){
		this->function_id=-1;
		
		this->is_active=false;
	}
	~Ctimer_node(){
		if (this->get_is_active() && this->p_owner){
			this->p_owner->remove_timer_node(this);
		}
	}
    void reset_cmsg_arg(){
		this->arg.reset_msg();
    }
	
	inline void init( int function_id,Ctimer_obj_base<RELOAD_MSG_T> * p_owner, Cmessage  * p_arg, char *buf,uint32_t buf_len ){
		assert(function_id!=-1);
		this->p_owner=p_owner;
		if (this->p_owner){
			//加入对象的定时器列表
			this->p_owner->add_timer_node(this);
		}
		this->arg.set(p_arg);
		this->buf.assign(buf, buf_len);
		this->function_id=function_id;
        //DEBUG_LOG("init function_id=%u time=%u",this->function_id, time(NULL));
		this->is_active=true;
	}
	
	inline void set_is_active(bool v){
		this->is_active=v;
	}
	inline bool get_is_active(){
		return this->is_active;
	}
	
	inline bool is_set_data(){
		return this->function_id!=-1;
	}
	/** 
	 * 运行
	 * 
	 * @param fun_list 用于获得回调函数指针
	 */
	void exec (Cfunction_list< RELOAD_MSG_T > &fun_list){
		if (this->get_is_active()){
			(*(fun_list.get_function(this->function_id) ))
			 (this->p_owner,this->arg.get(), (void*)this->buf.c_str(), this->buf.length());		
		};
	}
};

template < typename RELOAD_MSG_T >
class Ctimer_obj_base {
private:
	///保存对象所有的定时器指针
	std::set<Ctimer_node< RELOAD_MSG_T > *> timer_set;
public:

	typedef typename std::set<Ctimer_node< RELOAD_MSG_T > *> ::iterator  iterator;

    Ctimer_obj_base(){}
	void add_timer_node(Ctimer_node< RELOAD_MSG_T > * p_node){
		this->timer_set.insert(p_node);
	}
	
	void remove_timer_node( Ctimer_node<RELOAD_MSG_T> * p_node){
		assert(this->timer_set.count(p_node));
		this->timer_set.erase(p_node);
	}
	void remove_all_timer_node();
	~Ctimer_obj_base(){
		//DEBUG_LOG("~Ctimer_obj_base");
		this->remove_all_timer_node();
	}
};





template < typename RELOAD_MSG_T  >
class Ctimer_mgr_base {
private:
	std::map<Ctime_val, Ctimer_node<RELOAD_MSG_T> > timer_map;
	
public:
	typedef typename  std::map<Ctime_val, Ctimer_node<RELOAD_MSG_T> >::iterator  iterator;
	Cfunction_list<RELOAD_MSG_T> fun_list;

    Ctimer_mgr_base(){}
	bool add_timer( Ctime_val tv, uint32_t function_id, Ctimer_obj_base<RELOAD_MSG_T> * p_obj=NULL, Cmessage *p_arg=NULL, char * buf=NULL ,int buf_len=0 );
	/** 
	 * 增加定时器,
	 * 
	 * @param deal_time 
	 * @param function_id 
	 * @param p_obj  所属的对象,会同时将定时器的加入了它的定时器列表
	 * @param p_arg 
	 * @param buf 
	 * @param buf_len 
	 * 
	 * @return 
	 */
	inline bool add_timer( uint32_t deal_time, uint32_t function_id, Ctimer_obj_base<RELOAD_MSG_T> * p_obj, Cmessage *p_arg, char * buf=NULL ,int buf_len=0 ){
		Ctime_val tmp(deal_time,random()&0xFFFF);
		return this->add_timer(tmp, function_id,p_obj,p_arg,buf,buf_len);
	}
    inline bool add_timer( uint32_t deal_time, uint32_t function_id, Ctimer_obj_base<RELOAD_MSG_T> * p_obj=NULL, char * buf=NULL ,int buf_len=0 ){
		
		Ctime_val tmp(deal_time,random()&0xFFFF);
		return this->add_timer(tmp, function_id,p_obj,NULL,buf,buf_len);
	}

	//
    inline bool add_timer_from_now( int millisecond , uint32_t function_id, Ctimer_obj_base<RELOAD_MSG_T> * p_obj=NULL, char * buf=NULL ,int buf_len=0 ){
		Ctime_val tmp;
        gettimeofday(&(tmp.tv), 0);
		tmp.change_usec(millisecond*1000 );
		return this->add_timer(tmp, function_id,p_obj,NULL,buf,buf_len);
	}

	inline bool add_timer_from_now( int millisecond, uint32_t function_id, Ctimer_obj_base<RELOAD_MSG_T> * p_obj, Cmessage *p_arg, char * buf=NULL ,int buf_len=0 ){
		Ctime_val tmp;
        gettimeofday(&(tmp.tv), 0);
		tmp.change_usec(millisecond*1000 );
		return this->add_timer(tmp.tv, function_id,p_obj,p_arg,buf,buf_len);
	}

	
	
	/** 
	 * 处理到期事件
	 * 
	 * @param dealtime 到期时间
	 */
	void deal_timer(const Ctime_val dealtime);

    void reset_cmsg_obj() {
            iterator it; 
            for ( it= timer_map.begin();it!=  timer_map.end();++it ){
                    it->second.reset_cmsg_arg();
            }
    }

};


template < typename RELOAD_MSG_T   >
inline void 
Ctimer_obj_base<RELOAD_MSG_T>::remove_all_timer_node()
{
	iterator it;
	for (it = this->timer_set.begin(); it != this->timer_set.end(); ++it) {
		//设置定时器无效
		(*it)->set_is_active(false);
	}
	
	this->timer_set.clear();
}

template < typename RELOAD_MSG_T   >
inline bool 
Ctimer_mgr_base<RELOAD_MSG_T>::add_timer( Ctime_val tv, uint32_t function_id, Ctimer_obj_base<RELOAD_MSG_T> * p_obj, Cmessage *p_arg, char * buf ,int buf_len )
{
    //DEBUG_LOG("ADD TIMER EX func=%u now=%u",  function_id ,time(NULL ));
	Ctimer_node<RELOAD_MSG_T> *p_node;
	p_node=&(this->timer_map[tv]);
	//使用微秒级的,可偏移时间,而没有问题
	while( p_node->is_set_data()){
		//这个节点已经使用过了,偏移时间,直到找到可用节点
		tv.tv.tv_usec++;
		p_node=&(this->timer_map[tv]);
	}
	assert(this->fun_list.get_function(function_id)!=NULL);
	p_node->init(function_id, p_obj, p_arg, buf,  buf_len);
	return true;
}


template < typename RELOAD_MSG_T   >
inline void 
Ctimer_mgr_base<RELOAD_MSG_T>::deal_timer(const Ctime_val dealtime)
{
	iterator it;
	for (it=this->timer_map.begin();it!=this->timer_map.end(); ){
		if (it->first<=dealtime ){
            //DEBUG_LOG("deal timer %d %d", it->first.tv.tv_sec, dealtime.tv.tv_sec  ); 
			it->second.exec(this->fun_list);
			this->timer_map.erase(it++);	
		}else{//没有需要操作的
			break;
		}
	}
}
#endif /* _CNEW_CTIMER_H_ */
