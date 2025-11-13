#include <bits/stdc++.h>
#include "symtab.txt"
using namespace std;

int main() {
    ifstream fin("input.asm");
    if(!fin){
        cout<<"input.asm not found!";
        return 0;
    }

    map<string,int> op = {{"MOVER",4},{"MOVEM",5},{"ADD",1},{"SUB",2},
                          {"MULT",3},{"BC",7},{"STOP",0}};
    map<string,int> reg = {{"AREG",1},{"BREG",2},{"CREG",3}};
    map<string,int> cond = {{"LT",1},{"LE",2},{"EQ",3},{"GT",4},
                            {"GE",5},{"NE",6},{"ANY",7}};
    
    map<string,int> SYM;
    vector<string> LIT;
    vector<int> LADDR;
    vector<int> POOL; POOL.push_back(0);

    int LC = 0;
    string w1, w2, w3;  // max tokens per line = 3 (label, op, operand(s))

    while (fin >> w1) {

        // If first token is opcode, no label
        bool label = false;
        if(op.count(w1) || w1=="START" || w1=="LTORG" 
           || w1=="END" || w1=="DS" || w1=="STOP"){
            w3 = "";
            w2 = w1;
        }
        else { 
            // First token = label
            SYM[w1] = LC;
            label = true;
            fin >> w2;
        }

        // START
        if(w2=="START"){
            fin >> w3;
            LC = stoi(w3);
            cout << "(AD,01) (C,"<<LC<<")\n";
            continue;
        }

        // END/LTORG → assign literals
        if(w2=="END" || w2=="LTORG"){
            cout << (w2=="END"?"(AD,02)\n":"(AD,05)\n");
            for(int i = POOL.back(); i < LIT.size(); i++){
                LADDR.push_back(LC);
                LC++;
            }
            if(LIT.size() != POOL.back())
                POOL.push_back(LIT.size());
            if(w2=="END") break;
            continue;
        }
        // ORIGIN
        if(w2=="ORIGIN") {
            fin >> w3;
            // parse something like L1+3
            int pos = w3.find('+');
            string sym = w3.substr(0,pos);
            int k = stoi(w3.substr(pos+1));

            LC = SYM[sym] + k;
            cout << "(AD,03) (S,"<<sym<<") (C,"<<k<<")\n";
            continue;
        }

        // DS
        if(w2=="DS"){
            fin >> w3;
            cout << "(DL,01) (C,"<<w3<<")\n";
            LC += stoi(w3);
            continue;
        }

        // Imperative instructions
        fin >> w3;
        cout << "(IS," << op[w2] << ") ";

        // register?
        if(reg.count(w3)) cout << "(R,"<<reg[w3]<<") ";
        else cout<<"(-,-) ";

        // next operand if exists
        string operand;
        if(reg.count(w3)) fin >> operand;
        else operand = w3;

        // literal?
        if(operand[0]=='='){
            LIT.push_back(operand);
            cout<<"(L,"<<LIT.size()<<")\n";
        }
        // condition?
        else if(cond.count(operand)){
            cout<<"(CC,"<<cond[operand]<<")\n";
        }
        // symbol
        else{
            if(!SYM.count(operand)) SYM[operand] = -1;
            cout<<"(S,"<<operand<<")\n";
        }

        LC++;
    }

    // Print SYMTAB
    cout<<"\nSYMTAB:\n";
    for(auto &x:SYM)
        cout<<x.first<<" "<<x.second<<"\n";

    // Print LITTAB
    cout<<"\nLITTAB:\n";
    for(int i=0;i<LIT.size();i++)
        cout<<i+1<<" "<<LIT[i]<<" "<<LADDR[i]<<"\n";

    // Print POOLTAB
    cout<<"\nPOOLTAB:\n";
    for(int p:POOL) cout<<p+1<<"\n";
}
