#include <iostream>
// for the purpose of reading the command line arguments
#include <unistd.h>
#include <vector>
#include <sstream>
#include <cstring>
#include <string>
#include <stdbool.h>
#include <math.h>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
using namespace std;

// declare a struct to maintain the operations order in a vector
struct operations{
char dir;
int numBits;
operations(int _numBits,char _dir){
dir=_dir;
numBits=_numBits;
}
};

//define a class with the member functions and member variables to store a binary digit and perform shift operations on the it.

class BinaryManip{
    private:
// boolean for printing shifted value
    bool print;
// decimal value stored for printing
    string decimalPrinting;
// vector to hold the binary data given from the command line
    vector <bool> binaryData;
// binary data size
    int dataSize;

// vector to hold the operations to be performed as per given order in the command line argument
   vector <operations> operationsOrder;
// variable to hold the bit that should be inserted after the shift operation
   bool vacantBit;
// function to perform the shift left operation
    void shiftLeft(int numOfBits){
        for(int i=0; i<numOfBits;i++){
            binaryData.push_back(vacantBit);
            }
        binaryData.erase(binaryData.begin(),binaryData.begin()+numOfBits);
    }
// function to perform the shift right operations
    void shiftRight(int numOfBits){
        for(int i=0; i<numOfBits;i++){
            binaryData.insert(binaryData.begin(),vacantBit);
            }
        binaryData.erase(binaryData.begin()+dataSize,binaryData.end());
    }
// function for binary addition
    void binaryAdd(vector<bool> _binaryData1,vector<bool> _binaryData2,vector<bool> & _binaryData3,int &carryGenerated){
    bool c=0;
    vector<bool> refVector(_binaryData1.size());
    vector <bool>::reverse_iterator b2it=_binaryData2.rbegin();
    for(vector<bool>::reverse_iterator it=_binaryData1.rbegin();it!=_binaryData1.rend();++it){
                bool temp=*b2it++;
                bool temp1=*it;
                bool result=temp^temp1^c;
                c=((temp&temp1)|(temp&c)|(temp1&c));
                refVector.push_back(result);
    }
    vector <bool>::iterator reversRef=_binaryData3.begin();
    for(vector<bool>::reverse_iterator it=refVector.rbegin();it!=refVector.rend();++it){
            *reversRef=*it;
            reversRef++;
    }
    carryGenerated=c;
    }
// function for performing the 2s complement
    void twsComplement(vector<bool> & _binaryData){
        int carryGenerated;
     for(vector<bool>::iterator it=_binaryData.begin();it!=_binaryData.end();++it){
            *it=!*it;
        }
    vector<bool> Suport2SComp(_binaryData.size());
    for(int i=0;i<_binaryData.size()-1;i++){
            Suport2SComp.push_back(0);
        }
    Suport2SComp.push_back(1);
    vector<bool> result2sComplement(_binaryData.size());
    binaryAdd(_binaryData,Suport2SComp,result2sComplement,carryGenerated);
    _binaryData=result2sComplement;
    }

//function to convert from int to binary
    string InttoBin(int num){
    int absNum=abs(num);
    string binary="";
    while(absNum!=0){
        stringstream ss2;
        ss2 << (absNum%2);
        binary+=ss2.str();
        absNum=absNum/2;
    }
    reverse(binary.begin(),binary.end());
    return binary;
    }

//function to convert from binary to int
    string BinarytoInt(string bin){
        reverse(bin.begin(),bin.end());
        double decimal = 0;
        for(int counter = 0; counter <bin.length(); counter++ ){
            if(bin.c_str()[counter] == '1')
            decimal += pow(2, counter);
            }
        stringstream ss2;
        ss2 << (decimal);
        return ss2.str();
    }
// function to convert from hex to binary
//function to convert from binary to hex

