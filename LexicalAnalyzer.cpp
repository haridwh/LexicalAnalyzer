#include <iostream>
#include <vector>
using namespace std;

void parser(string input, vector<string> &lexic);
int getToken(string lexic);

int main(){
  string input;
  vector<string> lexic;
  int token;
  cout<<"Input : ";
  getline(cin, input);
  parser(input,lexic);
  cout<<"Output : ";
  for (int i=0; i<lexic.size();i++){
    token = getToken(lexic[i]);
    if (token!=0) {
      cout<<token<<" ";
    }else{
      cout<<"error";
      i=lexic.size();
    }
  }
  cout<<endl;
}

void parser(string input, vector<string> &lexic){
  string kata="";
  for (int i=0; i<input.length(); i++) {
    if (input[i]==' ') {
      lexic.push_back(kata);
      kata="";
    }else if (input[i]=='(') {
      if (kata != "") {
        lexic.push_back(kata);
        kata="";
      }
      lexic.push_back(string(1,input[i]));
    }else if (input[i]==')') {
      if (kata != "") {
        lexic.push_back(kata);
        kata="";
      }
      lexic.push_back(string(1,input[i]));
    }else{
      kata+=input[i];
    }
  }
  if (kata!="") {
    lexic.push_back(kata);
  }
}

int getToken(string lexic){
  if (lexic[0]=='p' || lexic[0]=='q' || lexic[0]=='r' || lexic[0]=='s') {
    return 1;
  }else if(lexic[0]=='n' && lexic[1]=='o' && lexic[2]=='t'){
    return 2;
  }else if(lexic[0]=='a' && lexic[1]=='n' && lexic[2]=='d'){
    return 3;
  }else if(lexic[0]=='o' && lexic[1]=='r'){
    return 4;
  }else if (lexic[0]=='x' && lexic[1]=='o' && lexic[2]=='r') {
    return 5;
  }else if (lexic[0]=='i' && lexic[1]=='f') {
    if (lexic.length()==3) {
      if (lexic[2] =='f') {
        return 8;
      }
    }else{
      return 6;
    }
  }else if (lexic[0]=='t' && lexic[1]=='h' && lexic[2]=='e' && lexic[3]=='n') {
    return 7;
  }else if (lexic[0]=='(') {
    return 9;
  }else if (lexic[0]==')') {
    return 10;
  }else{
    return 0;
  }
}
