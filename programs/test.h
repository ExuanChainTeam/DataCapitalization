#ifndef TEST_H
#define TEST_H
#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cstdlib>
#include <cstring>
extern FILE*fp;
class Test
{
public:
    Test();
public:
    static std::vector<std::string> preParse(char*str);
    static int getPriority(std::string opt);
    static void calculate(std::stack<int>& opdStack,std::string opt);
    static int evaMidExpression(char*str);
    static void TestMathExpression();
public:
    static void TestJosonCppArray();
    static void TestJsonCppFile();
    static void TestJsonCppMem();
    static void TestJsonCppWrite();
    static void writeMem();
    static void writeObject();
    static void writeArray();
public:
    static void TestCurlFtp();
    static size_t writeData(void*ptr,size_t size,size_t nmemb,void*stream);
    static void TestCurlDown(std::string &strUrl, std::string &filename);
    static void TestCurlUpload(const std::string&strFile,const std::string&strUrl);
    static size_t readFunction(void *buffer, size_t size, size_t count, FILE *stream);
};

#endif // TEST_H
