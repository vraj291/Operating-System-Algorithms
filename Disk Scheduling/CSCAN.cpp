#include <bits/stdc++.h>
using namespace std;

#define TRACKS 200

class CSCAN{

    int start;
    vector<int> requests;
    int requestCount;

    public:

    CSCAN(int arr[],int len,int pos):start(pos),requestCount(len){
        for(int i=0;i<requestCount;i++){
            requests.push_back(arr[i]);
        }
    }

    void printSequence(vector<int> sequence){
        cout << "The sequence of servicing requests : \n\n";
        cout << start << " --> ";
        for(int i=0;i<sequence.size()-1;i++){
            cout << sequence[i] << " --> ";
        }
        cout << sequence[sequence.size()-1] << "\n";
    }

    vector<int> getAuxillaryArray(){
        vector<int> aux;
        aux.push_back(0);
        aux.push_back(start);
        aux.push_back(TRACKS);
        for(int i=0;i<requestCount;i++){
            aux.push_back(requests[i]);
        }
        sort(aux.begin(),aux.end());
        return aux;
    }

    void schedule(){
        int cylindersTraversed = 0,i;
        vector<int> outputSequence;
        vector<int> aux = getAuxillaryArray();
        int startIndex = find(aux.begin(),aux.end(),start) - aux.begin();

        int currIndex = startIndex-1;
        cylindersTraversed += abs(aux[currIndex]-aux[startIndex]);

        for(i=currIndex;i>=1;i--){
            outputSequence.push_back(aux[currIndex]);
            cylindersTraversed += abs(aux[currIndex]-aux[currIndex-1]);
            currIndex--;
        }
        outputSequence.push_back(aux[currIndex]);
        cylindersTraversed += TRACKS;
        currIndex = aux.size()-1;

        for(i=currIndex;i>startIndex+1;i--){
            outputSequence.push_back(aux[currIndex]);
            cylindersTraversed += abs(aux[currIndex]-aux[currIndex-1]);
            currIndex--;
        }
        outputSequence.push_back(aux[currIndex]);

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

    CSCAN obj(cylinders,len,start);
    obj.schedule();

    cout << "\n\n\t\t\tPrepared by : Vraj Parikh 19CE088";
}

