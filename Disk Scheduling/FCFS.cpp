#include <bits/stdc++.h>
using namespace std;

class FCFS{

    int start;
    int* requests;
    int requestCount;

    public:

    FCFS(int arr[],int len,int pos):start(pos),requestCount(len){
        requests = new int[len];
        for(int i=0;i<requestCount;i++){
            requests[i] = arr[i];
        }
    }

    void printSequence(){
        cout << "The sequence of servicing requests : \n\n";
        cout << start << " --> ";
        for(int i=0;i<requestCount-1;i++){
            cout << requests[i] << " --> ";
        }
        cout << requests[requestCount-1] << "\n";
    }

    void schedule(){
        int cylindersTraversed = 0;
        int currPos = start;
        for(int i=0;i<requestCount;i++){
            cylindersTraversed += abs(currPos-requests[i]);
            currPos = requests[i];
        }
        printSequence();
        cout << "\nTotal cylinders traversed : " << cylindersTraversed << "\n";
    }
};

int main(){

    int start = 53;
    int cylinders[] = {98,183,37,122,14,124,65,67};
    int len = sizeof(cylinders)/sizeof(cylinders[0]);

    cout << "Starting Position : " << start << "\n";
    cout << "Given requests to service : [";
    for(int i=0;i<len-1;i++){
        cout << cylinders[i] << ", ";
    }
    cout << cylinders[len-1] << "]\n\n";

    FCFS obj(cylinders,len,start);
    obj.schedule();

    cout << "\n\n\t\t\tPrepared by : Vraj Parikh 19CE088";
}
