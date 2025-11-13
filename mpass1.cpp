#include <bits/stdc++.h>
using namespace std;

struct MNTEntry {
    string name;
    int mdt_ptr, kpdt_ptr, pp, kp;
};

struct KPDTEntry {
    string param, value;
};

int main() {
    vector<MNTEntry> MNT;
    vector<string> MDT;
    vector<KPDTEntry> KPDTAB;
    vector<string> ALA;

    string word;
    cout << "Enter macro code (END to stop):\n";

    while (cin >> word) {
        if (word == "MACRO") {
            string mname, header;
            cin >> mname; getline(cin, header);  // read rest of line

            // --- Create MNT entry
            MNTEntry m;
            m.name = mname;
            m.mdt_ptr = MDT.size();
            m.kpdt_ptr = KPDTAB.size();
            m.pp = m.kp = 0;

            // --- Parse parameters (&X or &Y=VAL)
            stringstream ss(header);
            string param;
            while (getline(ss, param, ',')) {
                param.erase(remove_if(param.begin(), param.end(), ::isspace), param.end());
                if (param.empty()) continue;
                size_t eq = param.find('=');
                if (eq != string::npos) {
                    string pname = param.substr(0, eq);
                    string val = param.substr(eq + 1);
                    ALA.push_back(pname);
                    KPDTAB.push_back({pname, val});
                    m.kp++;
                } else {
                    ALA.push_back(param);
                    m.pp++;
                }
            }

            // --- Read macro body until MEND
            string line;
            getline(cin, line); // move to next line
            while (true) {
                getline(cin, line);
                if (line.find("MEND") != string::npos) break;

                // Replace formal params with (P,i)
                for (int i = 0; i < ALA.size(); i++) {
                    size_t pos = line.find(ALA[i]);
                    if (pos != string::npos)
                        line.replace(pos, ALA[i].length(), "(P," + to_string(i + 1) + ")");
                }
                MDT.push_back(line);
            }
            MDT.push_back("MEND");
            MNT.push_back(m);
            ALA.clear();  // reset for next macro
        }
        else if (word == "END") break;
    }

    // --- Print tables
    cout << "\n--- MNT ---\n";
    cout << "Name\tMDTptr\tKPDTptr\tPP\tKP\n";
    for (auto &x : MNT)
        cout << x.name << "\t" << x.mdt_ptr+1 << "\t" << x.kpdt_ptr+1 << "\t" << x.pp << "\t" << x.kp << "\n";

    cout << "\n--- MDT ---\n";
    for (int i = 0; i < MDT.size(); i++)
        cout << i + 1 << "\t" << MDT[i] << "\n";

    cout << "\n--- KPDTAB ---\n";
    for (int i = 0; i < KPDTAB.size(); i++)
        cout << i + 1 << "\t" << KPDTAB[i].param << " = " << KPDTAB[i].value << "\n";
}
