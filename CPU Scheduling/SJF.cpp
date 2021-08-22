#include <bits/stdc++.h>
using namespace std;

struct Process{
    int pid;
    int act_time;
    int burst_time;
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

void getFileInputs(string filename,int _at[],int _bt[],int len){
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
    cout << "\n-------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "|  Process Id  |  Activation Time  |  Burst Time  |  Completion Time  |  Turn Around Time  |  Waiting Time  |  Response Time  |\n";
    cout << "-------------------------------------------------------------------------------------------------------------------------------\n";
    int tat=0,wt=0,rt=0;
    for(int i=0;i<len;i++){
        cout <<"|";
        cout.width(13);
        cout << processes[i].pid << " |";
        cout.width(18);
        cout << processes[i].act_time << " |";
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
    cout << "-------------------------------------------------------------------------------------------------------------------------------\n\n";
    cout << "Average Turn Around Time : " << (double)tat/(double)len << "\n";
    cout << "Average Waiting Time : " << (double)wt/(double)len << "\n";
    cout << "Average Response Time : " << (double)rt/(double)len << "\n";
}

void SJF(int _at[],int _bt[],int len){

    Process processes[len];
    int i,j,curr;

    for(i=0;i<len;i++){
        processes[i] = {i,_at[i],_bt[i]};
    }

    sort(processes,processes+len,[](Process p1, Process p2){
        return p1.burst_time < p2.burst_time;
    });

    cout << "\nScheduling as per SJF : \n\n";
    i=0;
    curr=0;
    while(i < len){
        if(processes[i].act_time <= curr){
            cout << " P" << processes[i].pid << " : " << curr << " - " << curr+processes[i].burst_time << "\n";
            curr += processes[i].burst_time;
            processes[i].comp_time = curr;
            processes[i].turn_around_time = processes[i].comp_time - processes[i].act_time;
            processes[i].wait_time = processes[i].turn_around_time - processes[i].burst_time;
            processes[i].resp_time = curr - processes[i].burst_time - processes[i].act_time;
            i++;
        }else{
            int temp=curr;
            while(processes[i].act_time > curr){
                curr++;
            }
            cout << " Empty : " << temp << " - " << curr << "\n";
        }
    }

    sort(processes,processes+len,[](Process p1, Process p2){
        return p1.pid < p2.pid;
    });

    displayProcesses(processes,len);
    writeToFile("SJF_output.txt",processes,len);
}

int main(){

    string filename = "SJF_input.txt";

    int len = getFileLength(filename);
    int _at[len];
    int _bt[len];

    getFileInputs(filename,_at,_bt,len);

    SJF(_at,_bt,sizeof(_at)/sizeof(_at[0]));

    cout << "\nOutput written to : SJF_output.txt";
    cout << "\n\n\t\t\tPrepared by : Vraj Parikh 19CE088";
}
