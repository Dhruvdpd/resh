#include<bits/stdc++.h>
using namespace std;

struct Process {
    int id, at, bt, ct, tat, wt;
};

int main(){
    int n; 
    cout<<"enter no of processes\n"; 
    cin>>n;

    vector<Process> p(n);

    cout<<"enter arrival and burst times\n";
    for(int i=0;i<n;i++){
        p[i].id = i+1;
        cin>>p[i].at>>p[i].bt;
    }

    sort(p.begin(), p.end(), [](auto &a, auto &b){ return a.at < b.at; });

    int time = 0;
    cout<<"Gantt Chart:\n";
    for(auto &x : p){
        if(time < x.at) time = x.at; // handle idle time
        cout<<"| P"<<x.id<<" ";
        time += x.bt;
        x.ct = time;
    }
    cout<<"|\n";

    time = 0;
    cout<<0<<" ";
    for(auto &x : p){
        if(time < x.at) time = x.at;
        time += x.bt;
        cout<<time<<" ";
    }
    cout<<"\n\n";

    cout<<"P\tAT\tBT\tCT\tTAT\tWT\n";
    for(auto &x : p){
        x.tat = x.ct - x.at;
        x.wt = x.tat - x.bt;
        cout<<"P"<<x.id<<"\t"<<x.at<<"\t"<<x.bt<<"\t"<<x.ct<<"\t"<<x.tat<<"\t"<<x.wt<<"\n";
    }
}
