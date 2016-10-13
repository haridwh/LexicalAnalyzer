#include <iostream>
#include <vector>
using namespace std;

//deklarasi fungsi, prosedur
void parser(string input, vector<string> &lexic);
int getToken(string lexic);

int main(){
  string input;
  //vector sama dengan List, jadi vector<string> sama dengan List yang isinya string
  vector<string> lexic;
  int token;
  cout<<"Input : ";
  //getLine mirip sama cin tapi bisa nerima input pake spasi, misal "if p then", kalau pake cin cuman ke input 'if'nya aja
  getline(cin, input);
  parser(input,lexic);//manggil prosedur parser
  cout<<"Output : ";
  //ngelakuin pengulangan sebanyak isi dari vector lexic
  for (int i=0; i<lexic.size();i++){
    token = getToken(lexic[i]);//dapetin token dari lexic ke-i, pake fungsi getToken
    //kalau token == 0 berarti error, kalau nggak sama dengan 0 berarti bener
    if (token!=0) {
      cout<<token<<" ";
    }else{
      cout<<"error";
      i=lexic.size();//i diset panjang isi vector lexic, jadi pengulangan langsung berhenti
    }
  }
  cout<<endl;
}


/*dipake buat ngeparser inputan, dan nyimpen di vector lexic
misal input "if p then", setelah di parser isi vector jadi {"if","p","then"}
@params inputan, lexic
*/
void parser(string input, vector<string> &lexic){
  string kata=""; //variabel buat naroh hasil perkata
  //ngelakuin pengulangan sebanyak length input
  for (int i=0; i<input.length(); i++) {
    if (input[i]==' ') {//ngecek input posisi ke-i == spasi atau nggak, misal not q, berarti not harus diinsert dulu sebelum lanjut ke q
      lexic.push_back(kata); //ngeinsert last kata ke dalem vector lexic
      kata=""; //kata diset kosong lagi
    }else if (input[i]=='(') {//ngecek input posisi ke-i == '('
      if (kata != "") { //ngecek variabel kata kosong atau nggak, misal inputan if(p and q), berarti sebelum '(' ada kata "if" jadi harus diinsert dulu
        lexic.push_back(kata);//insert last kata
        kata="";
      }
      lexic.push_back(string(1,input[i]));//insert last '(', pake string(1,input[i]) karena input[i] char jadi harus diubah dulu ke string
    }else if (input[i]==')') {//ngecek input posisi ke-i == ')'
      if (kata != "") { //ngecek variabel kata kosong atau nggak, misal inputan if(p and q), berarti sebelum ')' ada kata "q" jadi harus diinsert dulu
        lexic.push_back(kata);
        kata="";
      }
      lexic.push_back(string(1,input[i]));
    }else{
      kata+=input[i]; //kata = kata+input[i], misal variabel kata isinya "no" terus input[i] isinya "t" jadi hasilnya "not"
    }
  }
  if (kata!="") { //ngecek setelah pengulangan variabel kata masih ada isinya atau nggak, misal if a then, berarti setelah keluar pengulangan variabel kata ada isi "then" jadi harus diinsert
    lexic.push_back(kata);
  }
}

/*fungsi buat ngedapetin token dari lexic yang didapet dari inputan
@params lexic*/
int getToken(string lexic){
  if (lexic[0]=='p' || lexic[0]=='q' || lexic[0]=='r' || lexic[0]=='s') {//ngecek == proposisi, kalau iya return 1
    return 1;
  }else if(lexic[0]=='n' && lexic[1]=='o' && lexic[2]=='t'){ //ngecek == not
    return 2;
  }else if(lexic[0]=='a' && lexic[1]=='n' && lexic[2]=='d'){  //ngecek == and
    return 3;
  }else if(lexic[0]=='o' && lexic[1]=='r'){  //ngecek == or
    return 4;
  }else if (lexic[0]=='x' && lexic[1]=='o' && lexic[2]=='r') {  //ngecek == xor
    return 5;
  }else if (lexic[0]=='i' && lexic[1]=='f') {  //ngecek == if
    if (lexic.length()==3) { //ngecek panjang lexic kalau panajangnya 3 ada kemungkinan lexic isinya "iff"
      if (lexic[2] =='f') { //ngecek char lexic ke-3 sama dengan f gak, kalau iya berarti lexic == iff
        return 8;
      }
    }else if (lexic.length()==2) {  //ngecek panjang sama dengan 2, kalau iya berati if
      return 6;s
    }else{ //kalau panjang lebih dari 3, misal "ifff" berarti error
      return 0;
    }
  }else if (lexic[0]=='t' && lexic[1]=='h' && lexic[2]=='e' && lexic[3]=='n') { //ngecek == then
    return 7;
  }else if (lexic[0]=='(') { //ngecek == (
    return 9;
  }else if (lexic[0]==')') { //ngecek == )
    return 10;
  }else{ //selain diatas berarti error
    return 0;
  }
}
