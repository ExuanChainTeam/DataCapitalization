#include "test.h"
#include "globalfunction.h"
#include "jsonconfig.h"
#include "curlconfig.h"
#include <fstream>
using namespace  std;
FILE*fp;
Test::Test()
{

}

vector<string> Test::preParse(char *str)
{
    vector<string>  tokens;
    int len = strlen(str);
    char*p = (char*)malloc((len+1)*sizeof(char));
    int i =0,j =0;
    while(i < len)
    {
        if(str[i] ==  ' ')
        {
            i++ ;
            continue;
        }
        p[j++] = str[i++];
    }
    p[j] = '\0';
    j =0;
    len = strlen(p);
    while(j<len)
    {
        char temp[2];
        string token;
        switch (p[j])
        {
        case '+':
        case '*':
        case '/':
        case '(':
        case ')':
            {
                temp[0] = p[j];
                temp[1] = '\0';
                token=temp;
                tokens.push_back(token);
            }
            break;
        case '-':
            {
                if(p[j-1]==')'||isdigit(p[j-1]))  //作为减号使用
                {
                   temp[0] =p[j];
                   temp[1] = '\0';
                   token=temp;
                   tokens.push_back(token);
                }
                else    //作为负号使用
                {
                   temp[0] ='#';
                   temp[1] = '\0';
                   token=temp;
                   tokens.push_back(token);
                }
                break;
            }
        default:
            {
               i = j;
               while(isdigit(p[i])&&i<len)
               {
                   i++;
               }
               char *opd = (char *)malloc(i-j+1);
               strncpy(opd,p+j,i-j);
               opd[i-j]='\0';
               token=opd;
               tokens.push_back(token);
               j=i-1;
               free(opd);
               break;
            }
            break;
        }
        j++;
    }

    free(p);
    return tokens;

}

int Test::getPriority(string opt)
{
    int priority;
    if(opt=="#")
        priority = 3;
    else if(opt=="*"||opt=="/")
        priority = 2;
    else if(opt=="+"||opt=="-")
        priority = 1;
    else if(opt=="(")
        priority = 0;
    return priority;
}

void Test::calculate(stack<int> &opdStack, string opt)
{
    if(opt=="#")  //进行负号运算
    {
        int opd = opdStack.top();
        int result = 0-opd;
        opdStack.pop();
        opdStack.push(result);
        cout<<"操作符:"<<opt<<" "<<"操作数:"<<opd<<endl;
    }
    else if(opt=="+")
    {
        int rOpd = opdStack.top();
        opdStack.pop();
        int lOpd = opdStack.top();
        opdStack.pop();
        int result = lOpd + rOpd;
        opdStack.push(result);

        cout<<"操作符:"<<opt<<" "<<"操作数:"<<lOpd<<" "<<rOpd<<endl;
    }
    else if(opt=="-")
    {
        int rOpd = opdStack.top();
        opdStack.pop();
        int lOpd = opdStack.top();
        opdStack.pop();
        int result = lOpd - rOpd;
        opdStack.push(result);
        cout<<"操作符:"<<opt<<" "<<"操作数:"<<lOpd<<" "<<rOpd<<endl;
    }
    else if(opt=="*")
    {
        int rOpd = opdStack.top();
        opdStack.pop();
        int lOpd = opdStack.top();
        opdStack.pop();
        int result = lOpd * rOpd;
        opdStack.push(result);
        cout<<"操作符:"<<opt<<" "<<"操作数:"<<lOpd<<" "<<rOpd<<endl;
    }
    else if(opt=="/")
    {
        int rOpd = opdStack.top();
        opdStack.pop();
        int lOpd = opdStack.top();
        opdStack.pop();
        int result = lOpd / rOpd;
        opdStack.push(result);
        cout<<"操作符:"<<opt<<" "<<"操作数:"<<lOpd<<" "<<rOpd<<endl;
    }
}

