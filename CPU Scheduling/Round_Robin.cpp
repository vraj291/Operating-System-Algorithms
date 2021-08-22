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

class Queue{

    struct Node{
        int index;
        int burst_time;
        struct Node* next;
    };

    Node* head;
    int len;
    int temp_i;
    int temp_val;
    int difference;

    public:

    Queue(){
        head = NULL;
        len = 0;
        temp_i = -1;
        temp_val = -1;
        difference = 0;
    }

    Node* create(int i,int val){
        Node* ptr = (Node*)malloc(sizeof(Node));;
        ptr->index = i;
        ptr->burst_time = val;
        ptr->next = NULL;
        return ptr;
    }

    void add(int i,int val){
        Node* ptr = create(i,val);
        if(head == NULL){
            head = ptr;
            len++;
        }else{
            Node* temp = head;
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = ptr;
            len++;
        }
    }

    void display(){
        Node* temp = head;
        while(temp != NULL){
            cout << temp->index << " " << temp->burst_time << "\n";
            temp = temp->next;
        }
        cout << "\n";
    }

    void _delete(){
        Node* temp = head;
        if(len == 1){
            head = NULL;
            len = 0;
        }else if (len == 2){
            head = head->next;
            head->next = NULL;
            len = 1;
        }else{
            head = head->next;
            len--;
        }
        free(temp);
    }

    int performProcess(int quantum){
        if(head == NULL) return -1;
        if(temp_i != -1 && temp_val != -1){
            if(temp_val > 0){
                add(temp_i,temp_val);
            }
        }
        if(head->burst_time < quantum){
            difference = quantum - head->burst_time;
        }else{
            difference = 0;
        }
        head->burst_time -= quantum;
        temp_i = head->index;
        temp_val = head->burst_time;
        _delete();
        return temp_i;
    }

    bool checkDifference(){
        if(difference > 0){
            return true;
        }
        return false;
    }

    int getDifference(){
        return difference;
    }

    int size(){
        return len;
    }
};

void Round_Robin(int _at[],int _bt[],int len,int quantum){

    Process processes[len];
    Queue ready;
    int i,j,curr,temp_j,temp_curr;

    for(i=0;i<len;i++){
        processes[i] = {i,_at[i],_bt[i]};
        processes[i].resp_time = -1;
    }

    sort(processes,processes+len,[](Process p1, Process p2){
        return p1.act_time < p2.act_time;
    });

    cout << "\nScheduling as per Round Robin : \n\n";
    i=0,j=0,curr=0,temp_curr=0,temp_j=0;
    while(i < len || ready.size() > 0){
        while(processes[i].act_time <= j){
            ready.add(i,processes[i].burst_time);
            i++;
        }
        curr = ready.performProcess(quantum);
        if( i == 0 ){
            j++;
            temp_curr = -1;
            continue;
        }
        if(temp_curr != curr){
            if(temp_curr != -1){
                cout << " P" << temp_curr+1 << " : " ;
                processes[temp_curr].comp_time = j;
                processes[temp_curr].turn_around_time = processes[temp_curr].comp_time - processes[temp_curr].act_time;
                processes[temp_curr].wait_time = processes[temp_curr].turn_around_time - processes[temp_curr].burst_time;
                if(processes[temp_curr].resp_time == -1){
                    processes[temp_curr].resp_time = temp_j - processes[temp_curr].act_time;
                }
            }else{
                cout << " Empty : ";
            }
            cout << temp_j << " - " << j << "\n";
            temp_curr = curr;
            temp_j = j;
        }
        if(ready.checkDifference()){
            j += ready.getDifference();
        }else{
            j += quantum;
        }
    }
    cout << " P" << temp_curr+1 << " : " << temp_j << " - " << j << "\n";
    processes[temp_curr].comp_time = j;
    processes[temp_curr].turn_around_time = processes[temp_curr].comp_time - processes[temp_curr].act_time;
    processes[temp_curr].wait_time = processes[temp_curr].turn_around_time - processes[temp_curr].burst_time;
    if(processes[temp_curr].resp_time == -1){
        processes[temp_curr].resp_time = temp_j - processes[temp_curr].act_time;
    }

    sort(processes,processes+len,[](Process p1, Process p2){
        return p1.pid < p2.pid;
    });

    displayProcesses(processes,len);
    writeToFile("RR_output.txt",processes,len);
}

int main(){

    string filename = "RR_input.txt";

    int len = getFileLength(filename);
    int _at[len];
    int _bt[len];
    int quantum = 2;

    getFileInputs(filename,_at,_bt,len);

    Round_Robin(_at,_bt,sizeof(_at)/sizeof(_at[0]),quantum);

    cout << "\nOutput written to : RR_output.txt";
    cout << "\n\n\t\t\tPrepared by : Vraj Parikh 19CE088";
}


