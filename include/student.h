#include <iostream>
#include <vector>
#include <iomanip>
#include "json.hpp"
#include <fstream>
#include <string.h>
#include <any>

using namespace std;
using namespace nlohmann;

struct student {
	string name;
	any group;
	any avg;
	any debt;
};

auto get_name(const json& j) -> std::string {
	return j.get<string>();
}

auto get_group(const json& j) -> std::any {
	if (j.is_string())
		return j.get<string>();
	else
		return j.get<size_t>();
}

auto get_avg(const json& j) -> any {
	if (j.is_null())
		return nullptr;
	else if (j.is_string())
		return j.get<string>();
	else if (j.is_number_float())
		return j.get<double>();
	else
		return j.get<size_t>();
}

auto getDebt(const json& j) ->any {
	if (j.is_null())
		return nullptr;
	else if (j.is_string())
		return j.get<string>();
	else {
		return j.get<vector<string> >();
	}
}

void from_Json(const json& j, student& s) {

	s.name = get_name(j.at("name"));
	s.group = get_group(j.at("group"));
	s.avg = get_avg(j.at("avg"));
	s.debt = getDebt(j.at("debt"));
}
string gettypegroup(vector <student> st, int n) {
	if (st[n].group.type().name() == typeid (string).name())
	{
		return any_cast <string> (st[n].group);

	}
	else if (st[n].group.type().name() == typeid (unsigned int).name()) {
		return to_string(any_cast <unsigned int> (st[n].group));
	}
	else {
		return "null";
	}
}

string gettypeavg(vector <student> st, int n) {
	if (st[n].avg.type().name() == typeid (string).name())
	{
		return any_cast <string> (st[n].avg);
	}
	else if (st[n].avg.type().name() == typeid (unsigned int).name()) {
		return to_string(any_cast <unsigned int> (st[n].avg));


	}
	else if (st[n].avg.type().name() == typeid (double).name()) {
		return to_string(any_cast <double> (st[n].avg));
	}
	else {
		return "null";
	}
}

string gettypedebt(vector <student> st, int n) {
	if (st[n].debt.type().name() == typeid (nullptr_t).name()) {
		return "null";
	}
	if (st[n].debt.type().name() == typeid (string).name())
	{
		return any_cast <string> (st[n].debt);
	}
	else {
		return  to_string(any_cast<vector<string>>(st[n].debt).size()) + " items";
	}
}

vector<student> parseJS(json js) {
	int length = js["_meta"]["count"];

	int checkLength = 0;
	for (json::iterator i = js["items"].begin(); i != js["items"].end(); i++) {
		checkLength++;
	}

	if (length != checkLength) {
		cout << "_meta: count != items.count" << endl;
		throw new runtime_error("\_meta: count != items.count");
	}

	vector<student> students;
	cout << "|" << setw(18) << left << " name" << "|" << setw(8)
		<< " group" << "|" << setw(8) << " avg" << "|" << setw(18) << " dept" << "|" << endl;
	string stemp = "|------------------|--------|--------|------------------|";
	cout << stemp << endl;
	for (int i = 0; i < length; i++) {
		student p;
		from_Json((js["items"][i]), p);
		students.push_back(p);
	}
	for (int i = 0; i < length; i++) {
		cout << "|" << setw(18) << left << students[i].name << "|" << setw(8)
			<< gettypegroup(students, i) << "|" << setw(8) << gettypeavg(students, i) << "|" << setw(18) << gettypedebt(students, i) << "|" << endl;
		cout << stemp << endl;
	}
	return students;
}