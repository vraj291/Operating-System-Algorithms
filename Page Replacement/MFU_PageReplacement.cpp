#include <bits/stdc++.h>
using namespace std;

class Map{

    map<int,int> frequency;
    map<int,int> indexes;
    int max_size;

    public:

    Map(int size):max_size(size){}

    int findMFU(){
        int max = INT_MIN,index = -1;
        for(auto i : frequency){
            if(i.second == max){
                if(indexes[i.first] < indexes[index]){
                    max = i.second;
                    index = i.first;
                }
            }else if(i.second > max){
                max = i.second;
                index = i.first;
            }
        }
        return index;
    }

    void add(int page,int index){
        if(indexes.size() == max_size){
            int temp = findMFU();
            cout << "Page " << temp << " replaced\n";
            indexes.erase(temp);
            frequency.erase(temp);
        }
        indexes[page] = index;
        frequency[page] = 1;
    }

    bool find(int page,int index){
        if(indexes.find(page) != indexes.end()){
            //indexes[page] = index;
            frequency[page]++;
            return true;
        }
        return false;
    }
};

void MFU(string refString,int frames){

    int i,pageFaults=0,hits=0;
    Map pages(frames);
    for(i=0;i<refString.length();i++){
        if(pages.find(int(refString.at(i))-48,i)){
            cout << "Page Hit for " << refString.at(i) << "\n";
            hits++;
        }else{
            pageFaults++;
            cout << "Page Fault for " << refString.at(i) << "\n";
            pages.add(int(refString.at(i))-48,i);
        }
    }
    cout << "\nNumber of page hits : " << hits << "\n";
    cout << "Number of page faults : " << pageFaults << "\n";
}

int main(){

    string refString = "70120304230321201701";
    int frames = 3;

    cout << "Given Reference String : " << refString << "\n\n";

    MFU(refString,frames);

    cout << "\n\n\t\t\t Prepared by : Vraj Parikh 19CE088";
}
