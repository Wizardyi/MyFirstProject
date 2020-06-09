使用说明(具体相关定义请参考头文件http_client_thread.h):
1、程序输入: 
    A、struct login_auth_input结构体变量: 传入http post需要的相关信息
    B、login_auth_callback_func回调函数: 处理post请求返回的数据
    C、timeout: 设置http请求超时时长(单位: 秒), 0表示不超时

2、程序输出: 
    A、struct login_auth_output结构体变量: 作为调函数login_auth_callback_func参数传入

3、使用步骤(可参考test.cpp文件):
    A、实例化c_http_client_thread对象
    B、调用init函数传入相应参数(程序输入)即可

[备注]
1、依赖的库: libcurl、libjsoncpp、libtaomee++
2、libcurl库安装: sudo apt-get install curl
3、libjsoncpp库安装:
    A、sudo cp ./include/jsoncpp /usr/local/include/ -r
    B、sudo cp ./lib/* /usr/local/lib/
    C、sudo ldconfig
4、jsoncpp-src-0.5.0源码安装的时候如果需要用-fPIC编译参数，
需要修改文件SConstruct,将CCFLAGS变量增加-fPIC选项(位置大概在109行)

[需要写入配置文件的参数]: 
外网auth_url: http://maccount-sdk.61.com/account_service.php
auth_sign: 21ee5e1d8bf781576754be709301ffe9
sign_id: 101
proto_id: 1016


