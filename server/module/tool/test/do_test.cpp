extern "C" {
#include <libtaomee/inet/tcp.h>
}

#include "test.h"

#include "../../../proto/online/online.pb.h"
#include "../../../proto/online/player.pb.h"
// #include "../../../proto/home/home.pb.h"
#include "../../../proto/login/loginproto.pb.h"
#include "../../../proto/cache/cache.pb.h"
#include "../../../proto/share/share.pb.h"
// #include "../../../proto/scene/scene.pb.h"
#include "../../../share/cmd.h"
#include "../../../proto/isg/NetMsg.pb.h"
#include "../../../proto/isg/NetMsg2.pb.h"

#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <string>
#include <unistd.h>


using namespace std;


bool readFileToString(string file_name, string& fileData)
{
    ifstream file(file_name.c_str(),  std::ifstream::binary);
   
    if(file)
    {
        // Calculate the file's size, and allocate a buffer of that size.
        file.seekg(0, file.end);
        const int file_size = file.tellg();
        char* file_buf = new char [file_size+1];
        //make sure the end tag \0 of string.

        memset(file_buf, 0, file_size+1);
       
        // Read the entire file into the buffer.
        file.seekg(0, ios::beg);
        file.read(file_buf, file_size);


        if(file)
        {
            fileData.append(file_buf);
        }
        else
        {
            std::cout << "error: only " <<  file.gcount() << " could be read";
            fileData.append(file_buf);
            return false;
        }
        file.close();
        delete []file_buf;
    }
    else
    {
        return false;
    }

    return true;
}

