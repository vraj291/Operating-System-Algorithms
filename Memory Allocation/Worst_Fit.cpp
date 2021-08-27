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

void displayFragmentation(Process* processes,int processCount,Block* blocks,int blockCount){
    int internal=0,external=0,i;
    for(i=0;i<blockCount;i++){
        if(blocks[i].left < blocks[i].size){
            internal += blocks[i].left;
        }
    }
    for(i=0;i<processCount;i++){
        if(processes[i].blockid == -1){
            for(i=0;i<blockCount;i++){
                if(blocks[i].left == blocks[i].size){
                    external += blocks[i].left;
                }
            }
            if(external >= processes[i].size){
                external = 0;
            }
        }
    }
    cout << "Total Internal Fragmentation : " << internal << "\n";
    cout << "Total External Fragmentation : " << external << "\n";
}

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

void display(Process* processes,int processCount,Block* blocks,int blockCount){
    displayProcesses(processes,processCount);
    displayBlocks(blocks,blockCount);
    displayFragmentation(processes,processCount,blocks,blockCount);
}

void worstFit(int* p,int p_len,int* b,int b_len){

    Process processes[p_len];
    Block blocks[b_len];
    int i,j,index,max;

    for(i=0;i<b_len;i++){
        blocks[i] = {i+1,b[i],b[i]};
    }

    for(i=0;i<p_len;i++){
        index = -1;
        max = INT_MIN;
        for(j=0;j<b_len;j++){
            if(blocks[j].left-p[i] >= max && blocks[j].left-p[i] >= 0){
                max = blocks[j].left-p[i];
                index = j;
            }
        }
        if(index != -1){
            blocks[index].left -= p[i];
            blocks[index].pid.push_back(i+1);
            processes[i] = {i+1,p[i],index+1};
        }else{
            processes[i] = {i+1,p[i],-1};
        }

    }

    display(processes,p_len,blocks,b_len);
}

int main(){

    int b[] = {100,500,200,300,600};
    int p[] = {212,417,112,426};

    worstFit(p,sizeof(p)/sizeof(p[0]),b,sizeof(b)/sizeof(b[0]));
}



