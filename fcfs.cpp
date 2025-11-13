#include<bits/stdc++.h>
using namespace std;

int main(){
    int n; cout<<"enter no of processes\n"; 
    cin>>n;

    vector<pair<int,pair<int,int>>> v(n); 
    for(int i=0;i<n;i++){
        cout << "enter the arrival time" << endl;
        cin >> v[i].first;
        cout << "enter the process number and the burst time" << endl;
        cin >> v[i].second.first;
        cin >> v[i].second.second;
    }

    sort(v.begin(),v.end()); 


    vector<int> ct(n), tat(n), wt(n);

    cout<<"Gantt Chart:\n";
    for(int i=0;i<n;i++){
        cout<<"| P"<<v[i].second.first<<" ";
    }
    cout<<"|\n";

    int time = v[0].first;
    for(int i=0;i<n;i++){
        cout << time << "   " << time+v[i].second.second;
        time += v[i].second.second;
        if(time < v[i+1].first) time = v[i+1].first;
    }
    cout<<"\n\n";

    // Print table
    // cout<<"P\tAT\tBT\tCT\tTAT\tWT\n";
    // for(int i=0;i<n;i++){
    //     tat[i] = ct[i] - v[i].first;
    //     wt[i]  = tat[i] - v[i].second;
    //     cout<<"P"<<i+1<<"\t"<<v[i].first<<"\t"<<v[i].second<<"\t"<<ct[i]
    //     <<"\t"<<tat[i]<<"\t"<<wt[i]<<"\n";
    // }
}
