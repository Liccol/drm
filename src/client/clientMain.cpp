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
/*****************************************************************************
* Function: <name> extract_json
* Description: 从string里面截取第一个json串
* Parameter: 输入string，截取的json
* Returns: 截取的json
* Others: 只截取第一个json，如完全解析，轮训即可
*****************************************************************************/
//string extractJson(string str_in)
//{
//	string str_out = "";
//	int end_time = 1;//string中截取的}的个数，初始为1
//	do
//	{
//		int _start = str_in.find("{");//第一个{的位置
//		if (-1 == _start)
//			return "";
//		int _end = 0;
//		for (int i = 0; i < end_time; i++)//第 end_time个}的位置
//		{
//			_end = str_in.find("}", _end);
//			if (-1 == _end)
//				return "";
//			_end++;
//		}
//		std::string temp = str_in.substr(_start, _end - _start);//第一个{和第end_time个}之间的字符串
//
//		//检测temp字符串含有的{个数
//		int start_num = 0;
//		do
//		{
//			int comma_n = 0;
//			comma_n = temp.find("{");
//			if (-1 == comma_n)
//				break;
//			temp.erase(0, comma_n + 1);
//			start_num++;
//		} while (true);
//
//		//检测temp字符串含有的}个数
//		int end_num = 0;
//		temp = str_in.substr(_start, _end - _start);
//		do
//		{
//			int comma_n = 0;
//			comma_n = temp.find("}");
//			if (-1 == comma_n)
//				break;
//			temp.erase(0, comma_n + 1);
//			end_num++;
//		} while (true);
//
//		if (start_num == end_num)//如果{和}的数量相等，则判断为标准json
//		{
//			str_out = str_in.substr(_start, _end - _start + 1);
//			return str_out;
//		}
//		else//如不等，重新截取temp，下次多截取一个}
//		{
//			end_time++;
//		}
//
//	} while (true);
//
//}
int main(int argc, char argv[])
{
	licenseReq::reqForm licenseReq;
	json j = licenseReq;
	string reqStr = j.dump();
	cout << "send req: " << reqStr << endl;
	// string testStr = "{\"name\":\"test\",\"data\":1}";
	// http destination
	HttpRequest httpReq("127.0.0.1", 8080);
	// http POST request, get response
	string res = httpReq.HttpPost("/licenseReq", reqStr);
	cout << endl<<endl<< "get response: " <<endl<< res << endl;
	string licenseRspStr = "";
	int pos = res.find("{");
	cout << pos << endl;
	licenseRspStr = res.substr(pos);
	cout << licenseRspStr << endl;
	// 貌似不是这么parse的?或者结构使用用[]来获取的
	auto licenseRspObj = json::parse(licenseRspStr);
	cout << "JSON parse done!" << endl;
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