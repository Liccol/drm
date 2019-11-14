#include <iostream>
#include "assert.h" 
#include "nlohmann/json.hpp"

using namespace std;
using nlohmann::json;
namespace ns {
	struct person {
		std::string name;
		std::string address;
		int age;
	};

	void to_json(json& j, const person& p) {
		j = json{ {"name", p.name}, {"address", p.address}, {"age", p.age} };
	}

	void from_json(const json& j, person& p) {
		p.name = j.at("name").get<std::string>();
		p.address = j.at("address").get<std::string>();
		p.age = j.at("age").get<int>();
	}
}

int main(int arg, char args[]) {
	string str = "{\"name\":\"test\",\"address\":\"1\",\"age\":12}";
	try {
		auto js = json::parse(str);
		cout << js["name"] << endl;
		//tt = js;
		ns::person p2 = js;
		cout << "test address: " << p2.address << endl;
	}
	catch(exception e){
		cout << e.what() << endl;
	}

	// TODO: 对POST内容的string进行parse, 然后对这个json对象进行结构体赋值 structA = j;从而存到结构体中去.

	// create a person
	ns::person p{ "Ned Flanders", "744 Evergreen Terrace", 60 };

	// conversion: person -> json
	json j = p;

	std::cout << j << std::endl;
	// {"address":"744 Evergreen Terrace","age":60,"name":"Ned Flanders"}

	// conversion: json -> person
	ns::person p2 = j;

	// that's it
	std::cout << p2.address << std::endl;


	


	cin.get();

	return 0;
}