//#include <QCoreApplication>
/*
#include "dataSource/cdatabaseobject.h"
#include <iostream>
using namespace std;*/
#include "test.h"
using namespace  std;
int main(int argc, char *argv[])
{
   // QCoreApplication a(argc, argv);
    if(argc  >= 1 )
    {
        int ssize = sizeof(*argv);
        ssize ++;
    }

    Test::TestMathExpression();
    Test::TestJosonCppArray();
    Test::TestJsonCppFile();
    Test::TestJsonCppMem();
    Test::TestJsonCppWrite();
    Test::TestCurlFtp();

    return 0;
    //return a.exec();
}
