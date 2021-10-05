#include <bits/stdc++.h>
using namespace std;

class Map{

    map<int,int> indexes;
    int max_size;

    public:

    Map(int size):max_size(size){}

    // Find page entry to be replaced
    int findMRU(){
        int max = INT_MIN,index = -1;
        for(auto i : indexes){
            if(i.second > max){
                max = i.second;
                index = i.first;
            }
        }
        return index;
    }

    // Create a new page entry
    void add(int page,int index){
        if(indexes.size() == max_size){
            int temp = findMRU();
            cout << "Page " << temp << " was replaced.\n";
            indexes.erase(temp);
        }else{
            cout << "\n";
        }
        indexes[page] = index;
    }

    // Find an existing page entry
    bool find(int page,int index){
        if(indexes.find(page) != indexes.end()){
            indexes[page] = index;
            return true;
        }
        return false;
    }

    void display(){
        map<int,int>::iterator it;
        for(it = indexes.begin();it!=indexes.end();it++){
            cout << it->first << "\n";
        }
        cout << "\n";
    }
};

void MRU(string refString,int frames){

    int i,pageFaults=0,hits=0;
    Map pages(frames);
    for(i=0;i<refString.length();i++){
        if(pages.find(int(refString.at(i))-48,i)){
            cout << "Page Hit for " << refString.at(i) << ".\n";
            hits++;
        }else{
            pageFaults++;
            cout << "Page Fault for " << refString.at(i) << ". ";
            pages.add(int(refString.at(i))-48,i);
        }
    }
    cout << "\nNumber of page hits : " << hits << "\n";
    cout << "Number of page faults : " << pageFaults << "\n\n";
    cout << "Final allotment : \n";
    pages.display();
}

int main(){

    string refString = "70120304230323";
    int frames = 4;

    cout << "Given Reference String : " << refString << "\n";
    cout << "Number of Frames : " << frames << "\n\n";

   MRU(refString,frames);

    cout << "\n\t\t\t Prepared by : Vraj Parikh 19CE088";
}