int main(int argc, char** argv)
{
	// int online_fd = safe_tcp_connect("10.1.1.111", 4450, 1, 0);
	int online_fd = safe_tcp_connect("192.168.2.232", 4445, 1, 0);
// 	for (uint32_t i=5201; i<5301; i++) {
// 		int login_fd = safe_tcp_connect("129.211.109.190", i, 1, 0);
// 		std::cout << i << " login fd " << login_fd << std::endl;
// 	}
	// int online_fd = safe_tcp_connect("10.1.1.111", 4460, 1, 0);
	
	// int battle_fd = safe_tcp_connect("192.168.1.235", 4300, 1, 0);
	
	// int switch_fd = safe_tcp_connect("192.168.1.232", 5555, 1, 0);
//	if (argc < 4) {
//		std::cout << "./do_test 192.168.2.232 5555 9527" << std::endl;
//		return 0;
//	}
//	int switch_fd = safe_tcp_connect(argv[1], atoi(argv[2]), 1, 0);
	// int switch_fd = safe_tcp_connect("192.168.1.232", 9001, 1, 0);

#if 0
	shareproto::SetAllUserMails mails_;
	{
//		mails_.set_type(1);
		shareproto::AllUserMail* mail = mails_.add_mail();
		mail->set_id(130001);
		mail->set_content("[u][url=https://jinshuju.net/f/tg8gDd][b][00ff00]欢迎参与墨三国精英测试，点击本文字参与问卷调查，完成后可获得高值元宝、道具礼包哟！[ff0000][/b][/url][/u]");
		mail->set_title("Title");
		mail->set_validtime(time(NULL) + 20*365*24*60*60);
		shareproto::AwardItems* items = mail->mutable_items();
		shareproto::AwardItem* item1 = items->add_item();
		item1->set_type(10);
		item1->set_id(0);
		item1->set_num(88);

		shareproto::AwardItem* item2 = items->add_item();
		item2->set_type(9);
		item2->set_id(0);
		item2->set_num(8888);

		shareproto::AwardItem* item3 = items->add_item();
		item3->set_type(1);
		item3->set_id(5551);
		item3->set_num(3);

		shareproto::AwardItem* item4 = items->add_item();
		item4->set_type(1);
		item4->set_id(5552);
		item4->set_num(3);

		shareproto::AwardItem* item5 = items->add_item();
		item5->set_type(1);
		item5->set_id(101);
		item5->set_num(6);
	}
	{
		shareproto::AllUserMail* mail = mails_.add_mail();
		mail->set_id(120002);
		mail->set_content("【提示邮件】参与国战可获得请酒令，武将邀请函，酒，元宝，贡献，声望等丰厚奖励.第一名额外获得讨伐令，有资格向其它城池发起国战！更过咨询请添加官方QQ群: 556428402.");
		mail->set_title("国战20:00开启");
		mail->set_validtime(time(NULL) + 20*365*24*60*60);
		shareproto::AwardItems* items = mail->mutable_items();
		shareproto::AwardItem* item1 = items->add_item();
		item1->set_type(1);
		item1->set_id(19);
		item1->set_num(1);

		shareproto::AwardItem* item2 = items->add_item();
		item2->set_type(1);
		item2->set_id(22);
		item2->set_num(1);
	}
	{
		shareproto::AllUserMail* mail = mails_.add_mail();
		mail->set_id(120003);
		mail->set_content("拥有讨伐令的玩家，可开启国战，国战只能在相邻的敌对城池才能开启，需满足讨伐的兵力和粮草要求。为保证测试期间玩法体验，若势力在凌晨仍旧未开启国战，官方将开启次日国战.");
		mail->set_title("国战讨伐令使用");
		mail->set_validtime(time(NULL) + 20*365*24*60*60);
		shareproto::AwardItems* items = mail->mutable_items();
		shareproto::AwardItem* item1 = items->add_item();
		item1->set_type(1);
		item1->set_id(22);
		item1->set_num(1);
	}
//	{
//		shareproto::AllUserMail* mail = mails_.add_mail();
//		mail->set_id(120004);
//		mail->set_content("分行李，回高老庄~");
//		mail->set_title("大师兄，师傅被妖怪抓走了~");
//		mail->set_validtime(time(NULL) + 20*365*24*60*60);
//		shareproto::AwardItems* items = mail->mutable_items();
//		shareproto::AwardItem* item1 = items->add_item();
//		item1->set_type(10);
//		item1->set_id(0);
//		item1->set_num(88);
//
//		shareproto::AwardItem* item2 = items->add_item();
//		item2->set_type(9);
//		item2->set_id(0);
//		item2->set_num(8888);
//
//		shareproto::AwardItem* item3 = items->add_item();
//		item3->set_type(1);
//		item3->set_id(5551);
//		item3->set_num(3);
//
//		shareproto::AwardItem* item4 = items->add_item();
//		item4->set_type(1);
//		item4->set_id(5552);
//		item4->set_num(3);
//
//		shareproto::AwardItem* item5 = items->add_item();
//		item5->set_type(1);
//		item5->set_id(101);
//		item5->set_num(6);
//	}


	EXPECT(test(switch_fd, db_cmd_cs_set_all_user_mail, db_cmd_cs_set_all_user_mail,
				0, &mails_, &mails_), 0);

#endif

#if 0
	shareproto::cs_gm_ban cs_gm_ban_;
	cs_gm_ban_.set_ban_type(5);
	cs_gm_ban_.set_ban_time(5*60);
	cs_gm_ban_.set_userid(100064);
	EXPECT(test(switch_fd, ban_user_cmd, ban_user_cmd,
				100061, &cs_gm_ban_, &cs_gm_ban_), 0);
#endif

#if 0
	if (atoi(argv[3]) != 9527) {
		std::cout << "no no no! stupid guy!!!" << std::endl;
		return 0;
	}
	shareproto::cs_gm_ban_all_user cs_gm_ban_all_user_;
	cs_gm_ban_all_user_.set_thekey(atoi(argv[3]));
	EXPECT(test(switch_fd, gm_ban_all_user_cmd, gm_ban_all_user_cmd,
				100061, &cs_gm_ban_all_user_, &cs_gm_ban_all_user_), 0);
#endif

#if 0
	// 请求加入国战
	NetMsg::ReqEnterWorldWar ReqEnterWorldWar_;
	NetMsg::EnterWorldWarAck EnterWorldWarAck_;
	ReqEnterWorldWar_.set_worldwarid(1);
	EXPECT(test(battle_fd, (uint32_t)NetMsg::MessageType::ReqEnterWorldWar, 
				(uint32_t)NetMsg::MessageType::EnterWorldWarAck,
				12345678, &ReqEnterWorldWar_, &EnterWorldWarAck_), 0);
#endif 

#if 0
	// int login_fd = safe_tcp_connect("192.168.1.232", 14002, 1, 0);

	// 账号校验
	loginproto::cs_session_login cs_session_login_;
	loginproto::sc_session_login sc_session_login_;
	cs_session_login_.set_source_number("1505006");
	cs_session_login_.set_session("C0TUAD/FnqoLireSzOdPsA8KwSwh3ZXRGYCPXJKzU57S3VKexygg4EzLd6Aqg+im50gCzWQg5Y//QoZc9kieQUULPdpEPhNvbD9SoSm0sFnV62YN7Z+6FhHgzNyi2Rh5zjypD9leiy0HIp9rIo19h1pZh9V4yR8ntllg9dHnyxu5gNzValPxvVUqxEjMWyLntUSI+R+E066b64I1DZHsDyO1rQ1IN5l9L2XGtUcw1taYhLX0BLl03tGCqTD+SlaB3MK+w5WOAj84gPNyxKlIDvBw1Ua/YdjCV8gjptFfhjovfjY8pkCqy+0gichbaDwmynF3QdiePjRv3ZIRevNPmg==");
    cs_session_login_.set_source(5);
	cs_session_login_.set_platform(501);
	cs_session_login_.set_client_ip("127.0.0.0");
	// cs_session_login_.set_session("2c412e9ecd900ebaacf9f3af85059fff");
	EXPECT(test(login_fd, NetMsg::MessageType::ReqThirdPartyLogin, NetMsg::MessageType::ReqThirdPartyLogin, 1234567895, &cs_session_login_, &sc_session_login_), 0);

//		// 角色创建
//    // if (sc_session_login_.users_size() == 0) {
//            loginproto::cs_create_role cs_create_role_;
//            loginproto::sc_create_role sc_create_role_;
//            cs_create_role_.set_sex(1);
//            cs_create_role_.set_nick("设备测试");
//            cs_create_role_.set_server_id(1);
//            cs_create_role_.set_device("我是设备号");
//            EXPECT(
//                test(
//                    login_fd, 
//                    NetMsg::MessageType::ReqCreateUser, 1234567895, &cs_create_role_, &sc_create_role_), 0); 
//
//    // }
//	
//	// 获取服务器 ip、port
//			loginproto::cs_get_online_info cs_get_online_info_;
//			loginproto::sc_get_online_info sc_get_online_info_;
//			cs_get_online_info_.set_server_id(1);
//	EXPECT(test(login_fd, NetMsg::MessageType::ReqServerList, 1234567895, &cs_get_online_info_, &sc_get_online_info_), 0);
#endif 

#if 0

	// get server version
	onlineproto::cs_get_server_version cs_get_server_version_;
	onlineproto::sc_get_server_version sc_get_server_version_;
	EXPECT(test(online_fd, cli_get_server_version, 0, &cs_get_server_version_, &sc_get_server_version_), 0);
#endif

#if 1
	// enter server
	onlineproto::cs_enter_srv cs_enter_srv_;
	onlineproto::sc_enter_srv sc_enter_srv_;
	// uint32_t userid = 115874;
	uint32_t userid = 124880;
	cs_enter_srv_.Clear();
	cs_enter_srv_.set_userid(userid);
	// cs_enter_srv_.set_source_number("15618787123");
	cs_enter_srv_.set_source_number("69");
	cs_enter_srv_.set_server_id(7);
	cs_enter_srv_.set_session("ZsndFfnabd2slgycMdTY0Y2RnYmIwcmRxbG1lMWJmMmMO0O0O");
	cs_enter_srv_.set_source(5);
	cs_enter_srv_.set_platform_id(551);

	EXPECT(test(online_fd, NetMsg::MessageType::ReqEnterGame,
				NetMsg::MessageType::ReqEnterGame,
				userid, 
			&cs_enter_srv_, &sc_enter_srv_), 0);
#endif

#if 1
	NetMsg::ReqForceResourceDetailInfo req;
	for (int i=0; i<2000; i++) {
		req.add_uid(i);
	}
	NetMsg::ForceResourceDetailInfosAck ack;
	EXPECT(test(online_fd, NetMsg::MessageType::ReqForceResourceDetailInfo,
				NetMsg::MessageType::ReqForceResourceDetailInfo,
				userid, 
			&req, &ack), 0);
#endif

#if 0
	for (int i=0; i<10000; i++) {
		int online_fd = safe_tcp_connect("192.168.2.232", 4445, 1, 0);
//	for (int i=0; i<10000; i++) {
//		int online_fd = safe_tcp_connect("192.168.2.232", 4445, 1, 0);
		// enter server
		onlineproto::cs_enter_srv cs_enter_srv_;
		onlineproto::sc_enter_srv sc_enter_srv_;
		// uint32_t userid = 115874;
		uint32_t userid = 125214;
		cs_enter_srv_.Clear();
		cs_enter_srv_.set_userid(userid);
		// cs_enter_srv_.set_source_number("15618787123");
		cs_enter_srv_.set_source_number("55");
		cs_enter_srv_.set_server_id(7);
		cs_enter_srv_.set_session("aszdUf1abdDsggyccd3FjZ3JwaW40bmJyMjNqcmVpMXQO0O0O");
		cs_enter_srv_.set_source(5);
		cs_enter_srv_.set_platform_id(551);

		EXPECT(test(online_fd, NetMsg::MessageType::ReqEnterGame,
					NetMsg::MessageType::ReqEnterGame,
					userid, 
				&cs_enter_srv_, &sc_enter_srv_), 0);
//		close(online_fd);
//		sleep(3);
//	}

//	{
//		// 点将
//		for (int j=0; j<10000; j++) {
//			sleep(10);
//			for (int i=0; i<10; i++) {
//				NetMsg::ReqRaffleHero req;
//				NetMsg::RaffleHeroAck ack;
//				req.set_id(1);
//				req.set_num(10);
//				EXPECT(test(online_fd, NetMsg::MessageType::ReqRaffleHero,
//						NetMsg::MessageType::ReqRaffleHero,
//						userid, 
//					&req, &ack), 0);
//			}
//		}
//	}
	
#endif

#if 0
	NetMsg2::CSGetGuildActivityRank req;
	NetMsg2::SCGetGuildActivityRank ack;
	EXPECT(test(online_fd, NetMsg2::MessageType::CSGetGuildActivityReq,
					NetMsg2::MessageType::CSGetGuildActivityReq,
					userid, 
				&req, &ack), 0);
#endif

#if 0
	NetMsg::CSChangeNickOrSex req;
	NetMsg::SCChangeNickOrSex ack;

	req.set_firstname("健力");
	req.set_lastname("宝");
	req.set_secondname("可");
	req.set_sex(0); // 0:男；1：女
	req.set_icon(1); // 1:男头像；2：女头像

	EXPECT(test(online_fd, NetMsg::MessageType::CSChangeNickOrSex,
			NetMsg::MessageType::CSChangeNickOrSex,
			userid, 
		&req, &ack), 0);

#endif

//	NetMsg::CSChangeForce req;
//	NetMsg::SCChangeForce ack;
//	req.set_force(3);
//	EXPECT(test(online_fd, NetMsg::MessageType::CSChangeForce,
//			NetMsg::MessageType::CSChangeForce,
//			userid, 
//		&req, &ack), 0);
//

#if 0
	shareproto::CSGetAllLegionInvasion req;
	shareproto::SCGetAllLegionInvasion ack;
	EXPECT(test(online_fd, NetMsg::MessageType::CSGetAllLegionInvasion,
			NetMsg::MessageType::CSGetAllLegionInvasion,
			userid, 
		&req, &ack), 0);

	shareproto::CSGetLegionInvasion _req;
	shareproto::SCGetLegionInvasion _ack;
	_req.set_point_id(6576881762507423747);
	EXPECT(test(online_fd, NetMsg::MessageType::CSGetLegionInvasion,
			NetMsg::MessageType::CSGetLegionInvasion,
			userid, 
		&_req, &_ack), 0);


//	NetMsg::ReqBanquetHero ReqBanquetHero_;
//	ReqBanquetHero_.set_uid(6547833747633405957);
//	NetMsg::BanquetHeroAck BanquetHeroAck_;
//	EXPECT(test(online_fd, NetMsg::MessageType::ReqBanquetHero,
//				NetMsg::MessageType::ReqBanquetHero,
//				userid, 
//            &ReqBanquetHero_, &BanquetHeroAck_), 0);

//	NetMsg::CSGetForceActive cs_get_force_active_;
//	NetMsg::SCGetForceActive sc_get_force_active_;
//	EXPECT(test(online_fd, NetMsg::MessageType::CSGetForceActive,
//				NetMsg::MessageType::CSGetForceActive,
//				userid,
//				&cs_get_force_active_, &sc_get_force_active_), 0);

//	// get world war log
//	cacheproto::CSGetWorldWarLog req;
//	cacheproto::SCGetWorldWarLog ack;
//	req.set_start(1522252800);
//	req.set_end(1522339200);
//	EXPECT(test(online_fd, NetMsg::MessageType::CSGetWorldWarLog,
//				NetMsg::MessageType::CSGetWorldWarLog,
//				userid, 
//            &req, &ack), 0);
//
//	cacheproto::CSGetWorldWarDetailLog detail_req;
//	cacheproto::SCGetWorldWarDetailLog detail_ack;
//	detail_req.set_worldwarid(1522390770);
//	EXPECT(test(online_fd, NetMsg::MessageType::CSGetWorldWarDetailLog,
//				NetMsg::MessageType::CSGetWorldWarDetailLog,
//				userid, 
//            &detail_req, &detail_ack), 0);

//	NetMsg::ReqTeamArrivedTar team_arrive;
//	NetMsg::TeamArrivedTarAck team_arrive_ack; 
//	shareproto::RunPathAck* run_path = team_arrive.mutable_path();
//	// run_path->set_state(shareproto::RunState::ArrivedTarget);
//	run_path->set_state(shareproto::ArrivedTarget);
//	shareproto::PathInfo* path = run_path->mutable_path();
//	path->set_targetid(6520381587987955717);
//	path->set_runtarget(shareproto::RunToResourcesSoldier);
//
//	EXPECT(test(online_fd, NetMsg::MessageType::ReqTeamArrivedTar,
//				NetMsg::MessageType::ReqTeamArrivedTar,
//				userid, 
//            &team_arrive, &team_arrive_ack), 0);

	// NetMsg::CSGetArenaOpponentList CSGetArenaOpponentList_;
	// NetMsg::SCGetArenaOpponentListAck SCGetArenaOpponentListAck_;
	// EXPECT(test(online_fd, NetMsg::MessageType::CSGetArenaOpponentList,
	// 			NetMsg::MessageType::CSGetArenaOpponentList,
	// 			userid, 
	// 			&CSGetArenaOpponentList_, &SCGetArenaOpponentListAck_), 0);

//	NetMsg::CSGetArenaRecord CSGetArenaRecord_;
//	NetMsg::SCGetArenaRecordAck SCGetArenaRecordAck_;
//	EXPECT(test(online_fd, NetMsg::MessageType::CSGetArenaRecord,
//				NetMsg::MessageType::CSGetArenaRecord,
//				userid,
//				&CSGetArenaRecord_, &SCGetArenaRecordAck_), 0);

	// 请求添加国战
	// NetMsg::ReqAddWorldWarApplication ReqAddWorldWarApplication_;
	// NetMsg::AddWorldWarApplicationAck AddWorldWarApplicationAck_;
	// ReqAddWorldWarApplication_.set_force1(3);
	// ReqAddWorldWarApplication_.set_force2(9);
	// ReqAddWorldWarApplication_.set_city1(120);
	// ReqAddWorldWarApplication_.set_city2(147);
	// ReqAddWorldWarApplication_.set_type(1);
	// ReqAddWorldWarApplication_.set_path(27);
	// ReqAddWorldWarApplication_.set_percent(0.5);
	// EXPECT(test(online_fd, NetMsg::MessageType::ReqAddWorldWarApplication,
	// 			NetMsg::MessageType::AddWorldWarApplicationAck,
	// 			userid,
	// 			&ReqAddWorldWarApplication_, &AddWorldWarApplicationAck_), 0);

	// 请求移除国战申请
	// NetMsg::ReqRemoveWorldWarApplication ReqRemoveWorldWarApplication_;
	// NetMsg::RemoveWorldWarApplicationAck RemoveWorldWarApplicationAck_;
	// ReqRemoveWorldWarApplication_.set_force(3);
	// EXPECT(test(online_fd, NetMsg::MessageType::ReqRemoveWorldWarApplication,
	// 			NetMsg::MessageType::RemoveWorldWarApplicationAck,
	// 			userid, 
	// 			&ReqRemoveWorldWarApplication_, &RemoveWorldWarApplicationAck_), 0);
	
	// // 请求所有国战申请列表
	// NetMsg::WorldWarApplicationAck WorldWarApplicationAck_;
	// EXPECT(test(online_fd, NetMsg::MessageType::ReqWorldWarApplication,
	// 			NetMsg::MessageType::WorldWarApplicationAck,
	// 			userid, 
	// 			NULL, &WorldWarApplicationAck_), 0);

	// // 请求添加国战（测试用，直接开始国战）
	// NetMsg::ReqAddWorldWarPrepare ReqAddWorldWarPrepare_;
	// NetMsg::AddWorldWarPrepareAck AddWorldWarPrepareAck_;
	// ReqAddWorldWarPrepare_.set_force1(3);
	// ReqAddWorldWarPrepare_.set_force2(9);
	// ReqAddWorldWarPrepare_.set_city1(120);
	// ReqAddWorldWarPrepare_.set_city2(147);
	// ReqAddWorldWarPrepare_.set_type(1);
	// ReqAddWorldWarPrepare_.set_path(27);
	// ReqAddWorldWarPrepare_.set_percent(0.5);
	// ReqAddWorldWarPrepare_.set_time(10);
	// ReqAddWorldWarPrepare_.set_length(30);
	// EXPECT(test(online_fd, NetMsg::MessageType::ReqAddWorldWarPrepare,
	// 			NetMsg::MessageType::AddWorldWarPrepareAck,
	// 			userid, 
	// 			&ReqAddWorldWarPrepare_, &AddWorldWarPrepareAck_), 0);
#endif

	sleep(5000);
}
