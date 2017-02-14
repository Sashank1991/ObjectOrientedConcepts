#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <iterator>

using namespace std;
//function declaration for reading the file
void FunRead(string strFileName);
//function declaration for writing he file
void FunWrite(string strFileName,string strData, int intNumPrints);
// function to convert string to upper case
string StringToUpper(string strToConvert);

//starting of the program
int main(int intNumArg, char* chrArgs[] )
{
    // variables for storing the command arguments
    string strReadOrWrite;
    string strFileName;
    string strFileContent;
    string strNumPrints;
    // processing the data from command arguments and filling into their corresponding variables.
    try{
        for(int i=1; i<intNumArg;i++){
            string strCurrVal=StringToUpper(chrArgs[i]);
            if(strCurrVal=="-R" || strCurrVal=="-W"){
                strReadOrWrite=strCurrVal;
            }
            else if(strCurrVal=="-F" && i+1<intNumArg ){
                string tempValue=StringToUpper(chrArgs[i+1]);
                if(tempValue !="-W" &&tempValue !="-R" &&tempValue !="-F" &&tempValue !="-P" &&tempValue !="-N"){
                strFileName=chrArgs[i+1];
                }
            }
            else if(strCurrVal=="-P" && i+1<intNumArg){
                string tempValue=StringToUpper(chrArgs[i+1]);
                if(tempValue !="-W" &&tempValue !="-R" &&tempValue !="-F" &&tempValue !="-P" &&tempValue !="-N"){
                strFileContent=chrArgs[i+1];
                }
            }
            else if(strCurrVal=="-N"&& i+1<intNumArg){
                string tempValue=StringToUpper(chrArgs[i+1]);
                if(tempValue !="-W" &&tempValue !="-R" &&tempValue !="-F" &&tempValue !="-P" &&tempValue !="-N"){
                strNumPrints=tempValue;
                }

              }
        }
        // validating the data and making call to read or write functions
        if (StringToUpper(strReadOrWrite)=="-W"){
            if(strFileName.length()>0){
                    if (strFileContent.length()>0){
                        if (strNumPrints.length()>0){
                            stringstream ss(strNumPrints);
                            int isNumeric;
                            ss>> isNumeric;
                            if(!ss.fail()){
                                    FunWrite(strFileName,strFileContent,isNumeric);
                                    cout<< "Loaded given data on to the file. \n";
                            }
                            else{
                                cerr<< " -n value must be a integer.\n";
                            }
                        }
                        else{
                           cerr<< "Please give minimum 1 number of prints for the given data.\n";
                        }
                    }
                    else{
                      cerr<< "No file content specified for writing.\n";
                    }
            }
            else{
                cerr<< "No file name specified for writing.\n";
            }
        }
        else if (StringToUpper(strReadOrWrite)=="-R"){
            if(strFileName.length()>0){
                FunRead(strFileName);
            }
            else{
                cerr<< "No file name specified for reading.\n";
            }
        }
        else{
            cerr << "Input arguments does not specify either read or write.\n";
        }
    }
    catch(exception ex){
    cerr<<ex.what();
    }
    return 0;
}
//to read a file from the location provided in the command line arguments.
void FunRead(string strFileName){
  string line;
  ifstream myfile;
  myfile.open(strFileName.c_str());
    if(myfile.fail()){
        cerr << "Unable to open file, Please Check the file name.";
    }
    else{
        myfile>>noskipws;
       istream_iterator<char> eos;
       istream_iterator<char> currentChar (myfile);
        while(currentChar !=eos){
            cout << *currentChar;
            ++currentChar;
        }
        myfile.close();
    }
    cout << "\n";
}
//To write the given data n number of times provided in the command line arguments
void FunWrite(string strFileName,string strData, int intNumPrints){
 ofstream myfile (strFileName.c_str());
 myfile<<noskipws;
  if (myfile.is_open())
  { int i=0;
    while(i<intNumPrints){
        stringstream c(strData);
        c<<noskipws;
        istream_iterator<char> eos;
        istream_iterator<char> currentChar (c);
        while(currentChar !=eos){
            istream_iterator<char> ref=currentChar;
            if(*currentChar=='\\'){
                if(*(++currentChar)=='n'){
                    myfile<<"\n";
                }
                else if(*(currentChar)=='t'){
                    myfile<<"\t";
                }
                else{
                    myfile << *ref<<*currentChar;
                }
            }
            else{
            myfile << *currentChar;
            }
            ++currentChar;
        }
        i++;
    }
    myfile.close();
  }
  else cout << "Unable to open file";
}

// to convert a string into upper case
string StringToUpper(string strToConvert)
{
    transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::toupper);

    return strToConvert;
}
