#include <iostream>
// for the purpose of reading the command line arguments
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <new>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

int evaluateExpression(char *expression){
stack <int> stk;
vector <string> vec;
string str(expression);
size_t pos=0;
string delimiter=",";
while((pos=str.find(delimiter)) != str.npos){
	vec.push_back(str.substr(0,pos));
	str.erase(0,pos+delimiter.length());
}
vec.push_back(str.substr(0,str.length()));

for(vector<string>::iterator itr=vec.begin();itr!=vec.end();++itr){
	string temp=*itr;
	int oprand1=0;
	int oprand=0;
	int result=0;
	if(temp=="+"){
	oprand1=stk.top();
	stk.pop();	
	oprand=stk.top();
	stk.pop();
	result=oprand+oprand1;
	stk.push(result);	
	}
	else if(temp=="-"){
	oprand1=stk.top();
	stk.pop();	
	oprand=stk.top();
	stk.pop();
	result=oprand-oprand1;
	stk.push(result);
	}
	else if(temp=="*"){
	oprand1=stk.top();
	stk.pop();	
	oprand=stk.top();
	stk.pop();
	result=oprand*oprand1;
	stk.push(result);
	}
	else if(temp=="/"){
	oprand1=stk.top();
	stk.pop();	
	oprand=stk.top();
	stk.pop();
	result=oprand/oprand1;
	stk.push(result);
	}
	else{
		try{
			stk.push(atoi(temp.c_str()));
		}
		catch(exception & e){
			return 1;
		}
	}
}
cout<<stk.top()<<endl;
return 0;
}

int main(int argc, char *argv[])
{
    try{
	char *evalexp="";
    int c;
    while ((c = getopt(argc, argv, ":e:")) != -1) {
        switch (c)
        {
        case 'e':{
	        evalexp= new char[sizeof(optarg)];
		evalexp=optarg;
        	break;
        }
        case '?':
        default:
            cerr<<"Invalid arguments"<<endl;
            return -1;
            break;
        }
    }
    if(evalexp==""){
        cout<<"please provide with an evaluation expression. 			\n";
        return -1;
    }
    else{
	int val= evaluateExpression(evalexp);
		if(val) {
			cerr<< "Please provide evaluation 				expression in correct format."<< endl;
			return -1;
			}
		else{
			return 0;			
			}   
	}
    }
    catch(exception& e){
    cerr << e.what() << '\n';
    return -1;
  }
}
