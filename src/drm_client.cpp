#include <stdio.h>
#include <guiddef.h>
#include <combaseapi.h>
#include <iostream>
using namespace std;

extern "C"
{
#include "lua/src/lua.h"  
#include "lua/src/lualib.h"  
#include "lua/src/lauxlib.h"  
}
#define GUID_LEN 64

// 常量定义
// 授权状态
typedef enum {
	CDRMC_RIGHTS_VALID        = 0x00,	//有效
	CDRMC_RIGHTS_INVALID      = 0x01,	//无效
	CDRMC_RIGHTS_NOT_ACQUIRED = 0x02,	//没有权限
	CDRMC_RIGHTS_EXPIRED      = 0x03,	//权限过期
} CDRMC_Rights_Status;
// 对称加密算法及模式
typedef enum {
	CDRMC_ALG_SM4_CBC_NOPAD      = 0x01,//SM4_CBC
	CDRMC_ALG_SM4_CTR            = 0x02,//SM4_CTR 
	CDRMC_ALG_AES_128_CBC_NOPAD  = 0x03,//AES_128_CBC_NOPAD
	CDRMC_ALG_AES_128_CTR        = 0x04,//AES_128_CTR
} CDRMC_Symmetric_Crypto_Algorithm;
// CENC工作模式
typedef enum {
	CDRMC_ALG_CENC_AES_CTR  = 0x01,		//AES_CTR
	CDRMC_ALG_CENC_AES_CBC  = 0x02,		//AES_CBC
	CDRMC_ALG_CENC_SM4_CTR  = 0x03,		//SM4_CTR
	CDRMC_ALG_CENC_SM4_CBC  = 0x04,		//SM4_CBC
} CDRMC_Cenc_Algorithm;

// 数据结构定义
// Cipher句柄
typedef void* CDRMC_SessionHandle;
// CDRMC_SubSample
typedef struct __CDRMC_SubSample
{
    unsigned int u32ClearHeaderLen;		//一个subsample中清流数据长度
    unsigned int u32PayLoadLen;			//一个subsample中加密流对应的数据长度
} CDRMC_SubSample;
// CENC结构定义
typedef struct __CDRMC_Cenc
{
	unsigned int u32KeyIdLen;			//密钥标识长度
	unsigned char* pu8KeyId;			//密钥标识
	unsigned int u32IVLen;				//
	unsigned char * pu8IV;				//初始向量
	unsigned int u32FirstEncryptOffset;	//偏移地址
	CDRMC_SubSample * pstSubSample;		//Subsample
	unsigned int u32SubsampleNum;		//Subsample数量
} CDRMC_Cenc;

// 辅助函数定义
// char * ---> unsigned char *转换, 待测试
//void convertStrToUnChar(char* str, unsigned char* UnChar)
//{
//	int i = strlen(str), j = 0, counter = 0;
//	cout << i;
//	char c[2];
//	unsigned int bytes[2];
//	for (j = 0; j < i; j += 2)
//	{
//		if (0 == j % 2)
//		{
//			c[0] = str[j];
//			c[1] = str[j + 1];
//			sscanf(c, "%02x", &bytes[0]);
//			UnChar[counter] = bytes[0];
//			counter++;
//		}
//	}
//	cout << UnChar;
//	return;
//}

// 接口定义
int CDRMC_OpenSession (CDRMC_SessionHandle *phSession)
{
	printf("Session opened.\n");
    return 0;
}

int CDRMC_CloseSession (CDRMC_SessionHandle hSession)
{
    printf("Session closed.\n");
    return 0;
}
/*
DRM信息:pu8DrmInfo, include
---------name----------|--bit---
descriptor_tag         |   8
descriptor_length      |   8
video_format           |   4
video_encryption_method|   4
audio_format           |   4
audio_encryption_method|   4
DRM_data_bytes         |(description_length-2)*8
*/
// 获取许可证请求，得到许可证请求内容--->>>查看下许可证请求里面是不是要带设备ID信息？