int Test::evaMidExpression(char *str)
{
    vector<string> tokens = preParse(str);
    int i=0;
    int size = tokens.size();

    stack<int> opdStack;     //存储操作数
    stack<string> optStack;   //存储操作符
    for(i=0;i<size;i++)
    {
        string token = tokens[i];
        if(token=="#"||token=="+"||token=="-"||token=="*"||token=="/")
        {
            if(optStack.size()==0)   //如果操作符栈为空
            {
                optStack.push(token);
            }
            else
            {
                int tokenPriority = getPriority(token);
                string topOpt = optStack.top();
                int topOptPriority = getPriority(topOpt);
                if(tokenPriority>topOptPriority)
                {
                    optStack.push(token);
                }
                else
                {
                    while(tokenPriority<=topOptPriority)
                    {
                        optStack.pop();
                        calculate(opdStack,topOpt);
                        if(optStack.size()>0)
                        {
                            topOpt = optStack.top();
                            topOptPriority = getPriority(topOpt);
                        }
                        else
                            break;

                    }
                    optStack.push(token);
                }
            }
        }
        else if(token=="(")
        {
            optStack.push(token);
        }
        else if(token==")")
        {
            while(optStack.top()!="(")
            {
                string topOpt = optStack.top();
                calculate(opdStack,topOpt);
                optStack.pop();
            }
            optStack.pop();
        }
        else   //如果是操作数，直接入操作数栈
        {
            opdStack.push(atoi(token.c_str()));
        }
    }
    while(optStack.size()!=0)
    {
        string topOpt = optStack.top();
        calculate(opdStack,topOpt);
        optStack.pop();
    }
    return opdStack.top();

}

void Test::TestMathExpression()
{
    char *str = "((3+5*2)+3)/5+(-6)/4*2+3";
    char *str1 = "((3+5*2)+3)/5";
    char *str2 ="(-6)/4*2";
    cout << Test::evaMidExpression(str) <<endl;
    cout << Test::evaMidExpression(str1) <<endl;
    cout << Test::evaMidExpression(str2) <<endl;
}

void Test::TestJosonCppArray()
{
    const char json_data[] =
            "{\"name\" : \"Tocy\", \"salary\" : 100, \"msg\" : \"work hard\", \
            \"files\" : [\"1.ts\", \"2.txt\"]}";

        Json::Reader reader;
        Json::Value root;
        // reader将Json字符串解析到root，root将包含Json里所有子元素
        if (!reader.parse(json_data, json_data + sizeof(json_data), root))
        {
            cerr << "json parse failed\n";
            return;
        }

        cout << "demo read from memory ---------\n";
        string name = root["name"].asString();
        int salary = root["salary"].asInt();
        string msg = root["msg"].asString();
        cout << "name: " << name << " salary: " << salary;
        cout << " msg: " << msg << endl;
        cout << "enter files: \n";
        Json::Value files = root["files"]; // read array here
        for (unsigned int i = 0; i < files.size(); ++i)
        {
            cout << files[i].asString() << " ";
        }
        cout << endl;
}

void Test::TestJsonCppFile()
{
        ifstream ifs;
        ifs.open("checkjson.json");
        if(ifs.is_open())
        {
            cerr << "file is open" << endl;
        }

        Json::Reader reader;
        Json::Value root;
        if (!reader.parse(ifs, root, false))
        {
            cerr << "parse failed \n";
            return;
        }

        bool name = root["success"].asBool(); // 实际字段保存在这里
        int age = root["statusCode"].asInt(); // 这是整型，转化是指定类型
}

void Test::TestJsonCppMem()
{
    const char json_data[] =
       "{\"name\" : \"Tocy\", \"salary\" : 100, \"msg\" : \"work hard\", \
       \"files\" : [\"1.ts\", \"2.txt\"]}";

    Json::Reader reader;
    Json::Value root;
    // reader将Json字符串解析到root，root将包含Json里所有子元素
    if (!reader.parse(json_data, json_data + sizeof(json_data), root))
    {
       cerr << "json parse failed\n";
       return;
    }

    cout << "demo read from memory ---------\n";
    string name = root["name"].asString();
    int salary = root["salary"].asInt();
    string msg = root["msg"].asString();
    cout << "name: " << name << " salary: " << salary;
    cout << " msg: " << msg << endl;
    cout << "enter files: \n";
    Json::Value files = root["files"]; // read array here
    for (unsigned int i = 0; i < files.size(); ++i)
    {
       cout << files[i].asString() << " ";
    }
    cout << endl << endl;
}

void Test::TestJsonCppWrite()
{
    writeMem();
    writeObject();
    writeArray();
}

