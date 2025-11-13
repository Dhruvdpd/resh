#include<bits/stdc++.h>
using namespace std;

struct Process {
    int id, at, bt, ct, rt;
};

int main(){
    int n, q; 
    cout<<"Enter number of processes and time quantum: ";
    cin>>n>>q;

    vector<Process> p(n);
    cout<<"Enter arrival and burst times:\n";
    for(int i=0;i<n;i++){
        p[i].id = i+1;
        cin>>p[i].at>>p[i].bt;
        p[i].rt = p[i].bt;
    }

    queue<int> rq;
    int time=0, done=0, i=0;
    cout<<"Gantt Chart:\n";

    while(done < n){
        while(i<n && p[i].at <= time) rq.push(i), i++;

        if(rq.empty()){ time++; continue; }

        int idx = rq.front(); rq.pop();
        cout<<"|P"<<p[idx].id;
        int t = min(q, p[idx].rt);
        p[idx].rt -= t;
        time += t;

        while(i<n && p[i].at <= time) rq.push(i), i++;

        if(p[idx].rt == 0){
            p[idx].ct = time;
            done++;
        } else rq.push(idx);
    }
    cout<<"|\n\n";

    cout<<"P\tAT\tBT\tCT\tTAT\tWT\n";
    for(auto &x : p){
        int tat = x.ct - x.at;
        int wt  = tat - x.bt;
        cout<<"P"<<x.id<<"\t"<<x.at<<"\t"<<x.bt<<"\t"<<x.ct<<"\t"<<tat<<"\t"<<wt<<"\n";
    }
}