int CDRMC_GetLicenseRequest (
				CDRMC_SessionHandle hSession, 
	            unsigned char* pu8DrmInfo,
	            unsigned int u32DrmInfoLen,
	            unsigned char* pu8LicenseRequest, 
	            unsigned int* pu32LicenseRequestLen)
{
	return 0;
}
// 功能：处理许可证响应消息。
// 参数：hSession—输入参数，DRM会话句柄；
// pu8LicenseResponse—输入参数，许可证数据；
// u32LicenseResponseLen—输入参数，许可证数据长度。
// 返回：int，0表示成功，其他表示失败。
int CDRMC_ProcessLicenseResponse (CDRMC_SessionHandle hSession,
	            unsigned char* pu8LicenseResponse, 
	            unsigned int u32LicenseResponseLen)
{
	lua_State *L = luaL_newstate();
	if (L == NULL)
	{
		cout << "Creat Lua State Error !" << endl;
		return -1;
	}
	luaL_openlibs(L);
	int ret = luaL_dofile(L, "D:\\vsProject\\drm\\drm\\src\\luacode\\functionsForDrm.lua");
	if (ret)
	{
		cout << "Lua doFile Error !" << endl;
		cin.get();
		return 1;
	}
	lua_getglobal(L, "processLicenseResponse");
	lua_pushstring(L, (const char*)pu8LicenseResponse);
	lua_pushnumber(L, u32LicenseResponseLen);
	lua_pcall(L, 2, 0, 0);
	if (lua_isnumber(L, -1))
	{
		cout << "the result is :" << lua_tonumber(L, -1) << endl;
	}
	lua_close(L);
	return 0;
}
//功能：获取证书（DRM证书）申请消息。------>>>>需要看一下DRM证书结构
//参数：hSession—输入参数，DRM会话句柄；
//pu8ProvisionRequest—输出参数，证书请求数据缓冲区；
//pu32ProvisionRequestLen—输入输出参数，输入证书请求数据缓冲区长度，输出证书请求数据长度。
//返回：int，0表示成功，其他表示失败。
int CDRMC_GetProvisionRequest (CDRMC_SessionHandle hSession, 
	            unsigned char* pu8ProvisionRequest, 
	            unsigned int* pu32ProvisionRequestLen)
{
	return 0;
}
//功能：处理证书（DRM证书）响应消息。
//参数：hSession—输入参数，DRM会话句柄；
//pu8ProvisionResponse—输入参数，证书数据；
//u32ProvisionResponseLen—输入参数，证书数据长度。
//返回：int，0表示成功，其他表示失败。
int CDRMC_ProcessProvisionResponse (CDRMC_SessionHandle hSession, 
	            unsigned char* pu8ProvisionResponse, 
	            unsigned int u32ProvisionResponseLen)
{
	
	return 0;
}
//功能：查询授权状态。-------->>>是不是在解析的时候就把这个修改了？
//参数：hSession—输入参数，DRM会话句柄；
//pu8DrmInfo—输入参数，DRM信息；
//u32DrmInfoLen—输入参数，DRM信息长度；
//pRightsStatus—输出参数，授权状态。
//返回：int，0表示成功，其他表示失败。
int CDRMC_CheckRightsStatus (CDRMC_SessionHandle hSession, 
	            unsigned char* pu8DrmInfo, 
	            unsigned int u32DrmInfoLen, 
	            CDRMC_Rights_Status* pRightsStatus)
{
	lua_State *L = luaL_newstate();
	if (L == NULL)
	{
		cout << "Creat Lua State Error !" << endl;
		return -1;
	}
	luaL_openlibs(L);
	int ret = luaL_dofile(L, "D:\\vsProject\\drm\\drm\\src\\luacode\\functionsForDrm.lua");
	if (ret)
	{
		cout << "Lua doFile Error !" << endl; 
		cin.get();
		return 1;
	}
	lua_getglobal(L, "checkRightStatus");
	lua_pcall(L, 0, 1, 0);
	if (lua_isnumber(L, -1))
	{
		cout << "the result is :" << lua_tonumber(L, -1) << endl;
	}
	int statusRtn = lua_tonumber(L, -1);
	switch (statusRtn)
	{
	case 0:
		*pRightsStatus = CDRMC_RIGHTS_VALID;
		break;
	case 1:
		*pRightsStatus = CDRMC_RIGHTS_INVALID;
		break;
	case 2:
		*pRightsStatus = CDRMC_RIGHTS_NOT_ACQUIRED;
		break;
	case 3:
		*pRightsStatus = CDRMC_RIGHTS_EXPIRED;
		break;
	default:
		break;
	}
	lua_close(L);
	return 0;
}
//功能：解密。
//参数：hSession—输入参数，DRM会话句柄；
//pu8DrmInfo—输入参数，DRM信息；
//u32DrmInfoLen—输入参数，DRM信息长度；
//algo—输入参数，算法类型；
//pu8Iv—输入参数，初始向量；
//u32IvLen—输入参数，初始向量长度；
//pu8Input—输入参数，需解密的数据；
//u32InLen—输入参数，需解密数据的长度；
//pu8Output—输出参数，解密后数据存储的缓冲区；
//pu32OutLen—输入输出参数，输入解密后数据存储的缓冲区长度，输出解密后数据长度。
//返回：int，0表示成功，其他表示失败。
int CDRMC_Decrypt (CDRMC_SessionHandle hSession, 
				unsigned char* pu8DrmInfo, 
				unsigned int u32DrmInfoLen,
				CDRMC_Symmetric_Crypto_Algorithm algo, 
				unsigned char*pu8Iv, 
				unsigned int u32IvLen, 
				unsigned char*pu8Input, 
				unsigned int u32InLen, 
				unsigned char *pu8Output, 
				unsigned int *pu32OutLen)
{
	return 0;
}
//功能：CENC（通用加密格式）解密。
//参数：hSession—输入参数，DRM会话句柄；
//pu8DrmInfo—输入参数，DRM信息；
//u32DrmInfoLen—输入参数，DRM信息长度；
//algo—输入参数，算法类型；
//pstCENC—输入参数，CENC结构体；
//pu8Input—输入参数，需解密的数据；
//u32InLen—输入参数，需解密数据的长度；
//pu8Output—输出参数，解密后数据存储的缓冲区；
//pu32OutLen—输入输出参数，输入解密后数据存储的缓冲区长度，输出解密后数据长度。
//返回：int，0表示成功，其他表示失败。
int CDRMC_Cenc_Decrypt (CDRMC_SessionHandle hSession, 
				unsigned char* pu8DrmInfo, 
				unsigned int u32DrmInfoLen,  
				//CDRMC_Cenc_ Algorithm algo, 
				CDRMC_Cenc* pstCENC, 
				unsigned char*pu8Input, 
				unsigned int u32InLen, 
				unsigned char *pu8Output, 
				unsigned int* pu32OutLen)
{
	return 0;
}
//功能：获取设备唯一标识。
//参数：hSession—输入参数，DRM会话句柄；
//pu8DeviceId—输出参数，设备唯一标识；
//pu32DeviceIdLen—输入输出参数，输入设备唯一标识缓冲区长度，输出设备唯一标识长度。返回int，0表示成功，其他表示失败。
int CDRMC_GetDeviceId (CDRMC_SessionHandle hSession, 
				unsigned char * pu8DeviceId, 
				unsigned int* pu32DeviceIdLen)
{
	char buffer[GUID_LEN] = { 0 };
	GUID guid;
	if (CoCreateGuid(&guid))
	{
		fprintf(stderr, "create guid error\n");
		return -1;
	}
	_snprintf(buffer, sizeof(buffer),
		"%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1], guid.Data4[2],
		guid.Data4[3], guid.Data4[4], guid.Data4[5],
		guid.Data4[6], guid.Data4[7]);
	cout << "guid is " << buffer << endl;
	*pu32DeviceIdLen = strlen(buffer);
	//TODO: 把char*数据转到uchar*数据中去
	//convertStrToUnChar(buffer, pu8DeviceId);
	//cout << "guid is " << pu8DeviceId << endl;
	return 0;
}
//功能：获取设备证书。
//参数：hSession—输入参数，DRM会话句柄；
//pu8DeviceCert—输出参数，设备证书；
//pu32DeviceCertLen—输入输出参数，输入设备证书缓冲区长度，输出设备证书长度。
//返回：int，0表示成功，其他表示失败。
int CDRMC_GetDeviceCert (CDRMC_SessionHandle hSession, 
				unsigned char * pu8DeviceCert, 
				unsigned int* pu32DeviceCertLen)
{

	return 0;
}
//功能：获取DRM厂商标识。------->DRMID应该是内置在设备内部的，随机设定一个（通过lua去获取）,写一个数据交互函数就行了
//参数：hSession—输入参数，DRM会话句柄；
//pu8DrmId—输出参数，DRM客户端厂商标识；
//pu32DrmIdLen—输入输出参数，输入DRM客户端厂商标识缓冲区长度，输出DRM客户端厂商标识长度。
//返回：int，0表示成功，其他表示失败。
int CDRMC_GetDrmId (CDRMC_SessionHandle hSession, 
				unsigned char* pu8DrmId, 
				unsigned int* pu32DrmIdLen)
{
	lua_State *L = luaL_newstate();
	if (L == NULL)
	{
		cout << "Creat Lua State Error !" << endl;
		return -1;
	}
	luaL_openlibs(L);
	int ret = luaL_dofile(L, "D:\\vsProject\\drm\\drm\\src\\luacode\\functionsForDrm.lua");
	if (ret)
	{
		cout << "Lua doFile Error !" << endl;
		cin.get();
		return 1;
	}
	lua_getglobal(L, "getDrmId");
	lua_pcall(L, 0, 1, 0);
	if (lua_isnumber(L, -1))
	{
		cout << "the result is :" << lua_tostring(L, -1) << endl;
	}
	string strRtn = lua_tostring(L, -1);
	pu8DrmId = (unsigned char *)strRtn.c_str();
	lua_close(L);
	return 0;
}

