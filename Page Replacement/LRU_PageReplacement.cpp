#include <bits/stdc++.h>
using namespace std;

class Map{

    map<int,int> indexes;
    int max_size;

    public:

    Map(int size):max_size(size){}

    int findLRU(){
        int min = INT_MAX,index = -1;
        for(auto i : indexes){
            if(i.second < min){
                min = i.second;
                index = i.first;
            }
        }
        return index;
    }

    void add(int page,int index){
        if(indexes.size() == max_size){
            int temp = findLRU();
            cout << "Page " << temp << " replaced\n";
            indexes.erase(temp);
        }
        indexes[page] = index;
    }

    bool find(int page,int index){
        if(indexes.find(page) != indexes.end()){
            indexes[page] = index;
            return true;
        }
        return false;
    }
};

void LRU(string refString,int frames){

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

    string refString = "70120304230323";
    int frames = 4;

    cout << "Given Reference String : " << refString << "\n\n";

    LRU(refString,frames);

    cout << "\n\n\t\t\t Prepared by : Vraj Parikh 19CE088";
}