    public:
//check for negative integer
    bool negativeFlag=false;
//initialize
    BinaryManip(string _binaryData,int _dataSize,vector<operations> _operationsOrder,bool _vacantBit,bool _print){
	print= false;
	vacantBit=false;
        string data(_binaryData);
        string dataType;
        string::iterator detectDecOrHex=data.end()-1;
        dataType=*detectDecOrHex;
        if(dataType=="D"||dataType=="d"){
            data=data.substr(0,data.length()-1);
            // get the binary data
            int convertedData=atoi(data.c_str());
            if(convertedData<0){
                negativeFlag=1;
                data=  InttoBin(atoi(data.substr(1).c_str()));
            }
            else{
                data=  InttoBin(convertedData);
            }
        }
        for(std::string::iterator it = data.begin(); it != data.end(); ++it) {
        if(*it=='1'){
                 binaryData.push_back(true);
            }
        else if(*it=='0'){
                binaryData.push_back(false);
           }
        }
        dataSize=_dataSize;
        operationsOrder=_operationsOrder;
        vacantBit=_vacantBit;
        print=_print;
    }
    BinaryManip(vector<bool> _binaryData,int _dataSize,vector<operations> _operationsOrder,bool _vacantBit,bool _print){
	print= false;
	vacantBit=false;
        binaryData=_binaryData;
        dataSize=_dataSize;
        operationsOrder=_operationsOrder;
        vacantBit=_vacantBit;
        print=_print;
    }
// get the size of binary data
    int getSize(){
    return binaryData.size();
    }

// set the size
    void setSize(int _dataSize){
        if(binaryData.size()!=_dataSize){
            if(binaryData.size()<_dataSize){
                    int numOfInsertions=_dataSize-binaryData.size();
                    for (int i=0;i<numOfInsertions;i++){
                         binaryData.insert(binaryData.begin(),0);
                    }
            }
            dataSize=_dataSize;
        }
    }
// if necessary do tws complement
    void do2scomplement(){
        if(negativeFlag==1){
            decimalPrinting="-"+decimalPrinting;
            twsComplement(binaryData);
        }
    }

// function to start the process of doing operations mentioned in the command line argument
    int performOperations(){
        for (int i=0;i<operationsOrder.size();i++){
            operations currentOp=operationsOrder[i];
            currentOp.dir=='r'?shiftRight(currentOp.numBits):shiftLeft(currentOp.numBits);
        }

if(negativeFlag==1){
      vector<bool> temp=binaryData;
      twsComplement(temp);
       stringstream ss2;
        for(vector<bool>::iterator iter = temp.begin(); iter != temp.end(); ++iter){
                ss2<<*iter;
         }
        decimalPrinting="-"+BinarytoInt(ss2.str());
}
else{
stringstream ss2;
        for(vector<bool>::iterator iter = binaryData.begin(); iter != binaryData.end(); ++iter){
                ss2<<*iter;
         }
        decimalPrinting=BinarytoInt(ss2.str());
}

     }
     // print the operated data
     void printing(string form){
         if(print){
            for(vector<bool>::iterator iter = binaryData.begin(); iter != binaryData.end(); ++iter){
                cout<<*iter;
            }
            if(form=="d"){
                 //string str(binaryData.begin(), binaryData.end());
                 cout<<"("<<decimalPrinting<<")";
            }
            else if(form=="h"){
                    int result=atoi(decimalPrinting.c_str());
                    cout << setbase(16);
                    cout<<"("<<result<<")";
            }
            else{
            }
            cout<<endl;
        }
     }
    //operator overloading
    //for he sum of the two binary numbers
    BinaryManip operator+ (BinaryManip b2){
        int carryGenerated;
    BinaryManip bm(this->binaryData,this->dataSize,this->operationsOrder,this->vacantBit,this->print);
    binaryAdd(this->binaryData,b2.binaryData,bm.binaryData,carryGenerated);

    if(this->negativeFlag || b2.negativeFlag ){
    if(!carryGenerated ||(this->negativeFlag && b2.negativeFlag) ){
      vector<bool> temp=bm.binaryData;
      twsComplement(temp);
       stringstream ss2;
        for(vector<bool>::iterator iter = temp.begin(); iter != temp.end(); ++iter){
                ss2<<*iter;
         }
        bm.decimalPrinting="-"+BinarytoInt(ss2.str());
    }
    else{
        stringstream ss2;
        for(vector<bool>::iterator iter = bm.binaryData.begin(); iter != bm.binaryData.end(); ++iter){
                ss2<<*iter;
         }
        bm.decimalPrinting=BinarytoInt(ss2.str());
    }

    }
    else{
         if(carryGenerated){
            bm.binaryData.insert(bm.binaryData.begin(),carryGenerated);
         }
        stringstream ss2;
        for(vector<bool>::iterator iter = bm.binaryData.begin(); iter != bm.binaryData.end(); ++iter){
                ss2<<*iter;
         }
        bm.decimalPrinting=BinarytoInt(ss2.str());
    }
    return bm;
    }
    //for he difference of the two binary numbers
    BinaryManip operator- (BinaryManip b2){
    int carryGenerated;
    BinaryManip bm(this->binaryData,this->dataSize,this->operationsOrder,this->vacantBit,this->print);
    twsComplement(b2.binaryData);
    binaryAdd(this->binaryData,b2.binaryData,bm.binaryData,carryGenerated);
    if((!carryGenerated||(this->negativeFlag && !b2.negativeFlag)) && !(! this->negativeFlag && b2.negativeFlag) ){
      vector<bool> temp=bm.binaryData;
      twsComplement(temp);
       stringstream ss2;
        for(vector<bool>::iterator iter = temp.begin(); iter != temp.end(); ++iter){
                ss2<<*iter;
         }
        bm.decimalPrinting="-"+BinarytoInt(ss2.str());
    }
    else{
        stringstream ss2;
        for(vector<bool>::iterator iter = bm.binaryData.begin(); iter != bm.binaryData.end(); ++iter){
                ss2<<*iter;
         }
        bm.decimalPrinting=BinarytoInt(ss2.str());
    }
    return bm;
    }

} ;

 int max(int a0, int a1) { return (a0 < a1 ? a1 : a0);}
 int min(int a0, int a1) { return (a0 < a1 ? a0 : a1);}
