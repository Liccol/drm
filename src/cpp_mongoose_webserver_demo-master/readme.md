1. ���� [CppHttpDemo](https://github.com/tashaxing/CppHttpDemo) ��ĿС���޸ģ�������ǻ���[mongoose](https://github.com/cesanta/mongoose)��
	- ������uri���涯̬�������ݵ��жϣ�
	- �����˽����ύ/�ϴ���server�˵��ļ��Ĺ��ܣ�������`mongoose`�е�`MG_ENABLE_HTTP_STREAMING_MULTIPART`�꣬�ļ�����λ�ø���`http_server.cpp`�к���`upload_fname()`��ע�������޸ģ�
	- �����˷���ָ����Ŀ¼����Ŀ¼��ָ����������7�㣩�£�����html��js��css���ļ��Ĺ��ܣ�
	- �޸���`SendRsp()`������ʹ���ܹ����ݴ���Ĳ������ظ���ͬ��״̬�롣
	- ȥ����`std::to_string()`,��Ϊ�ϵͰ汾�ı�������֧�ָú������������ں�˼ƽ̨��ʹ�õ�`arm-hisiv300-linux-g++`...
2. ��������ȫ����,ʹ��c/c++��д��webserver demo��
3. ֧��get��post��֧�ֶ�̬����(http://uri?qurey_string)��֧��POST�ϴ��ļ����ύ����ʽ����Ĭ�Ͻ��յ����ļ�ת����ͬ��Ŀ¼�£�
4. �ɷ������չ�Զ���ָ�
5. ������`mongoose`���õĿ�ƽ̨�ԣ�����Ҫ�޸Ĵ��룬��֧�ֿ�ƽ̨��Ŀǰ��**win10_x64,CentOS7_x64,arm(��˼ϵ��оƬhi35xx)** �о��õ���֤��
6. ������ʹ��`Windows`ƽ̨��QT Creator��ΪIDE��ʹ��`Windows`ƽ̨��Creator����ֱ�ӱ������У�
7. **���У�**
�����Ѿ���win10ƽ̨����õ�`webserver.exe`��
- ����ʹ��`run.bat`�ű����У�����ǰ��Ҫ�޸�`run.bat`�ж�Ӧ��`web html`�ļ��е�·����
`run.bat`��
> ```
> webserver 8080 ../../web
> ```
- Ҳ����ֱ��ʹ��`cmd`���и�exe����
> webserver.exe 8080 ../../web

- **ע����Ȼ����������`Windows`ϵͳ�д���������ģ��������5�����������뱾���ǿ�ƽ̨�ġ���Ϊ�˷����Լ�֮��git����ֱ���ϴ����̡���ҿ������Լ���ϵͳʹ�ø���Ŀ��Դ����б��볢�ԣ����������һ�����ۡ�**����
8. **Ŀ¼�ṹ��**
```
����web
    ����index.html (������)
����mongoose
    ����common
       ����mongoose.h
       ����mongoose.cpp
    ����http_server.h
    ����http_server.cpp
    ����main.cpp (������)
����build-mongoose-Desktop_Qt_5_8_0_MinGW_Static_32bit-Release
	����release
    		����webserver.exe
       		����run.bat
```
��ȥ�����õ�main.cpp��index.html������ľ��Ǹ�WebServer�ĺ��Ĵ��롣��չʱ��ֻ��Ҫ�޸�main.cpp�����ݼ��ɡ�

��by zhsun��