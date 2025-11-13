#include<bits/stdc++.h>
using namespace std;

struct Process {
    int id, at, bt, rt, ct, tat, wt;
};

int main(){
    int n;
    cout<<"Enter number of processes: ";
    cin>>n;

    vector<Process> p(n);
    cout<<"Enter arrival and burst times:\n";
    for(int i=0;i<n;i++){
        p[i].id = i+1;
        cin>>p[i].at>>p[i].bt;
        p[i].rt = p[i].bt;  // remaining time = burst time initially
    }

    int time = 0, completed = 0;
    cout<<"Gantt Chart:\n";

    while(completed < n){
        int idx = -1;
        int mn = INT_MAX;

        // choose process with smallest remaining time among arrived ones
        for(int i=0;i<n;i++){
            if(p[i].at <= time && p[i].rt > 0 && p[i].rt < mn){
                mn = p[i].rt;
                idx = i;
            }
        }

        if(idx == -1){ time++; continue; }

        cout<<"|P"<<p[idx].id<<" ";
        p[idx].rt--;    // run for 1 unit
        time++;

        if(p[idx].rt == 0){       // finished
            p[idx].ct = time;
            completed++;
        }
    }
    cout<<"|\n\n";

    cout<<"P\tAT\tBT\tCT\tTAT\tWT\n";
    for(auto &x : p){
        x.tat = x.ct - x.at;
        x.wt = x.tat - x.bt;
        cout<<"P"<<x.id<<"\t"<<x.at<<"\t"<<x.bt<<"\t"<<x.ct<<"\t"<<x.tat<<"\t"<<x.wt<<"\n";
    }
}