int main(int argc, char *argv[])
{
    try{
// boolean for printing shifted value
    bool print= false;
    string printType;
// vector to hold the binary data given from the command line
    string binaryData;
    string binaryData1;
// binary data size
    int dataSize;
    int dataSize1;
// vector to hold the operations to be performed as per given order in the command line argument
   vector <operations> operationsOrder;
   vector <operations> operationsOrder1;
// variable to hold the bit that should be inserted after the shift operation
   bool vacantBit=false;
// operation to be performed
    string operation="";
    string errorData="";
	string ShowIn="b";
    int c;
    while ((c = getopt(argc, argv, ":i:s:r:l:I:S:R:L:v:o:dhp")) != -1) {
        switch (c)
        {
        case 'i':{
            if(optarg[strlen(optarg)-1]=='D'||optarg[strlen(optarg)-1]=='d'){
                try{
                string validateStr(optarg);
                validateStr=validateStr.substr(0,validateStr.length()-1);
                int testInt=atoi(validateStr.c_str());
                string str(optarg);
                binaryData=str;
                }
                catch(exception const & e){
                    cout<<"error : " << "Input binary data(-i) is not in correct format.\n";
                    return -1;
                }
            }
            else{
            int validateData=1;
            for(int i=0; i< strlen(optarg); i++){
                if(optarg[i]=='0'||optarg[i]=='1'){}
                else{
                   validateData=0;
                }
            }
            if(validateData){
                //bm.binaryData(inputData.begin(),inputData.end());
                string str(optarg);
                binaryData=str;
            }
            else{
                errorData += "Input binary data(-i) is not in correct format.\n";
            }

            }
            break;
        }
        case 'I':{
            if(optarg[strlen(optarg)-1]=='D'||optarg[strlen(optarg)-1]=='d'){
                try{
                string validateStr(optarg);
                validateStr=validateStr.substr(0,validateStr.length()-1);
                int testInt=atoi(validateStr.c_str());
                string str(optarg);
                binaryData1=str;
                }
                catch(exception const & e){
                    cout<<"error : " << "Input binary data(-I) is not in correct format.\n";
                    return -1;
                }
            }
            else{
            int validateData=1;
            for(int i=0; i< strlen(optarg); i++){
                if(optarg[i]=='0'||optarg[i]=='1'){}
                else{
                   validateData=0;
                }
            }
            if(validateData){
                //bm.binaryData(inputData.begin(),inputData.end());
                string str(optarg);
                binaryData1=str;
            }
            else{
                errorData += "Input binary data(-I) is not in correct format.\n";
            }

            }
            break;
        }
        case 's':{
            stringstream ss(optarg);
            int isNumeric;
            ss>> isNumeric;
            if(!ss.fail() && isNumeric>0){
                dataSize=isNumeric;
              }
            else{
               errorData += "Input size(-s) of the given data should be valid numeric greater than zero.\n";
              }
            break;
        }
       case 'S':{
            stringstream ss(optarg);
            int isNumeric;
            ss>> isNumeric;
            if(!ss.fail() && isNumeric>0){
                dataSize1=isNumeric;
              }
            else{
               errorData += "Input size(-S) of the given data should be valid numeric greater than zero.\n";
              }
            break;
        }

        case 'r':{
            stringstream ss(optarg);
            int isNumeric;
            ss>> isNumeric;
            if(!ss.fail()&& isNumeric>=0){
                    operations op(isNumeric,'r');
                    operationsOrder.push_back(op);
              }
            else{
               errorData += "shift right bits(-r) should be valid numeric.\n";
              }
            break;
        }
        case 'R':{
            stringstream ss(optarg);
            int isNumeric;
            ss>> isNumeric;
            if(!ss.fail()&& isNumeric>=0){
                    operations op(isNumeric,'r');
                    operationsOrder1.push_back(op);
              }
            else{
               errorData += "shift right bits(-R) should be valid numeric.\n";
              }
            break;
        }
        case 'l':{
            stringstream ss(optarg);
            int isNumeric;
            ss>> isNumeric;
            if(!ss.fail()&& isNumeric>=0){
                    operations op(isNumeric,'l');
                    operationsOrder.push_back(op);
              }
            else{
               errorData += "shift left bits(-l) should be valid numeric.\n";
              }
            break;
        }
        case 'L':{
            stringstream ss(optarg);
            int isNumeric;
            ss>> isNumeric;
            if(!ss.fail()&& isNumeric>=0){
                    operations op(isNumeric,'l');
                    operationsOrder1.push_back(op);
              }
            else{
               errorData += "shift left bits(-L) should be valid numeric.\n";
              }
            break;
        }

        case 'v':{
            stringstream ss(optarg);
            bool isBool;
            ss>> isBool;
            if(!ss.fail()){
                vacantBit=isBool;
              }
            else{
               errorData += "vacant filler(-v) should be a valid bit. Either 1 or 0 can only be accepted.\n";
              }
            break;
        }
        case 'o':{
                string str(optarg);
                if(str=="+"||str=="-"){
                operation=str;
                }
                else{
                  errorData += "either + or - operators can only be accepted.\n";
                }

            break;
        }
         case 'd':
            printType="d";
            break;
        case 'h':
            printType="h";
            break;
        case 'p':
            print=true;
            break;
        case ':':
            errorData +="One of the required arguments are missing in the syntax.\n";
            break;
        case '?':
        default:
            //cout<<argv[optind];
            optind++;
            break;
        }
    }
    if(errorData!=""){
        cerr<<errorData;
        return -1;
    }
    else{
    BinaryManip bm(binaryData,dataSize,operationsOrder,vacantBit,print);
    BinaryManip bm1(binaryData1,dataSize1,operationsOrder1,vacantBit,print);
    // make the sizes equal before performing the operatons
    int maxSize=max(dataSize, max(dataSize1, max(bm.getSize(), bm1.getSize())));
    bm.setSize(maxSize);
    bm1.setSize(maxSize);
    dataSize=maxSize;
    dataSize1=maxSize;
    //perform twos complement if necessary
    bm.do2scomplement();
    bm1.do2scomplement();
    //performing shifting operations
    bm.performOperations();
    bm1.performOperations();
//performing the operations
    BinaryManip bm2(binaryData,dataSize,operationsOrder,vacantBit,print);
    bm2.setSize(maxSize);
	int operationSet=0;    
	if(operation=="+"){
     bm2=bm+bm1;
	operationSet=1;
    }
    else if(operation=="-"){
    bm2=bm-bm1;
	operationSet=1;
    }
    if(print){
        bm.printing(printType);
        bm1.printing(printType);
	if(operationSet){
        bm2.printing(printType);
	}
    }
    return 0;
     }
    }
    catch(exception& e){
    cerr << e.what() << '\n';
    return -1;
  }
}
