#include <bits/stdc++.h>
using namespace std;

class SSTF{

    int start;
    struct request{
        int position;
        bool satisfied;
    };
    vector<request> requests;
    int requestCount;

    public:

    SSTF(int arr[],int len,int pos):start(pos),requestCount(len){
        for(int i=0;i<requestCount;i++){
            requests.push_back({arr[i],false});
        }
    }

    void printSequence(vector<int> sequence){
        cout << "The sequence of servicing requests : \n\n";
        cout << start << " --> ";
        for(int i=0;i<requestCount-1;i++){
            cout << sequence[i] << " --> ";
        }
        cout << sequence[requestCount-1] << "\n";
    }

    int getNextRequest(int currPos){
        int index,diff = INT_MAX;
        for(int i=0;i<requestCount;i++){
            if(!requests[i].satisfied && diff >= abs(currPos-requests[i].position)){
                diff = abs(currPos-requests[i].position);
                index = i;
            }
        }
        requests[index].satisfied = true;
        return requests[index].position;
    }

    void schedule(){
        int cylindersTraversed = 0;
        vector<int> outputSequence;
        int currPos = start,nextPos;

        for(int i=0;i<requestCount;i++){
            nextPos = getNextRequest(currPos);
            outputSequence.push_back(nextPos);
            cylindersTraversed += abs(currPos-nextPos);
            currPos = nextPos;
        }
        printSequence(outputSequence);
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

    SSTF obj(cylinders,len,start);
    obj.schedule();

    cout << "\n\n\t\t\tPrepared by : Vraj Parikh 19CE088";
}

