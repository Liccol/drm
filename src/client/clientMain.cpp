// test4HTTP.cpp : 定义控制台应用程序的入口点。
//

#include "HttpRequest.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include "nlohmann/json.hpp"
using namespace std;
using nlohmann::json;
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
	string nonce;
	string status;
	string selectedAlgorithm;
	string certificateChain[100];
	string signature;
}keySyncRsp;

namespace licenseReq {
	struct reqForm
	{
		string type = "licenseRequest";
		string version = "2.0";
		string deviceID = "testdeviceID";
		string nonce = "asdfghjklqwertyuiop";
		string requestTime = "2132412";
		string contentIDs[100] = { "213" };
		string supportedAlgorithms[100] = { "KMSProfile1" };
		string extensions[100] = {};
		string certificateChain[100] = {"21312ewas12"};
		string signature = "signature";
	};
	void to_json(json& j, const reqForm& req) {
		j = json{ {"type", req.type}, {"version", req.version}, {"deviceID", req.deviceID},
				{"nonce", req.nonce}, {"requestTime", req.requestTime}, {"contentIDs", req.contentIDs[0]},
				{"supportedAlgorithms", req.supportedAlgorithms[0]}, {"extensions", req.extensions[0]}, {"certificateChain", req.certificateChain[0]},
				{"signature", req.signature}
			};
	}
	// licenseReq中不需要使用json string解析
	void from_json(const json& j, reqForm& req) {
	}
}

namespace licenseRsp {
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
	};
	// licenseRsp中不需要转换为json string格式
	void to_json(json& j, const rspForm& rsp) {
	}
	// json string解析
	void from_json(const json& j, reqForm& req) {
	}
}

int main(int argc, char argv[])
{
	licenseReq::reqForm licenseReq;
	json j = licenseReq;
	string reqStr = j.dump();
	cout << "send req: " << reqStr << endl;
	// string testStr = "{\"name\":\"test\",\"data\":1}";
	// http destination
	// 本地测试
	// HttpRequest httpReq("127.0.0.1", 8080);
	// ECS测试
	HttpRequest httpReq("101.132.174.165", 8080);
	// http POST request, get response
	string res = httpReq.HttpPost("/licenseReq", reqStr);
	// cout << endl<<endl<< "get response: " <<endl<< res << endl;
	// get JSON response data
	string licenseRspStr = "";
	int pos = res.find("{");
	// cout << pos << endl;
	licenseRspStr = res.substr(pos);
	// cout << licenseRspStr << endl;
	// parse JSON data
	auto licenseRspObj = json::parse(licenseRspStr);
	// cout << "JSON parse done!" << endl;
	cin.get();
	if (licenseRspObj["version"] == "2.0" && licenseRspObj["type"] == "licenseResponse")
	{
		cout << "licenseRsp read success!" << endl;
	}
	else
	{
		return -1;
	}
	cin.get();
	return 0;
}