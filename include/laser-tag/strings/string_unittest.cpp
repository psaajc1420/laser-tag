/*
    Jacob Cadena
    11/22/18
    list_unitest.cpp    
    
*/

#include <limits.h>
#include <cstring>
#include "ds_string.h"
#include "gtest/gtest.h"

namespace {

    class StringTest : public testing::Test {
        protected: 
            virtual void SetUp() {
                s[0] = String("testString");
                s[1] = String("a test string");
                s[2] = String("");
                s[3] = String("THIS IS AN UPPERCASE STRING");
                s[4] = String("this is an uppercase string");
                s[5] = String("\n");
                s[6] = String("");
                s[7] = String("  split  split  split  ");
                s[8] = String("                          ");
                s[9] = String("testString");
            }

            String s[10];
    };

    
    // Tests the equality operator
    TEST_F(StringTest, EqualityOperator) {
        EXPECT_TRUE(s[0] == String("testString"));
        EXPECT_TRUE(s[0] == s[9]);
        EXPECT_TRUE(s[2] == "");
        EXPECT_TRUE(s[1] == "a test string");
        EXPECT_FALSE(s[3] == s[4]);
    }

    // Tests the assignment operator
    TEST_F(StringTest, AssigmentOperator) {
        String str;
        str = "a test string";
        EXPECT_TRUE(str == s[1]);
        EXPECT_EQ(13, str.size()); 
        EXPECT_EQ(13, strlen(str.c_str())); 
        str = String("testString");
        EXPECT_TRUE(str == s[0]);
        EXPECT_EQ(10, str.size()); 
        EXPECT_EQ(10, strlen(str.c_str())); 
        str = "";
        EXPECT_TRUE(str == s[6]);
        str = String("\n");
        EXPECT_TRUE(str == s[5]);
    }
    
    // Tests the addition operator
    TEST_F(StringTest, AdditionOperator) {
        EXPECT_TRUE(String("testStringtestString") == s[0]+s[9]);
        EXPECT_TRUE(s[6] + s[6] == "");
        EXPECT_TRUE(s[5] + s[6] == String("\n"));
        EXPECT_TRUE(s[0] + s[1] + s[2] == "testStringa test string");
        EXPECT_TRUE(String("testStringtestString") == "testStringtestString");
    }
    

    // Tests the greater than operator
    TEST_F(StringTest, GreaterThanOperator) {
        EXPECT_TRUE(s[0] > s[1]);
        EXPECT_TRUE(s[4] > s[3]);
        EXPECT_TRUE(s[9] > s[6]);
        EXPECT_TRUE(s[7] > s[6]);
    }

    // Tests the less than operator
    TEST_F(StringTest, LessThanOperator) {
        EXPECT_TRUE(s[1] < s[0]);
        EXPECT_TRUE(s[3] < s[4]);
        EXPECT_TRUE(s[6] < s[9]);
        EXPECT_TRUE(s[6] < s[7]);
    }

    // Tests the [] operator
    TEST_F(StringTest, DereferenceOperator) {
        EXPECT_TRUE(s[0][1] == 'e');
        EXPECT_TRUE(s[4][4] == ' ');
        EXPECT_TRUE(s[6][0] == 0);
    }

    // Tests the size function
    TEST_F(StringTest, Size) {
        EXPECT_TRUE(s[9].size() == 10);
        EXPECT_EQ(10, strlen(s[9].c_str())); 
        EXPECT_TRUE(s[2].size() == 0);
        EXPECT_EQ(0, strlen(s[2].c_str()));
        EXPECT_TRUE(s[8].size() == 26);
        EXPECT_EQ(26, strlen(s[8].c_str()));
        EXPECT_TRUE(s[3].size() == 27);
        EXPECT_EQ(27, strlen(s[3].c_str()));
    }    

    // Tests the c_str function
    TEST_F(StringTest, c_str) {
        EXPECT_TRUE(strcmp(s[0].c_str(), "testString") == 0);
        EXPECT_TRUE(strcmp(s[9].c_str(), s[0].c_str()) == 0);
        EXPECT_TRUE(strcmp(s[2].c_str(), "") == 0);
    }    

    // Tests the substring function
    TEST_F(StringTest, Substring) {
        EXPECT_TRUE(strcmp(s[0].c_str(), "testString") == 0);
        EXPECT_TRUE(strcmp(s[9].c_str(), s[0].c_str()) == 0);
        EXPECT_TRUE(strcmp(s[2].c_str(), "") == 0);
    }

    // Tests the substring function
    TEST_F(StringTest, Find) {
        String s = "This is an awesome fun project. Let's do this again.";
        EXPECT_EQ(String::npos, s.find("beautiful"));
        EXPECT_EQ(String::npos, s.find(String("beautiful")));
        EXPECT_EQ(String::npos, s.find("focus"));
        EXPECT_EQ(String::npos, s.find(String("focus")));
        EXPECT_EQ(11, s.find("awesome"));
        EXPECT_EQ(11, s.find(String("awesome")));
        EXPECT_EQ(30, s.find(String(".")));
        EXPECT_EQ(30, s.find("."));
    }    

    // Tests the push_back function
    TEST_F(StringTest, push_back) {
        
        // push_back char
        String s;
        EXPECT_EQ(nullptr, s.c_str());
        EXPECT_EQ(0, s.size());
        s.push_back('j');
        EXPECT_EQ(1, s.size());
        EXPECT_EQ(1, strlen(s.c_str()));
        s.push_back('a');
        s.push_back('c');
        s.push_back('o');
        s.push_back('b');
        EXPECT_EQ(5, s.size());
        EXPECT_EQ(5, strlen(s.c_str()));
        EXPECT_TRUE(strcmp("jacob", s.c_str()) == 0);
        
        // push_back char*
        String s2;
        EXPECT_EQ(nullptr, s2.c_str());
        EXPECT_EQ(0, s2.size());
        s2.push_back("This should work");
        EXPECT_TRUE(strcmp("This should work", s2.c_str()) == 0);
        EXPECT_EQ(16, s2.size());

        // push_back string
        String s3;
        EXPECT_EQ(nullptr, s3.c_str());
        EXPECT_EQ(0, s3.size());
        s3.push_back(String("This should work again"));
        EXPECT_TRUE(strcmp("This should work again", s3.c_str()) == 0);
        EXPECT_EQ(22, s3.size());

    }    

    // Tests the push_back function
    TEST_F(StringTest, AdditionAssignmentOperator) {

        // += (const char) 
        String s;
        EXPECT_EQ(nullptr, s.c_str());
        EXPECT_EQ(0, s.size());
        s += 'j';
        EXPECT_EQ(1, s.size());
        EXPECT_EQ(1, strlen(s.c_str()));
        s += 'a';
        s += 'c';
        s += 'o';
        s += 'b';
        EXPECT_EQ(5, s.size());
        EXPECT_EQ(5, strlen(s.c_str()));

        // += (const char*)
        String s2;
        EXPECT_EQ(nullptr, s2.c_str());
        EXPECT_EQ(0, s2.size());
        s2 += "This should work";
        EXPECT_TRUE(strcmp("This should work", s2.c_str()) == 0);
        EXPECT_EQ(16, s2.size());
        
        // += (const String&)
        String s3;
        EXPECT_EQ(nullptr, s3.c_str());
        EXPECT_EQ(0, s3.size());
        s3 += String("This should work again");
        EXPECT_TRUE(strcmp("This should work again", s3.c_str()) == 0);
        EXPECT_EQ(22, s3.size());
    }


} // namespace
