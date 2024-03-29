#include <stdio.h>
#include "rapidjson_lib.h"

using namespace std;

// 解析json数据测试
void testReadJson() {

	const char* str = "{\"name\":\"xiaoming\",\"age\":18,\"job\":\"coder\",\"a\":{\"b\":1}}";

	Document doc;
	// 在DOM中解析json字符串
	doc.Parse(str);

	//// 读取json数据
	//const Value& age = doc["age"];
	//printf("age=%d \n", age.GetInt());

	//// 读取对象中的对象
	//const Value& b = doc["a"]["b"];
	//printf("b=%d \n", b.GetInt());

	// 序列化
	StringBuffer buff;
	Writer<StringBuffer> writer(buff);
	doc.Accept(writer);

	// 打印json字符串
	printf(buff.GetString());
}

// 写入json数据测试
void testWriteJson() {

	const char* name = "xiaoming";
	int age = 18;
	double height = 1.64;

	StringBuffer buff;
	Writer<StringBuffer> writer(buff);

	writer.StartObject();

	writer.String("name");
	//writer.String(name,10); 第二个参数用于设置写入字符串长度，如果超出字符串长度会有垃圾数据
	writer.String(name);

	writer.String("age");
	writer.Int(age);

	writer.String("height");
	writer.Double(height);

	// 数组
	writer.String("arr");
	writer.StartArray();
	for (int i = 0; i < 5; ++i)
	{
		writer.Int(i);
	}
	writer.EndArray();

	writer.EndObject();

	printf(buff.GetString());
}


// 测试解析数组
void testReadArr() {

	const char* str = "{\"employees\": [{ \"firstName\":\"John\" , \"lastName\":\"Doe\" },{ \"firstName\":\"Anna\" , \"lastName\":\"Smith\" },{ \"firstName\":\"Peter\" , \"lastName\":\"Jones\"}]}";

	Document doc;
	doc.Parse(str);

	if (doc.HasParseError() == false)
	{
		const Value& employees = doc["employees"];

		// rapidjson uses SizeType instead of size_t.
		for (SizeType i = 0; i < employees.Size(); i++)
		{
			const Value& temp = employees[i];

			printf("firstName=%s，lastName=%s \n", temp["firstName"].GetString(), temp["lastName"].GetString());
		}
	}
	else {
		printf("parse error!\n");
	}
}

// 写数组
void testWriteArr() {
	StringBuffer buff;
	Writer<StringBuffer> writer(buff);

	writer.StartArray();
	for (int i = 0; i < 5; ++i)
	{
		writer.Int(i);
	}
	writer.EndArray();

	printf("%s", buff.GetString());
}

int main() {

	testReadJson();

	//testWriteJson();

	//testReadArr();

	//testWriteArr();

	getchar();
}