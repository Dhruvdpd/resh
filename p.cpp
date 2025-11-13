#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class MemoryAllocation {
private:
    vector<int> blocks;
    vector<int> processes;
    int lastAllocatedIndex; // for Next Fit

public:
    MemoryAllocation(vector<int> b, vector<int> p) {
        blocks = b;
        processes = p;
        lastAllocatedIndex = 0;
    }

    void resetBlocks(vector<int> original) {
        blocks = original;
        lastAllocatedIndex = 0;
    }

    void printResult(vector<int> allocation, vector<int> usedRemaining) {
        cout << "\n-------------------------------------------------------------\n";
        cout << setw(10) << "Process"
             << setw(15) << "Size"
             << setw(20) << "Block Allocated"
             << setw(20) << "Remaining Block Size" << endl;
        cout << "-------------------------------------------------------------\n";
        for (int i = 0; i < processes.size(); i++) {
            cout << setw(10) << i + 1
                 << setw(15) << processes[i];
            if (allocation[i] != -1)
                cout << setw(20) << allocation[i] + 1 << setw(20) << usedRemaining[i];
            else
                cout << setw(20) << "Not Allocated" << setw(20) << "-";
            cout << endl;
        }
        cout << "-------------------------------------------------------------\n";
    }

    void firstFit() {
        vector<int> allocation(processes.size(), -1);
        vector<int> remaining = blocks;
        vector<int> usedRemaining(processes.size(), -1);

        for (int i = 0; i < processes.size(); i++) {
            for (int j = 0; j < blocks.size(); j++) {
                if (remaining[j] >= processes[i]) {
                    allocation[i] = j;
                    remaining[j] -= processes[i];
                    usedRemaining[i] = remaining[j]; // store snapshot
                    break;
                }
            }
        }
        cout << "\nResult using First Fit:";
        printResult(allocation, usedRemaining);
    }

    void nextFit() {
        vector<int> allocation(processes.size(), -1);
        vector<int> remaining = blocks;
        vector<int> usedRemaining(processes.size(), -1);

        int j = lastAllocatedIndex;

        for (int i = 0; i < processes.size(); i++) {
            bool allocated = false;
            int count = 0;
            while (count < blocks.size()) {
                if (remaining[j] >= processes[i]) {
                    allocation[i] = j;
                    remaining[j] -= processes[i];
                    usedRemaining[i] = remaining[j];
                    lastAllocatedIndex = j;
                    allocated = true;
                    break;
                }
                j = (j + 1) % blocks.size();
                count++;
            }
        }
        cout << "\nResult using Next Fit:";
        printResult(allocation, usedRemaining);
    }

    void bestFit() {
        vector<int> allocation(processes.size(), -1);
        vector<int> remaining = blocks;
        vector<int> usedRemaining(processes.size(), -1);

        for (int i = 0; i < processes.size(); i++) {
            int bestIdx = -1;
            for (int j = 0; j < blocks.size(); j++) {
                if (remaining[j] >= processes[i]) {
                    if (bestIdx == -1 || remaining[j] < remaining[bestIdx]) {
                        bestIdx = j;
                    }
                }
            }
            if (bestIdx != -1) {
                allocation[i] = bestIdx;
                remaining[bestIdx] -= processes[i];
                usedRemaining[i] = remaining[bestIdx];
            }
        }
        cout << "\nResult using Best Fit:";
        printResult(allocation, usedRemaining);
    }

    void worstFit() {
        vector<int> allocation(processes.size(), -1);
        vector<int> remaining = blocks;
        vector<int> usedRemaining(processes.size(), -1);

        for (int i = 0; i < processes.size(); i++) {
            int worstIdx = -1;
            for (int j = 0; j < blocks.size(); j++) {
                if (remaining[j] >= processes[i]) {
                    if (worstIdx == -1 || remaining[j] > remaining[worstIdx]) {
                        worstIdx = j;
                    }
                }
            }
            if (worstIdx != -1) {
                allocation[i] = worstIdx;
                remaining[worstIdx] -= processes[i];
                usedRemaining[i] = remaining[worstIdx];
            }
        }
        cout << "\nResult using Worst Fit:";
        printResult(allocation, usedRemaining);
    }
};

int main() {
    int nb, np;
    cout << "Enter number of memory blocks: ";
    cin >> nb;
    vector<int> blocks(nb);
    cout << "Enter sizes of memory blocks:\n";
    for (int i = 0; i < nb; i++) cin >> blocks[i];

    cout << "Enter number of processes: ";
    cin >> np;
    vector<int> processes(np);
    cout << "Enter sizes of processes:\n";
    for (int i = 0; i < np; i++) cin >> processes[i];

    MemoryAllocation ma(blocks, processes);

    int choice;
    do {
        cout << "\n===== Memory Allocation Menu =====\n";
        cout << "1. First Fit\n";
        cout << "2. Next Fit\n";
        cout << "3. Best Fit\n";
        cout << "4. Worst Fit\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            ma.resetBlocks(blocks);
            ma.firstFit();
            break;
        case 2:
            ma.resetBlocks(blocks);
            ma.nextFit();
            break;
        case 3:
            ma.resetBlocks(blocks);
            ma.bestFit();
            break;
        case 4:
            ma.resetBlocks(blocks);
            ma.worstFit();
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}