// test4HTTP.cpp : �������̨Ӧ�ó������ڵ㡣
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
	// licenseReq�в���Ҫʹ��json string����
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
	// licenseRsp�в���Ҫת��Ϊjson string��ʽ
	void to_json(json& j, const rspForm& rsp) {
	}
	// json string����
	void from_json(const json& j, reqForm& req) {
	}
}
/*****************************************************************************
* Function: <name> extract_json
* Description: ��string�����ȡ��һ��json��
* Parameter: ����string����ȡ��json
* Returns: ��ȡ��json
* Others: ֻ��ȡ��һ��json������ȫ��������ѵ����
*****************************************************************************/
//string extractJson(string str_in)
//{
//	string str_out = "";
//	int end_time = 1;//string�н�ȡ��}�ĸ�������ʼΪ1
//	do
//	{
//		int _start = str_in.find("{");//��һ��{��λ��
//		if (-1 == _start)
//			return "";
//		int _end = 0;
//		for (int i = 0; i < end_time; i++)//�� end_time��}��λ��
//		{
//			_end = str_in.find("}", _end);
//			if (-1 == _end)
//				return "";
//			_end++;
//		}
//		std::string temp = str_in.substr(_start, _end - _start);//��һ��{�͵�end_time��}֮����ַ���
//
//		//���temp�ַ������е�{����
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
//		//���temp�ַ������е�}����
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
//		if (start_num == end_num)//���{��}��������ȣ����ж�Ϊ��׼json
//		{
//			str_out = str_in.substr(_start, _end - _start + 1);
//			return str_out;
//		}
//		else//�粻�ȣ����½�ȡtemp���´ζ��ȡһ��}
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
	// ò�Ʋ�����ôparse��?���߽ṹʹ����[]����ȡ��
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