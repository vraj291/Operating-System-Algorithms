#include <bits/stdc++.h>
using namespace std;

class PriorityQueue{

    struct Node{
        int page;
        int next;
    };

    struct CompareNext {
        bool operator()(Node const& p1, Node const& p2){
            return p1.next < p2.next;
        }
    };

    priority_queue<Node, vector<Node>, CompareNext> Q;
    unordered_set<int> pages;
    int max_size;

    public:

    PriorityQueue(int size):max_size(size){}

    void add(int page,int next){
        if(Q.size() == max_size){
            pages.erase(Q.top().page);
            Q.pop();
        }
        Q.push({page,next});
        pages.insert(page);
    }

    bool find(int page){
        if(pages.find(page) != pages.end()){
            return true;
        }
        return false;
    }
};

int findNext(string refString,int index,char page){
    for(int i=index+1;i<refString.length();i++){
        if(refString.at(i) == page){
            return i;
        }
    }
    return INT_MAX;
}

void Optimal(string refString,int frames){

    int i,pageFaults=0,hits=0;
    PriorityQueue pages(frames);
    for(i=0;i<refString.length();i++){
        if(pages.find(int(refString.at(i))-48)){
            cout << "Page Hit for " << refString.at(i) << "\n";
            hits++;
        }else{
            pageFaults++;
            cout << "Page Fault for " << refString.at(i) << "\n";
            pages.add(int(refString.at(i))-48,findNext(refString,i,refString.at(i)));
        }
    }
    cout << "\nNumber of page hits : " << hits << "\n";
    cout << "Number of page faults : " << pageFaults << "\n";
}

int main(){

    string refString = "70120304230323";
    int frames = 4;

    cout << "Given Reference String : " << refString << "\n\n";

    Optimal(refString,frames);

    cout << "\n\n\t\t\t Prepared by : Vraj Parikh 19CE088";
}

