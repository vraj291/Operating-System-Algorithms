#include <bits/stdc++.h>
using namespace std;

struct Process{
    int pid;
    int act_time;
    int burst_time;
    int priority;
    int comp_time;
    int turn_around_time;
    int wait_time;
    int resp_time;
};

int getFileLength(string filename){
    int c = 0;
    string temp;
    ifstream input(filename);
    while(getline(input,temp)){
        c++;
    }
    input.close();
    return c;
}

void getFileInputs(string filename,int _at[],int _bt[],int _pr[],int len){
    int i,j,last,temp,index;
    string file;
    ifstream input(filename);
    for(i=0;i<len;i++){
        getline(input,file);
        index = file.find(' ');
        temp = stoi(file.substr(0,index));
        file = file.substr(index+1);
        index = file.find(' ');
        _at[temp] = stoi(file.substr(0,index));
        file = file.substr(index+1);
        index = file.find(' ');
        _bt[temp] = stoi(file.substr(0,index));
        file = file.substr(index+1);
        index = file.find(' ');
        _pr[temp] = stoi(file.substr(0,index));
    }
    input.close();
}

void writeToFile(string filename,Process* processes,int len){
    ofstream out(filename);
    for(int i=0;i<len;i++){
        out << processes[i].pid << " ";
        out << processes[i].turn_around_time << " ";
        out << processes[i].wait_time << " ";
        out << processes[i].resp_time << "\n";
    }
}

void displayProcesses(Process* processes,int len){
    cout << "\n--------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "|  Process Id  |  Activation Time  |  Priority  |  Burst Time  |  Completion Time  |  Turn Around Time  |  Waiting Time  |  Response Time  |\n";
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------\n";
    int tat=0,wt=0,rt=0;
    for(int i=0;i<len;i++){
        cout <<"|";
        cout.width(13);
        cout << processes[i].pid << " |";
        cout.width(18);
        cout << processes[i].act_time << " |";
        cout.width(11);
        cout << processes[i].priority << " |";
        cout.width(13);
        cout << processes[i].burst_time << " |";
        cout.width(18);
        cout << processes[i].comp_time << " |";
        cout.width(19);
        cout << processes[i].turn_around_time << " |";
        tat += processes[i].turn_around_time;
        cout.width(15);
        cout << processes[i].wait_time << " |";
        wt += processes[i].wait_time;
        cout.width(16);
        cout << processes[i].resp_time << " |\n";
        rt += processes[i].resp_time;
    }
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------\n\n";
    cout << "Average Turn Around Time : " << (double)tat/(double)len << "\n";
    cout << "Average Waiting Time : " << (double)wt/(double)len << "\n";
    cout << "Average Response Time : " << (double)rt/(double)len << "\n";
}

int findMin(map<int,int> ready, Process* processes,int len){
    int index = -1;
    int max = INT_MIN;
    for(int i=0;i<len;i++){
        if(processes[i].priority > max && ready[i] > 0){
            max = processes[i].priority;
            index = i;
        }
    }
    return index;
}

void Priority(int _at[],int _bt[],int _pr[],int len){

    Process processes[len];
    map<int,int> ready;
    int i,j,curr,temp_j,temp_curr;

    for(i=0;i<len;i++){
        processes[i] = {i,_at[i],_bt[i],_pr[i]};
        processes[i].resp_time = -1;
    }

    sort(processes,processes+len,[](Process p1, Process p2){
        return p1.act_time < p2.act_time;
    });

    cout << "\nScheduling as per Priority Scheduling : \n\n";
    i=0,j=0,curr=0,temp_curr=0,temp_j=0;
    while(true){
        if(processes[i].act_time == j){
            ready[i] = processes[i].burst_time;
            if(processes[i].priority > processes[curr].priority || ready.size() == 1){
                if(processes[i].resp_time == -1){
                    processes[i].resp_time = j - processes[i].act_time;
                }
                curr = i;
            }
            i++;
        }
        if(ready[curr] == 0){
            processes[curr].comp_time = j;
            processes[curr].turn_around_time = processes[curr].comp_time - processes[curr].act_time;
            processes[curr].wait_time = processes[curr].turn_around_time - processes[curr].burst_time;
            ready.erase(curr);
            curr = findMin(ready,processes,len);
            if(curr == -1){
                cout << " P" << temp_curr+1 << " : " << temp_j << " - " << j << "\n";
                break;
            }else{
                if(processes[curr].resp_time == -1){
                    processes[curr].resp_time = j - processes[curr].act_time;
                }
            }
        }
        ready[curr]--;
        if(temp_curr != curr){
            cout << " P" << temp_curr+1 << " : " << temp_j << " - " << j << "\n";
            temp_curr = curr;
            temp_j = j;
        }
        j++;
    }

    sort(processes,processes+len,[](Process p1, Process p2){
        return p1.pid < p2.pid;
    });

    displayProcesses(processes,len);
    writeToFile("Priority_output.txt",processes,len);
}

int main(){

    string filename = "Priority_input.txt";

    int len = getFileLength(filename);
    int _at[len];
    int _bt[len];
    int _pr[len];

    getFileInputs(filename,_at,_bt,_pr,len);

    Priority(_at,_bt,_pr,sizeof(_at)/sizeof(_at[0]));

    cout << "\nOutput written to : Priority_output.txt";
    cout << "\n\n\t\t\tPrepared by : Vraj Parikh 19CE088";
}

