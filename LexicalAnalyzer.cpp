#include <iostream>
#include <vector>


using namespace std;

/**
  *Digunakan untuk membuat inputan user menjadi lowcase, sehingga inputan kapital atau tidak dapat diterima
  *oleh program
  *
  *@param string input, inputan dari user
  *@return string input, inputan user yang sudah diubah ke huruf kecil semua
  */
string lowcase(string input);

/**
  *Digunakan untuk melakukan trim, sehingga tidak ada space yang berlebih
  *misal input "    if     p then     q   ", maka setelah ditrim hasilnya akan menjadi "if p then q"
  *
  *@param string input, inputan dari user
  *@return string result, inputan user yang sudah ditrim
  */
string trim(string input);

/**
  *Digunakan untuk memparser inputan, dan menyimpannya ke dalam vector lexic
  *misal input "if p then", setelah diparser maka isi vector menjadi {"if","p","then"}
  *
  *@param string input, hasil inputan user yang telah ditrim
  *@param vector<string> lexic, vector untuk menyimpan hasil parser
  */
void parser(string input, vector<string> &lexic);

/**
  *Digunakan untuk mendapatkan token dari elemen-elemen vector lexic yang didapat dari hasil parser
  *
  *@param string lexic, elemen ke-i dari vector lexic
  *@return int, token dari lexic
  */
int getToken(string lexic);

/**DIgunakan untuk mengecek apakah string inputan diterima(VALID) atau tidak(TIDAK VALID)
  *
  *@param vector<int> tokens, vector untuk menyimpan string token
  *@return string, string berupa "VALID" atau "TIDAK VALID"
  */
string validator(vector<int> tokens);

/**Main Program*/
int main(){
  string input;
  vector<string> lexic;
  vector<int> tokens;
  int token;
  cout<<"Input : ";
  getline(cin, input);
  input = trim(lowcase(input));
  parser(input,lexic);
  cout<<"Output : ";
  for (int i=0; i<lexic.size();i++){
    token = getToken(lexic[i]);
    if (token!=0) {
      tokens.push_back(token);
      cout<<token<<" ";
    }else{
      cout<<"error";
      i=lexic.size();
    }
  }
  cout<<endl<<validator(tokens);
  cout<<endl;
  return 0;
}

/** Fungsi dan Prosedur */
string lowcase(string input){
    for (int i=0; i<input.length();i++){
        input[i]=tolower(input[i]);
    }
    return input;
}

string trim(string input){
  if (input!=""){
    int inpBegin = input.find_first_not_of(" ");
    if (inpBegin == string::npos){
       return "";
    }
    int inpLength = input.find_last_not_of(" ") - inpBegin + 1;
    string result = input.substr(inpBegin,inpLength);

    int spaceBegin;
    int spaceLength;
    int begin=0;
    spaceBegin = result.find_first_of(" ",begin);
    while(spaceBegin != string::npos){
      spaceLength = result.find_first_not_of(" ",spaceBegin) - spaceBegin;
      result.replace(spaceBegin, spaceLength, " ");
      begin=spaceBegin+1;
      spaceBegin = result.find_first_of(" ",begin);
    }
    return result;
  }else{
    return "";
  }
}

void parser(string input, vector<string> &lexic){
  string kata="";
  for (int i=0; i<input.length(); i++) {
    if (input[i]==' ') {
      if (input[i-1] !='(' && input[i-1]!=')')
      {
        lexic.push_back(kata);
        kata="";
      }
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
  switch (lexic.length()){
    case 1:
      if (lexic[0]=='p' || lexic[0]=='q' || lexic[0]=='r' || lexic[0]=='s') {
        return 1;
      }else if (lexic[0]=='(') {
        return 9;
      }else if (lexic[0]==')') {
        return 10;
      }
    case 2:
      if (lexic[0]=='o' && lexic[1]=='r') {
        return 4;
      }else if (lexic[0]=='i' && lexic[1]=='f') {
        return 6;
      }
    case 3:
      if(lexic[0]=='n' && lexic[1]=='o' && lexic[2]=='t'){
        return 2;
      }else if(lexic[0]=='a' && lexic[1]=='n' && lexic[2]=='d'){
        return 3;
      }else if (lexic[0]=='x' && lexic[1]=='o' && lexic[2]=='r') {
        return 5;
      }else if (lexic[0]=='i' && lexic[1]=='f' && lexic[2]=='f'){
        return 8;
      }
    case 4:
      if (lexic[0]=='t' && lexic[1]=='h' && lexic[2]=='e' && lexic[3]=='n') {
        return 7;
      }
    default:
      return 0;
  }
}

string validator(vector<int> tokens){
    vector<int> stack;
    char state = '1';
    for (int i = 0; i < tokens.size(); i++) {
      switch (tokens[i]) {
        case 1:
          if (state == '1') {
            state = '2';
          }else if (state == '2') {
            stack.push_back(1);
          }
          break;
        case 2:
          break;
        case 3:
          if (state == '2') {
            state = '1';
          }
          break;
        case 4:
          if (state == '2') {
            state = '1';
          }
          break;
        case 5:
          if (state == '2') {
            state = '1';
          }
          break;
        case 6:
          if (state == '1') {
            stack.push_back(6);
          }
          break;
        case 7:
          if (state == '2') {
            if (stack.back()==6) {
                state = '1';
                stack.pop_back();
            }
          }
          break;
        case 8:
          if (state == '2') {
            state = '1';
          }
          break;
        case 9:
          if (state == '1') {
            stack.push_back(9);
          }
          break;
        case 10:
          if (state == '2') {
            if (stack.back()==9) {
              stack.pop_back();
            }
          }
          break;
      }
    }
    if (stack.size()==0 && state == '2') {
      return "VALID";
    }else{
      return "TIDAK VALID";
    }
}