void Test::writeMem()
{
    Json::Value root;
    Json::FastWriter writer;
    Json::Value person;

    person["name"] = "tocy";
    person["age"] = 1000;
    root.append(person);

    string json_file = writer.write(root);

    cout << "demo write json ==============\n";
    cout << json_file << endl;
}

void Test::writeObject()
{
    Json::Value root;
    Json::FastWriter writer;
    Json::Value person;

    person["name"] = "tocy";
    person["age"] = 1000;
    root.append(person);

    string json_file = writer.write(root);

    cout << "demo write json ==============\n";
    cout << json_file << endl;
}

void Test::writeArray()
{
    Json::Value root;
    Json::FastWriter writer;

    {
        Json::Value person;
        person["name"] = "Tocy";
        person["salary"] = 100;
        root[0] = person;
    }

    {
        Json::Value person;
        person["name"] = "Kit";
        person["salary"] = 89;
        root[1] = person;
    }

    root[2] = "a json note";

    string json_file = writer.write(root);
    cout << "demo write json ==============\n";
    cout << json_file << endl;

}

void Test::TestCurlFtp()
{
    curl_global_init(CURL_GLOBAL_ALL);
    CURL* curl = curl_easy_init();
    string strUrl ="https://gateway.ipfs.io/ipfs/QmbL4ygrUNEhVLwcpSTTDuMd33f7PZx3au1nDixAZHd43x";
    curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());

    if((fp = fopen("test.bat","w")) == NULL)
    {
        curl_easy_cleanup(curl);
        exit(1);
    }
    //CURLOPT_WRITEFUNCTION 将后继的动作交给write_data函数处理
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Test::writeData);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    exit(0);

}

size_t Test::writeData(void *ptr, size_t size, size_t nmemb, void *stream)
{

    int written = fwrite(ptr, size, nmemb, (FILE *)fp);
    return written;
}

void Test::TestCurlDown(string &strUrl,string&filename)
{
    CURLcode ret;

    curl_global_init(CURL_GLOBAL_ALL);
    CURL*curl = curl_easy_init();
    curl_easy_setopt(curl,CURLOPT_URL,strUrl.c_str());
    curl_easy_setopt(curl,CURLOPT_USERPWD,"username:password");
    ret = curl_easy_setopt(curl,CURLOPT_WRITEDATA,filename.c_str());
    ret = curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,Test::writeData);

    curl_easy_setopt(curl,CURLOPT_TRANSFERTEXT,1);
    curl_easy_setopt(curl,CURLOPT_VERBOSE,1);
    ret = curl_easy_setopt(curl,CURLOPT_VERBOSE,1);

    curl_easy_cleanup(curl);
    curl_global_cleanup();

}

void Test::TestCurlUpload(const string&strFile,const string&strUrl)
{
    CURLcode ret;
    curl_global_init(CURL_GLOBAL_ALL);
    CURL*curl =curl_easy_init();
    FILE *fpUpload;
    fopen(strFile.c_str(),"wb");
    curl_easy_setopt(curl,CURLOPT_UPLOAD,strUrl.c_str());
    curl_easy_setopt(curl,CURLOPT_USERPWD,"username:password");

    curl_easy_setopt(curl,CURLOPT_UPLOAD,1L);
    curl_easy_setopt(curl,CURLOPT_FTP_CREATE_MISSING_DIRS,CURLFTP_CREATE_DIR);
    ret = curl_easy_setopt(curl,CURLOPT_READDATA,fpUpload);
    curl_easy_setopt(curl,CURLOPT_INFILESIZE_LARGE,sizeof(fpUpload));
    ret = curl_easy_setopt(curl,CURLOPT_READFUNCTION,Test::readFunction);
    curl_easy_setopt(curl,CURLOPT_FTP_RESPONSE_TIMEOUT,60000);

    curl_easy_setopt(curl,CURLOPT_TRANSFERTEXT,1);
    curl_easy_setopt(curl,CURLOPT_BUFFERSIZE,200);

    curl_easy_setopt(curl,CURLOPT_VERBOSE,1);
    ret = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    fclose(fpUpload);

}

size_t Test::readFunction(void *buffer, size_t size, size_t count, FILE *stream)
{

    return fread(buffer,size,count,stream);

}
