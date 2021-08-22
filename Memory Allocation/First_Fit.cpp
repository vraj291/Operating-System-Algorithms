#include <bits/stdc++.h>
using namespace std;

struct Process{
    int pid;
    int size;
    int blockid;
};

struct Block{
    int blockid;
    int size;
    int left;
    vector<int> pid;
};

void displayProcesses(Process* processes,int len){
    cout << "Process Table : \n\n";
    cout << "----------------------------------------------\n";
    cout << "|  Process Id  |  Process Size  |  Block Id  |\n";
    cout << "----------------------------------------------\n";
    for(int i=0;i<len;i++){
        cout <<"|";
        cout.width(13);
        cout << processes[i].pid << " |";
        cout.width(15);
        cout << processes[i].size << " |";
        cout.width(11);
        if(processes[i].blockid == -1)
            cout << "    Waiting |\n";
        else
            cout << processes[i].blockid << " |\n";
    }
    cout << "----------------------------------------------\n\n";
}

void displayBlocks(Block* blocks,int len){

    string temp;
    int i,j;

    cout << "Memory Blocks : \n\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "|  Block Id  |  Block Size  |  Available Space  |  Processes Running  |\n";
    cout << "-----------------------------------------------------------------------\n";
    for(i=0;i<len;i++){
        temp = "";
        cout << "|";
        cout.width(11);
        cout << blocks[i].blockid << " |";
        cout.width(13);
        cout << blocks[i].size << " |";
        cout.width(18);
        cout << blocks[i].left << " |";
        if(blocks[i].pid.size() == 0){
            cout << "      None executing |\n";
        }else{
            for(j=0;j<blocks[i].pid.size()-1;j++){
                temp += (char)(48+blocks[i].pid[j]);
                temp += ", ";
            }
            temp += (char)(48+blocks[i].pid[j]);
            for(j=temp.length();j<20;j++){
                temp = " " + temp;
            }
            cout << temp << " |\n";
        }
    }
    cout << "-----------------------------------------------------------------------\n\n";
}

void firstFit(int* p,int p_len,int* b,int b_len){

    Process processes[p_len];
    Block blocks[b_len];
    int i,j,temp;

    for(i=0;i<b_len;i++){
        blocks[i] = {i+1,b[i],b[i]};
    }

    for(i=0;i<p_len;i++){
        temp = -1;
        for(j=0;j<b_len;j++){
            if(blocks[j].left >= p[i]){
                temp = j+1;
                blocks[j].left -= p[i];
                blocks[j].pid.push_back(i+1);
                break;
            }
        }
        processes[i] = {i+1,p[i],temp};
    }

    displayProcesses(processes,p_len);
    displayBlocks(blocks,b_len);
}

int main(){

    int b[] = {100,500,200,300,600};
    int p[] = {212,417,112,426};

    firstFit(p,sizeof(p)/sizeof(p[0]),b,sizeof(b)/sizeof(b[0]));
}