int main(int argc, char* argv[]) {
	// TODO: 初始化优化
	cout << "start DRM client" << endl;
	CDRMC_SessionHandle hSession = NULL;
	unsigned char deviceId[] = "";
	unsigned int deviceIdLen = 0; 
	cout << "start CDRMC_GetDeviceId test!" << endl;
	if (CDRMC_GetDeviceId(hSession, deviceId, &deviceIdLen)) {
		cout << "CDRMC_GetDeviceId error" << endl;
		return -1;
	}
	cout << "Length of device ID is "<< deviceIdLen << endl;
	cout << "end CDRMC_GetDeviceId test" << endl << endl;

	unsigned char pu8LicenseResponse[] = "01010028FF02020028FE03030028FD04040028FCFF080028FA05050028FB";
	// 使用sizeof的时候会把最后一个当作\n这类结尾符来处理?
	unsigned int u32LicenseResponseLen = sizeof(pu8LicenseResponse) - 1;
	cout << "start CDRMC_ProcessLicenseResponse test!" << endl;
	if (CDRMC_ProcessLicenseResponse(hSession, pu8LicenseResponse, u32LicenseResponseLen)) {
		cout << "CDRMC_ProcessLicenseResponse error" << endl;
		return -1;
	}
	cout << "end CDRMC_ProcessLicenseResponse test" << endl << endl;
	
	unsigned char pu8DrmInfo[] = "2121423213";
	unsigned int u32DrmInfoLen = sizeof(pu8DrmInfo) - 1;
	cout << pu8DrmInfo << endl << u32DrmInfoLen << endl;
	CDRMC_Rights_Status pRightsStatus = CDRMC_RIGHTS_INVALID;
	cout << "start CDRMC_CheckRightsStatus test!" << endl;
	if (CDRMC_CheckRightsStatus(hSession, pu8DrmInfo, u32DrmInfoLen, &pRightsStatus)) {
		cout << "CDRMC_CheckRightsStatus error" << endl;
		return -1;
	}
	cout << "rights status is " << pRightsStatus << endl;
	cout << "end CDRMC_CheckRightsStatus test" << endl << endl;



	cin.get();
	return 0;
}