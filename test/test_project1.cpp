#include <iostream>
#include "gtest/gtest.h"

#include "student.h"
#include "json.hpp"

nlohmann::json jst1 = {
	{
	{"name", "Ivanov Petr"},
	{"group", "1"},
	{"avg","4.25"},
	{"debt",nlohmann::detail::value_t::null},
	}
};
vector<student> students;

TEST(Testfunction, fromjson) {
	student s1;
	
	from_Json((jst1[0]), s1);
	students.push_back(s1);
	EXPECT_EQ(s1.name, "Ivanov Petr");
	EXPECT_EQ(gettypegroup(students, 0), "1");
	EXPECT_EQ(gettypeavg(students, 0), "4.25");
	EXPECT_EQ(gettypedebt(students, 0), "null"); 
	EXPECT_TRUE(true);
}

nlohmann::json jst2 = {
	{
	{"name", "Sidorov Ivan"},
	{"group", 31},
	{"avg", 4},
	{"debt", "C++"},
	}
};

TEST(Testfunction, typeCheck1) {
	student s1;
	from_Json((jst2[0]), s1);
	students.push_back(s1);
	EXPECT_EQ(s1.name, "Sidorov Ivan");
	EXPECT_EQ(any_cast<unsigned int>(s1.group), 31);
	EXPECT_EQ(any_cast<unsigned int>(s1.avg), 4);
	EXPECT_EQ(any_cast<string>(s1.debt), "C++");
	EXPECT_TRUE(true);
}

nlohmann::json jst3 = {
	{
	{"name", "Pertov Nikita"},
	{"group", "IU8-31"},
	{"avg", 3.33},
	{"debt", {"C++","Linux","Network"}},
	}
};

TEST(Testfunction, typeCheck2) {
	vector<string>test2;
	test2.push_back("C++");
	test2.push_back("Linux");
	test2.push_back("Network");

	student s1;
	from_Json((jst3[0]), s1);
	students.push_back(s1);
	


	EXPECT_EQ(s1.name, "Pertov Nikita");
	EXPECT_EQ(any_cast<string>(s1.group), "IU8-31");
	EXPECT_EQ(any_cast<double>(s1.avg), 3.33);
	EXPECT_EQ(any_cast<vector<string>>(s1.debt), test2);
	EXPECT_TRUE(true);
}

string sss = R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
})";

TEST(Testfunction, typeCheck3) {
	
	json JS;
	stringstream stream(sss);
	stream >> JS;
	vector<student> students = parseJS(JS);

	student s2;
	s2.name = "Sidorov Ivan";
	s2.group = (unsigned int)31;
	s2.avg = (unsigned int)4;
	s2.debt = new string("C++");

	EXPECT_EQ(students[0].name, "Ivanov Petr");
	EXPECT_EQ(gettypegroup(students,0), "1");
	EXPECT_EQ(gettypeavg(students, 0), "4.25");
	EXPECT_EQ(gettypedebt(students, 0), "null");

	EXPECT_EQ(students[1].name, s2.name);
	EXPECT_EQ(any_cast<unsigned int>(students[1].group), any_cast<unsigned int>(s2.group));
	EXPECT_EQ(any_cast<unsigned int>(students[1].avg), any_cast<unsigned int>(s2.avg));
	EXPECT_EQ(any_cast<string>(students[1].debt), "C++");

	EXPECT_EQ(students[2].name, "Pertov Nikita");
	EXPECT_EQ(any_cast<string>(students[2].group), "IU8-31");
	EXPECT_EQ(any_cast<double>(students[2].avg), 3.33);
	EXPECT_EQ(gettypedebt(students,2), "3 items");

	EXPECT_TRUE(true);

}

string metaString = R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 5
  }
})";

TEST(Testfunction, MetaLength) {
	json JS;
	stringstream stream(metaString);
	stream >> JS;
	EXPECT_ANY_THROW(parseJS(JS));
}
