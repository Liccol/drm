#include <iostream>
#include <memory>
#include "http_server.h"

using namespace std;

struct reqForm
{
	string type;
	string version;
	string deviceID;
	string nonce;
	string requestTime;
	string contentIDs[100];
	string supportedAlgorithms[100];
	string extensions[100];
	string certificateChain[100];
	string signature;
}licenseReq;

struct rspForm
{
	string type;
	string version;
	string status;
	string selectedAlgorithm;
	string responseTime;
	string deviceID;
	string drmServerID;
	string nonce;
	string protectedLicenses[100];
	string certificateChain[100];
	string ocspResponse;
	string signature;
}licenseRsp;


bool Fun1Handler(std::string body, std::string query_string, mg_connection *c, OnRspCallback reply_callback)
{
    std::cout << "FUNC: " << __FUNCTION__ << "  "
              << "body: " << body << std::endl;
    std::cout << "FUNC: " << __FUNCTION__ << "  "
              << "query_string: " << query_string << std::endl;

    reply_callback(c, "200 OK", "success");

	return true;
}

bool Fun2Handler(std::string body, std::string query_string, mg_connection *c, OnRspCallback reply_callback)
{
    std::cout << "FUNC: " << __FUNCTION__ << "  "
              << "body: " << body << std::endl;
    std::cout << "FUNC: " << __FUNCTION__ << "  "
              << "query_string: " << query_string << std::endl;

    char n1[100], n2[100];
    char res[100];
    double result;
	
    if(!body.empty()){
        struct mg_str http_body;
        http_body.p   = body.c_str();
        http_body.len = body.length();
        mg_get_http_var(&http_body, "n1", n1, sizeof(n1));
        mg_get_http_var(&http_body, "n2", n2, sizeof(n2));

    }
    else if(!query_string.empty()){
        struct mg_str http_body;
        http_body.p   = query_string.c_str();
        http_body.len = query_string.length();
        mg_get_http_var(&http_body, "n1", n1, sizeof(n1));
        mg_get_http_var(&http_body, "n2", n2, sizeof(n2));
    }

    /* Compute the result and send it back as a JSON object */
    result = strtod(n1, NULL) + strtod(n2, NULL);
    sprintf_s(res, "%0.5f", result);
    reply_callback(c, "200 OK", res);

    return true;
}

// 添加url动态解析，把请求信息解析到该函数中
/*struct reqForm
	{
		string type;
		string version;
		string deviceID;
		string nonce;
		string requestTime;
		string contentIDs[100];
		string supportedAlgorithms[100];
		string extensions[100];
		string certificateChain[100];
		string signature;
	}licenseReq;*/
bool Fun3Handler(std::string body, std::string query_string, mg_connection *c, OnRspCallback reply_callback)
{
	// 使用POST的话, body里边会有东西么？
	std::cout << "get license request!" << endl;
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
		licenseReq.type = tmp;
		mg_get_http_var(&http_body, "version", tmp, sizeof(tmp));
		licenseReq.version = tmp;
		mg_get_http_var(&http_body, "deviceID", tmp, sizeof(tmp));
		licenseReq.deviceID = tmp;
		mg_get_http_var(&http_body, "nonce", tmp, sizeof(tmp));
		licenseReq.nonce = tmp;
		mg_get_http_var(&http_body, "requestTime", tmp, sizeof(tmp));
		licenseReq.requestTime = tmp;
		mg_get_http_var(&http_body, "signature", tmp, sizeof(tmp));
		licenseReq.signature = tmp;
		// 字符串数组的解析方式还需要更改
		mg_get_http_var(&http_body, "contentIDs", tmp, sizeof(tmp));
		licenseReq.contentIDs[0] = tmp;
		mg_get_http_var(&http_body, "supportedAlgorithms", tmp, sizeof(tmp));
		licenseReq.supportedAlgorithms[0] = tmp;
		mg_get_http_var(&http_body, "extensions", tmp, sizeof(tmp));
		licenseReq.extensions[0] = tmp;
		mg_get_http_var(&http_body, "certificateChain", tmp, sizeof(tmp));
		licenseReq.certificateChain[0] = tmp;
		std::cout << "version is " << licenseReq.version << endl;
	}
	/* Compute the result and send it back as a JSON object */
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
        case 1:{
            port = "8080"; //默认使用80端口
            break;
        }
        case 2:{
            port = argv[1];
            break;
        }
        case 3:{
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
    http_server->AddHandler("/api/fun1", Fun1Handler);
    http_server->AddHandler("/api/sum",  Fun2Handler);
    http_server->AddHandler("/api/test",  Fun3Handler);
	http_server->Start();

	return 0;
}
