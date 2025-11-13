#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int main(){

    cout << "enter the no of processes" << endl;
    int n;
    cin >> n;
    cout << "enter the time quantum" << endl;
    int quant;
    cin >> quant;


    vector<pair<int,pair<int,int>>> v(n); 
    for(int i=0;i<n;i++){
        cout << "enter the arrival time" << endl;
        cin >> v[i].first;
        cout << "enter the process number and the burst time" << endl;
        cin >> v[i].second.first;
        cin >> v[i].second.second;
    }

    sort(v.begin(),v.end());

    queue<pair<int,pair<int,int>>> q;
    for(int i = 0;i < n;i++){
        q.push(v[i]);
    } 
    cout << "Gantt chart" << endl;
    int time = v[0].first;
    while(!q.empty()){
        pair<int,pair<int,int>> p1 = q.front();
        q.pop();
        cout << "| P" << p1.second.first << " -" << time << "-" << min(quant+time,time+p1.second.second);
        time += min(quant+time,p1.second.second);
        p1.second.second -= quant;
        if(p1.second.second > 0) q.push(p1); 

    }
    return 0;
}
// #include <bits/stdc++.h>
// using namespace std;

// int main() {
//     int n, q; cin >> n >> q;                   // n processes, time quantum q
//     vector<int> at(n), bt(n), rt(n), ct(n);   // arrival, burst, remaining, completion
//     for(int i=0;i<n;i++){
//         cin >> at[i] >> bt[i];
//         rt[i] = bt[i];
//     }

//     queue<int> rq;    // ready queue (stores indices)
//     int time = 0, done = 0, i = 0;

//     cout << "Gantt: ";

//     while(done < n) {
//         while(i < n && at[i] <= time) rq.push(i), i++;

//         if(rq.empty()) { time++; continue; }

//         int p = rq.front(); rq.pop();
//         cout << "|P" << p+1;

//         int t = min(q, rt[p]);
//         rt[p] -= t;
//         time += t;

//         while(i < n && at[i] <= time) rq.push(i), i++;

//         if(rt[p] == 0) {
//             ct[p] = time;
//             done++;
//         } else rq.push(p);
//     }
//     cout << "|\n\n";

//     cout << "P\tAT\tBT\tCT\tTAT\tWT\n";
//     for(int i=0;i<n;i++){
//         int tat = ct[i] - at[i];
//         int wt  = tat - bt[i];
//         cout<<"P"<<i+1<<"\t"<<at[i]<<"\t"<<bt[i]<<"\t"<<ct[i]<<"\t"<<tat<<"\t"<<wt<<"\n";
//     }
// }
