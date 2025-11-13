#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream ic("ic.txt");
    ifstream symf("symtab.txt");
    ifstream litf("littab.txt");

    if(!ic){ cout<<"ic.txt not found!\n"; return 0; }
    if(!symf){ cout<<"symtab.txt not found!\n"; return 0; }
    if(!litf){ cout<<"littab.txt not found!\n"; return 0; }

    // ---- Step 1: Read SYMTAB ----
    map<string,int> SYM;
    string s; int addr;
    while(symf >> s >> addr){
        SYM[s] = addr;
    }

    // ---- Step 2: Read LITTAB ----
    vector<pair<string,int>> LIT(1); // 1-based indexing
    int index; string lit; int laddr;
    while(litf >> index >> lit >> laddr){
        LIT.push_back({lit, laddr});
    }

    // ---- Step 3: Process IC ----
    cout << "\nMACHINE CODE:\n";
    string line;
    int LC = 0;

    while(getline(ic, line)){
        if(line.empty()) continue;

        // START directive
        if(line.find("(AD,01)") != string::npos){
            int pos = line.find("(C,");
            if(pos != string::npos){
                string num = line.substr(pos+3);
                num.pop_back();
                LC = stoi(num);
            }
            continue;
        }

        // ORIGIN / END / LTORG → no machine code generated
        if(line.find("(AD,02)") != string::npos || 
           line.find("(AD,03)") != string::npos ||
           line.find("(AD,05)") != string::npos){
            continue;
        }

        // DS (reserve space)
        if(line.find("(DL,01)") != string::npos){
            int pos = line.find("(C,");
            string num = line.substr(pos+3);
            num.pop_back();
            int k = stoi(num);
            LC += k;
            continue;
        }

        // DC (define constant)
        if(line.find("(DL,02)") != string::npos){
            int pos = line.find("(C,");
            string num = line.substr(pos+3);
            num.pop_back();
            cout << LC << " : 00 00 " << num << "\n";
            LC++;
            continue;
        }

        // Imperative statement (IS)
        if(line.find("(IS,") != string::npos){
            int opcode=0, reg=0, mem=0;

            // Extract opcode
            int opStart = line.find("(IS,");
            opcode = stoi(line.substr(opStart+4,2));

            // Extract register or condition code
            int rpos = line.find("(R,");
            if(rpos != string::npos){
                reg = stoi(line.substr(rpos+3,1));
            } 
            else if(line.find("(CC,") != string::npos){
                int ccpos = line.find("(CC,");
                reg = stoi(line.substr(ccpos+4,1));
            }

            // Extract memory address / constant / symbol
            if(line.find("(S,") != string::npos){
                int spos = line.find("(S,");
                string sym = line.substr(spos+3);
                sym.pop_back();
                mem = SYM[sym];
            }
            else if(line.find("(L,") != string::npos){
                int lpos = line.find("(L,");
                int idx = stoi(line.substr(lpos+3));
                mem = LIT[idx].second;
            }
            else if(line.find("(C,") != string::npos){
                int cpos = line.find("(C,");
                string num = line.substr(cpos+3);
                num.pop_back();
                mem = stoi(num);
            }

            // Print machine code line
            cout << LC << " : " 
                 << setw(2) << setfill('0') << opcode << "  "
                 << setw(2) << reg << "  "
                 << setw(3) << mem << "\n";
            LC++;
        }
    }

    ic.close();
    symf.close();
    litf.close();
}
