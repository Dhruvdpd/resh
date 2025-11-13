#include<bits/stdc++.h>
using namespace std;

struct Process {
    int id, at, bt, pr, ct, tat, wt;
};

int main(){
    int n;
    cout<<"Enter number of processes: ";
    cin>>n;

    vector<Process> p(n);
    cout<<"Enter arrival, burst time and priority:\n";
    for(int i=0;i<n;i++){
        p[i].id = i+1;
        cin>>p[i].at>>p[i].bt>>p[i].pr;
    }

    vector<int> done(n,0);
    int time=0, completed=0;

    cout<<"Gantt Chart:\n";
    while(completed < n){
        int idx = -1, high = -1;
        for(int i=0;i<n;i++){
            if(!done[i] && p[i].at <= time && p[i].pr > high){
                high = p[i].pr;
                idx = i;
            }
        }
        if(idx == -1){ time++; continue; }

        cout<<"|P"<<p[idx].id<<" ";
        time += p[idx].bt;
        p[idx].ct = time;
        done[idx] = 1;
        completed++;
    }
    cout<<"|\n\n";

    cout<<"P\tAT\tBT\tPR\tCT\tTAT\tWT\n";
    for(auto &x : p){
        x.tat = x.ct - x.at;
        x.wt = x.tat - x.bt;
        cout<<"P"<<x.id<<"\t"<<x.at<<"\t"<<x.bt<<"\t"<<x.pr<<"\t"<<x.ct<<"\t"<<x.tat<<"\t"<<x.wt<<"\n";
    }
}
