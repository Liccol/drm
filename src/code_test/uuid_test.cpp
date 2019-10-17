#include <stdio.h>
#include <guiddef.h>
#include <combaseapi.h>
#include <iostream>
#define GUID_LEN 64  
using namespace std;

std::string GuidToString()
{
	char buffer[GUID_LEN] = { 0 };
	GUID guid;

	if (CoCreateGuid(&guid))
	{
		fprintf(stderr, "create guid error\n");
		return "error";
	}
	_snprintf(buffer, sizeof(buffer),
		"%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1], guid.Data4[2],
		guid.Data4[3], guid.Data4[4], guid.Data4[5],
		guid.Data4[6], guid.Data4[7]);
	return std::string(buffer);
}
int main(int argc, char* argv[]) {
	std::string guid_pc = GuidToString();
	cout<< "guid is "<< guid_pc.c_str() << endl;
	cin.get();
	return 0;
}