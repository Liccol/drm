// test4HTTP.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "HttpRequest.h"
#include <iostream>
#include <Windows.h>
using namespace std;
int main(int argc, char argv[])
{
	HttpRequest httpReq("127.0.0.1", 8080);


	std:: string res = httpReq.HttpPost("/keySync/", HttpRequest::genJsonString("test", 100));
	std::cout << res << std::endl;
	cin.get();
	return 0;
}