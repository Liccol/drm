#include <iostream>
#include <memory>
#include "http_server.h"

using namespace std;

struct cekStruct {
	string cekID;
	string encCEK;
	string startTime;
	string endTime;
};

struct contentInfomation
{
	string contentID;
	struct cekStruct ceks[100];
	string contentRules;
};

struct reqForm
{
	string type;
	string version;
	string kmsID;
	string nonce;
	string selectedAlgorithm;
	string selectedAlgorithm;
	string contentInfosTmp;
	struct contentInfomation contentInfos[100];
	string extensions[100];
	string certificateChain[100];
	string signature;
}keySyncReq;

struct rspForm
{
	string type;
	string version;
	string keyGateWayID;
	string selectedAlgorithm;
	string nonce;
	string status;
	string selectedAlgorithm;
	string certificateChain[100];
	string signature;
}keySyncRsp;

// 添加url动态解析，把请求信息解析到该函数中

bool KeySync(std::string body, std::string query_string, mg_connection *c, OnRspCallback reply_callback)
{
	// 使用POST的话, body里边会有东西么？  ---->有的,使用body解析
	std::cout << "get key sync request!" << endl;
	std::cout << "FUNC: " << __FUNCTION__ << "  "
		<< "body: " << body << std::endl;
	std::cout << "FUNC: " << __FUNCTION__ << "  "
		<< "query_string: " << query_string << std::endl;

	char res[100];
	char tmp[100] = "";
	double result;
	//get content
	if (!body.empty()) {
		struct mg_str http_body;
		http_body.p = body.c_str();
		http_body.len = body.length();
	}
	else if (!query_string.empty()) {
		struct mg_str http_body;
		http_body.p = query_string.c_str();
		http_body.len = query_string.length();
		mg_get_http_var(&http_body, "type", tmp, sizeof(tmp));
		if (tmp != "keySyncRequest")
		{
			cout << "key sync request TYPE error!" << endl;
			return false;
		}
		else
		{
			keySyncReq.type = tmp;
		}
		mg_get_http_var(&http_body, "version", tmp, sizeof(tmp));
		if (tmp != "1.0")
		{
			cout << "key sync request VERSION error!" << endl;
			return false;
		}
		else
		{
			keySyncReq.version = tmp;
		}
		// 解析所有内容,生成响应(什么格式?)--->string转struct的方式要看下
		mg_get_http_var(&http_body, "kmsID", tmp, sizeof(tmp));
		keySyncReq.kmsID = tmp;
		mg_get_http_var(&http_body, "nonce", tmp, sizeof(tmp));
		keySyncReq.nonce = tmp;
		mg_get_http_var(&http_body, "selectedAlgorithm", tmp, sizeof(tmp));
		keySyncReq.selectedAlgorithm = tmp;
		mg_get_http_var(&http_body, "contentInfos", tmp, sizeof(tmp));
		keySyncReq.contentInfosTmp = tmp;
		// contentInfosTmp内容转为结构体contentInfos
		mg_get_http_var(&http_body, "certificateChain", tmp, sizeof(tmp));
		keySyncReq.certificateChain[0] = tmp;
		mg_get_http_var(&http_body, "signature", tmp, sizeof(tmp));
		keySyncReq.signature = tmp;
		std::cout << "version is " << keySyncReq.version << endl;
	}
	/* Compute the result and send it back as a JSON object */
	// result修改为JSON格式
	result = 200;
	sprintf_s(res, "%0.5f", result);

	reply_callback(c, "200 OK", res);

	return true;
}

int main(int argc, char *argv[])
{
	printf("\tusage notes: %s [port] [webpath]\n"
		"\t - [port]:\tYou can modify the port that webserver uses, through appoint [port], default 80.\n"
		"\t - [webpath]:\tYou can modify the web/html path, through appoint [webpath], default '../web'.\n", argv[0]);

	std::string port;
	switch (argc) {
	case 1: {
		port = "8080"; //默认使用80端口
		break;
	}
	case 2: {
		port = argv[1];
		break;
	}
	case 3: {
		port = argv[1];
		HttpServer::s_web_dir = argv[2];
	}
	default:
		break;
	}

	// 启动http server
	auto http_server = std::shared_ptr<HttpServer>(new HttpServer);
	http_server->Init(port);
	// add handler
	http_server->AddHandler("/api/keysync", KeySync);
	// start
	http_server->Start();

	return 0;
}
