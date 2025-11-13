#include<iostream>
#include<bits/stdc++.h>
using namespace std;
void firstfit(vector<int> blocks,vector<int> processes){
    int n = blocks.size();
    for(int i = 0;i < n;i++){
        int target = processes[i];
        int done = 0;
        for(int j = 0;j < n;j++){
            if(blocks[j] > target){
                cout << "process with size " << target << " allocated at " << blocks[j] << " remaining size = " << blocks[j] - target << endl;
                blocks[j] -= target;
                done = 1;
                break;
            }
        }
        if(done == 0) cout << "process with size " << target << " not allocated " << endl;
        
    }
}
void nextfit(vector<int> blocks,vector<int> processes){
    int n = blocks.size();
    int ptr = 0;
    for(int i = 0;i < n;i++){
        int target = processes[i];
        int done = 0;
        int count = 0;
        while(done == 0 && count != n){
            if(blocks[ptr] > target){
                cout << "process with size " << target << " allocated at " << blocks[ptr] << endl;
                cout << "remaining size = " << blocks[ptr] - target << endl;
                blocks[ptr] -= target;
                done = 1;
                break;
            }
            ptr++;
            count++;
            ptr %= n;
        }
        if(done == 0) cout << "process with size " << target << " not allocated " << endl;
        
    }
}
void bestfit(vector<int> blocks,vector<int> processes){
    int n = blocks.size();
    for(int i = 0;i < n;i++){
        int target = processes[i];
        int min_target = -1;
        int done = 0;
        for(int j = 0;j < n;j++){
            if(blocks[j] >= target){
                if(min_target == -1) min_target = j;
                else if(blocks[j] < blocks[min_target]) min_target = j;
  
            }
        }
        if(min_target != - 1) done = 1;
        if(done == 1){
            cout << "process with size " << target << " allocated at " << blocks[min_target] << " remaining size = " << blocks[min_target] - target << endl;
            blocks[min_target] -= target;
        }
        else cout << "process with size " << target << " not allocated " << endl;
    }
}
void worstfit(vector<int> blocks,vector<int> processes){
    int n = blocks.size();
    for(int i = 0;i < n;i++){
        int target = processes[i];
        int max_target = -1;
        int done = 0;
        for(int j = 1;j < n;j++){
            if(blocks[j] >= target){
                if(max_target == -1) max_target = j;
                else if(blocks[j] > blocks[max_target]) max_target = j;
                done = 1;
            }
        }
        if(max_target != -1) done = 1;
        if(done == 1){
            cout << "process with size " << target << " allocated at " << blocks[max_target] << " remaining size = " << blocks[max_target] - target << endl;
            blocks[max_target] -= target;
        }
        else cout << "process with size " << target << " not allocated " << endl;
    }
}
int main(){
    cout << "enter no of memory blocks" << endl;
    int n;
    cin >> n;
    cout << "enter the block sizes" << endl;
    vector<int> blocks(n);
    for(int i = 0;i < n;i++) cin >> blocks[i];

    cout << "enter the processes" << endl;
    vector<int> processes(n);
    for(int i = 0;i < n;i++) cin >> processes[i];

    char ch = 'y';
    while(ch == 'y'){
        cout << "\n1. First Fit\n2. Next Fit\n3. Best Fit\n4. Worst Fit\nChoice: " << endl;
        cout << "enter the required thing" << endl;
        int number;
        cin >> number;
        if(number == 1) firstfit(blocks,processes);
        else if(number == 2) nextfit(blocks,processes);
        else if(number == 3) bestfit(blocks,processes);
        else if(number == 4) worstfit(blocks,processes);
        else {
            cout << "end" << endl;
            break;
        }
    }
    return 0;
}