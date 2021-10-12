#include <bits/stdc++.h>
using namespace std;

class Bankers{

    int processCount;
    int resourceCount;
    int** alloc;
    int** max;
    int** need;
    int* available;

    public :

    Bankers(string filename){
        readFromFile(filename);
    }

    void readFromFile(string filename){
        int i,j;
        string info;
        ifstream input(filename);
        getline(input,info);
        int temp = info.find(" ");
        processCount = stoi(info.substr(0,temp));
        resourceCount = stoi(info.substr(temp+1));
        alloc = new int*[processCount];
        max = new int*[processCount];
        need = new int*[processCount];
        available = new int[resourceCount];
        getline(input,info);
        istringstream ss(info);
        string word;
        for(i=0;i<resourceCount;i++){
            ss >> word;
            available[i] = stoi(word);
        }
        for(i=0;i<processCount;i++){
            alloc[i] = new int[resourceCount];
            getline(input,info);
            istringstream ss(info);
            string word;
            for(j=0;j<resourceCount;j++){
                ss >> word;
                alloc[i][j] = stoi(word);
            }
        }
        for(i=0;i<processCount;i++){
            max[i] = new int[resourceCount];
            need[i] = new int[resourceCount];
            getline(input,info);
            istringstream ss(info);
            string word;
            for(j=0;j<resourceCount;j++){
                ss >> word;
                max[i][j] = stoi(word);
                need[i][j] = max[i][j] - alloc[i][j];
            }
        }
    }

    void saveToFile(string filename){
        ofstream out(filename);
        int i,j;
        out << processCount << " " << resourceCount << "\n";
        for(j=0;j<resourceCount-1;j++){
                out << available[j] << " ";
            }
        out << available[resourceCount-1] << "\n";
        for(i=0;i<processCount;i++){
            for(j=0;j<resourceCount-1;j++){
                out << alloc[i][j] << " ";
            }
            out << alloc[i][resourceCount-1] << "\n";
        }
        for(i=0;i<processCount;i++){
            for(j=0;j<resourceCount-1;j++){
                out << max[i][j] << " ";
            }
            out << max[i][resourceCount-1] << "\n";
        }
    }

    int getResourceCount(){
        return resourceCount;
    }

    bool compare(int* a,int* b){
        for(int i=0;i<resourceCount;i++){
            if(a[i] > b[i]){
                return false;
            }
        }
        return true;
    }

    void add(int* a,int* b){
        for(int i=0;i<resourceCount;i++){
            a[i] += b[i];
        }
    }

    void subtract(int* a,int* b){
        for(int i=0;i<resourceCount;i++){
            a[i] -= b[i];
        }
    }

    void printSafeSeqeunce(vector<int> sequence){
        cout << "The Safe Sequence obtained : ";
        for(int i=0;i<processCount-1;i++){
            cout << "P" << sequence[i] << " --> ";
        }
        cout << "P" << sequence[processCount-1] << "\n";
    }

    bool isSafe(){
        int blockedCount = 0;
        bool safe = true;
        int currProcess = 0;

        int* tempAvailable = new int[resourceCount];
        for(int i=0;i<resourceCount;i++){
            tempAvailable[i] = available[i];
        }

        vector<int> sequence;

        while(true){
            if(find(sequence.begin(),sequence.end(),currProcess) == sequence.end()){
                if(compare(need[currProcess],tempAvailable)){
                    add(tempAvailable,alloc[currProcess]);
                    sequence.push_back(currProcess);
                }else{
                    blockedCount++;
                }
            }
            if(currProcess == processCount-1){
                if(blockedCount == 0){
                    break;
                }
                blockedCount = 0;
                currProcess = 0;
            }else{
                currProcess++;
            }
        }

        if(sequence.size() == processCount){
            printSafeSeqeunce(sequence);
            return true;
        }else{
            return false;
        }
    }

    bool request(int process,int* request){
        if(compare(request,need[process]) && compare(request,available)){
            saveToFile("temp.txt");
            subtract(available,request);
            subtract(need[process],request);
            add(alloc[process],request);
            if(isSafe()){
                return true;
            }else{
                readFromFile("temp.txt");
                return false;
            }
        }
        return false;
    }
};

void menu(){
    cout << "Available options : 1] Check for Safe State, 2] Make a request, 3] Save current state to file, 4] Exit\n";
}

int main(){
    menu();
    string filename;
    bool exit = false;
    int choice;
    int* request;
    cout << "\nEnter Input Filename : ";
    cin >> filename;
    Bankers b(filename);
    request = new int[b.getResourceCount()];
    while(!exit){
        cout << "\nEnter your choice : ";
        cin >> choice;
        cout << "\n";
        switch(choice){
            case 1:
                if(b.isSafe()){
                    cout << "The system is in a safe state.\n";
                }else{
                    cout << "The system is in an unsafe state.\n";
                }
                break;
            case 2:
                int pid;
                cout << "Enter Process to make request for : ";
                cin >> pid;
                cout << "Enter Request String : ";
                for(int i=0;i<b.getResourceCount();i++){
                    cin >> request[i];
                }
                cout << "\n";
                if(b.request(pid,request)){
                    cout << "The request can be granted.\n";
                }else{
                    cout << "The request cant be granted.\n";
                }
                break;
            case 3:
                b.saveToFile("output.txt");
                cout << "The current state was saved in output.txt.\n";
                break;
            case 4:
                exit = true;
                cout << "The program will now exit.\n";
                break;
            default:
                cout << "Wrong Choice.\n";
        }
    }
    cout << "\n\t\t\tPrepared by : Vraj Parikh 19CE088";
}
