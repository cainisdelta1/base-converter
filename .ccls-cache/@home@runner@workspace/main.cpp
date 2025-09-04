// todo: add shifting fractional numbers to a higher base
#include <iostream>
#include <cstring>// todo: add shifting fractional numbers to a higher base
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

void split(const string& str, const string& delim, vector<string>& parts) { // https://stackoverflow.com/questions/289347/using-strtok-with-a-stdstring
  size_t start, end = 0;
  while (end < str.size()) {
    start = end;
    while (start < str.size() && (delim.find(str[start]) != string::npos)) {
      start++;  // skip initial whitespace
    }
    end = start;
    while (end < str.size() && (delim.find(str[end]) == string::npos)) {
      end++; // skip to end of word
    }
    if (end-start != 0) {  // just ignore zero-length strings.
      parts.push_back(string(str, start, end-start));
    }
  }
}

string downShiftNum(int sBase,int eBase, int num){
  string bufStr="";
  int bufNum=0;
  while(num>0){
    bufNum = num % eBase; // take remainder from dividing by the base you want it in
    bufStr.append(to_string(bufNum)); // appends num to end of string
    num/=eBase;
  }
  reverse(bufStr.begin(), bufStr.end()); // reverses string because you cant append to the beginning 
  return bufStr;
}

string upShiftNum(int sBase, int eBase, int num){
  cout << endl;
  int endNum = 0;
  int digit;
  for(int i = 0; num > 0; i++){
    digit = num%10; // gives the last digit of the num
    endNum += digit*(pow(sBase,i));
    num/=10;
  } // converts num to base 10
  string endStr = downShiftNum(10, eBase,endNum); // convert from base 10 to ending base
  return endStr;
}

float fraction(float num){
  float fract = 0,p;
  fract = modf(num,&p);
  return fract;
}

string downShiftFract(int sBase, int eBase, float num){
  float p;
  string bufInt="";
  int i = 0;
  while(num!=0){
    num*=eBase; // multiplying number by the base you want
    if(num>=1) bufInt.append(to_string((int)num));
    else bufInt.append("0");
    //bufInt.append(); // move num over
    //bufInt+=(int)num; // adds the whole number (1 or 0) to the end of number in the new base
    num = modf(num,&p); // removes that whole number again
    if(i>100) break;
    i++;
  }
  return bufInt;
}

/*std::string downShiftFract(int sBase, int eBase, float num){
  float p;
  std::string bufInt="";
  int i = 0;
  while(num<1){
    num*=eBase;
    if(num>0){
      bufInt+="0";
      bufInt+=(char)(int)num;
      num = modf(num,&p);
    }
    else{
      bufInt+="0";
    }
    if(i>100) break;
    i++;
  }
  return bufInt;
}*/

float upShiftFract(int sBase, int eBase, string sNum, int digits){
  string sNumFract = ".";
  sNumFract.append(sNum);
  float num = stof(sNumFract);
  float buf=0;
  int bufInt=0;
  cout<<endl;
  for(int i = 0; i < digits; i++){
    num*=10;
    bufInt=num;
    buf+=(float)((sNum[i]-'0')*pow(sBase,-(i+1)));
  }
  return buf;
}

int main() {
  cout << "what base to start? " << endl;
  int sBase;
  cin >> sBase;
  cout << "what base to end? " << endl;
  int eBase;
  cin >> eBase;
  cout << "what number to convert? " << endl;
  string sNum;
  cin >> sNum;
  vector<string> parts;
  split(sNum, ".", parts);
  int sNumInt = stoi(sNum);
  if(stoi(sNum) == stof(sNum)){
    if(sBase<eBase){
      cout << upShiftNum(sBase,eBase,sNumInt);
    }
    else {
      cout << downShiftNum(sBase,eBase, sNumInt);
    }
  }
  else{
    float sNumF = stof(sNum);
    if(sBase<eBase){
      int digits = parts[1].length();
      cout << "digits: " << digits << endl;
      vector<string>parts2;
      split(to_string(upShiftFract(sBase, eBase, parts[1],digits)),".", parts2);
      int newBaseDigits = parts2[1].length();
      cout << upShiftNum(sBase, eBase, sNumInt) << "." << (upShiftFract(sBase, eBase, parts[1],digits)*pow(eBase,newBaseDigits));
    }
    else {
      cout << downShiftNum(sBase,eBase,sNumInt) << "." << downShiftFract(sBase,eBase, fraction(sNumF));
    }
  }
}