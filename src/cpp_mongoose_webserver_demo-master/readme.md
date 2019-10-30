1. 基于 [CppHttpDemo](https://github.com/tashaxing/CppHttpDemo) 项目小做修改，其根本是基于[mongoose](https://github.com/cesanta/mongoose)；
	- 增加了uri后面动态请求内容的判断；
	- 增加了接收提交/上传到server端的文件的功能，即开启`mongoose`中的`MG_ENABLE_HTTP_STREAMING_MULTIPART`宏，文件保存位置根据`http_server.cpp`中函数`upload_fname()`的注释自行修改；
	- 增加了返回指定根目录（根目录的指定方法见第7点）下，本地html、js、css等文件的功能；
	- 修改了`SendRsp()`函数，使其能够根据传入的参数，回复不同的状态码。
	- 去掉了`std::to_string()`,因为较低版本的编译器不支持该函数，比如我在海思平台上使用的`arm-hisiv300-linux-g++`...
2. 经测试完全可用,使用c/c++编写的webserver demo；
3. 支持get，post。支持动态请求(http://uri?qurey_string)，支持POST上传文件（提交表单形式），默认将收到的文件转存在同级目录下；
4. 可方便地扩展自定义指令；
5. 得益于`mongoose`良好的跨平台性，不需要修改代码，就支持跨平台，目前在**win10_x64,CentOS7_x64,arm(海思系列芯片hi35xx)** 中均得到验证。
6. 本工程使用`Windows`平台的QT Creator作为IDE，使用`Windows`平台的Creator可以直接编译运行；
7. **运行：**
内有已经在win10平台编译好的`webserver.exe`，
- 可以使用`run.bat`脚本运行，运行前需要修改`run.bat`中对应的`web html`文件夹的路径，
`run.bat`：
> ```
> webserver 8080 ../../web
> ```
- 也可以直接使用`cmd`运行该exe程序：
> webserver.exe 8080 ../../web

- **注：虽然本工程是在`Windows`系统中创建并编译的，但是如第5点所述，代码本身是跨平台的。我为了方便自己之后git，就直接上传工程。大家可以在自己的系统使用该项目的源码就行编译尝试，有问题可以一起讨论。**：）
8. **目录结构：**
```
└─web
    └─index.html (测试用)
└─mongoose
    └─common
       ├─mongoose.h
       └─mongoose.cpp
    ├─http_server.h
    ├─http_server.cpp
    └─main.cpp (测试用)
└─build-mongoose-Desktop_Qt_5_8_0_MinGW_Static_32bit-Release
	└─release
    		├─webserver.exe
       		└─run.bat
```
除去测试用的main.cpp和index.html，其余的就是该WebServer的核心代码。扩展时，只需要修改main.cpp的内容即可。

（by zhsun）