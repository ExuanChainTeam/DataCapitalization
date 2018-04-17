#include "FHE.h"
#include "EncryptedArray.h"
#include <NTL/lzz_pEXFactoring.h>
#include <iostream>
#include <stack>
#include <string>
#include <typeinfo>
#include <climits>
#include <math.h>
#include <fstream>

using namespace std;

stack<Ctxt>  theStack;
FHEcontext *context;
FHESecKey* secretKey;
FHEPubKey* publicKey;
ZZX G;
void setupHELib();
bool isOp(string token);
void evaluate(char op);
void greeting()
{
    cout << "welcome to use homomorphic encrytion calculator" << endl;
    cout << "input expresion ini reverse polish notation" << endl;
    cout << "input q to quit" << endl;
}
void test_poly()
{
    double array [] = { -1.0, 5.0, -2.0, 1.0 };
    double result;
   // result = poly(2.0, 3, array);
    cout << "The polynomial:x**3 - 2.0x**2 + 5x - 1 at 2.0 is %lf \n" << result << endl;
}

int main (int argc,char*argv[])
{
    ofstream  filein;
    filein.open("context.txt",ios::trunc);
    string token ;
    greeting();
    cout << "long max:" << LONG_MAX <<endl;

    //setup FHE
    setupHELib();
    EncryptedArray ea(*context,G);
    filein << *context << endl;
    //cout << "context content:" << *context << endl;
    filein.close();
    //Main loop
    int count =0;
    long inputNum=0;
   // cout << "init theStack size is:" << endl;
    ZZX const_poly;
    ZZX const_poly1;
    while(true)
    {
        if(count < 2)
        {
            cin >> inputNum;
            count ++;
        }
        else
        {
            cin >> token;
        }
        if(token[0] == 'q')
        {
            break;
        }
        else if(isOp(token))
        {
            if(theStack.size() < 2)
            {
                cout <<"not enough numbers on the stack"<< endl;
            }
            else
            {
                //perform the operation
                evaluate(token[0]);
            }
        }
        else
        {
            //should be a number ,push it
            //encrpt it first
            Ctxt& c = *(new Ctxt(*publicKey));
            NewPlaintextArray p(ea);
            encode(ea,p,inputNum);
           /* if(count == 0)
                ea.encode(const_poly,p);
            else
                ea.encode(const_poly1,p);*/
            //encode(ea,p,atoi(token.data()));
            //p.(atoi(token.data()));
            ea.encrypt(c,*publicKey,p);
            //theStack.push(atoi(token.data()));
            theStack.push(c);
        }
    }

    filein.open("publictext.txt",ios::trunc);
    filein << *publicKey <<endl;
    filein.close();
    //cout << "publicKey is :" << *publicKey << endl;
    NewPlaintextArray p(ea);
  //  cout << "theStack size is :" << theStack.size() << endl;
  //   cout << "theStack type is :" << typeid(theStack.top()).name() << endl;


    ea.decrypt(theStack.top(),*secretKey,p);
    filein.open("ciphertext.txt",ios::trunc);
    filein << theStack.top() <<endl;
    filein.close();
    filein.open("secretKey.txt",ios::trunc);
    filein << *secretKey <<endl;
    filein.close();

    //cout << "ciphertext is: " << theStack.top() << endl;
    //cout << "secretKey is: " << *secretKey << endl;
    cout << "the answer is:";
    vector<long> veclong;
    vector<ZZX> vecZZX;
    decode(ea,vecZZX,p);
    filein.open("ZZX.txt",ios::trunc);
    for(int i =0;i<vecZZX.size();i++)
    {
        filein << vecZZX[i] << endl;
    }
    p.print(cout);
    cout << endl;
   // filein.close();
    return 0;
}

bool isOp(string token)
{
    return (token[0] == '+' || token[0] == '-' || token[0] == '*');
}
void evaluate(char op)
{
    Ctxt *op1,*op2;
    switch (op) {
    case '+':
        op1 = new Ctxt(theStack.top());
        theStack.pop();
        op2 = new Ctxt(theStack.top());
        theStack.pop();
        (*op1) += (*op2);
        
        theStack.push(*op1);
        break;
    case '-':
        op1 = new Ctxt(theStack.top());
        theStack.pop();
        op2 = new Ctxt(theStack.top());
        theStack.pop();
        (*op1) -= (*op2);
        theStack.push(*op1);
        break;
    case '*':
        op1 = new Ctxt(theStack.top());
        theStack.pop();
        op2 = new Ctxt(theStack.top());
        theStack.pop();
        (*op1) *= (*op2);
        theStack.push(*op1);
    default:
        break;
    }
}


void setupHELib()
{
    long p = 2 ;//101;//10021801547;//101;
    long r= 31;
    long L=8;//2,3,5,7
    long c=2;
    long k=80;
    long s =0;
    long d=2;
    long w=64;
    unsigned long m=FindM(k,L,c,p,d,s,0);
   // cout << "max long " << LONG_MAX <<endl;

    vector<long> gens1, ords1;

    cout << "p is :" << p << endl;
    cout << "m is :" << m << endl;
    context = new FHEcontext(m,p,r);
    buildModChain(*context,L,c);
    G = context->alMod.getFactorsOverZZ()[0];

    secretKey = new FHESecKey(*context);
    publicKey = secretKey;

    secretKey->GenSecKey(w);
    addSome1DMatrices(*secretKey);

}
