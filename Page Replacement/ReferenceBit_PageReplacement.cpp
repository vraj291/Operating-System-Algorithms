#include <bits/stdc++.h>
using namespace std;

class Page{

    int page;
    int ref;
    string history;

    public:

    Page(int p): page(p),ref(0){
        history = "";
        for(int i=0;i<8;i++){
            history += "0";
        }
    }

    void refer(){
        ref = 1;
    }

    bool isPage(int p){
        if(p == page)
            return true;
        return false;
    }

    void updateHistory(){
        char c = '0';
        if(ref == 1){
            c = '1';
        }
        history = c + history.substr(0,history.length()-1);
        ref = 0;
    }

    int getHistory(){
        return stoi(history,0,2);
    }
};

class Pages{

    vector<Page> pages;
    int len;

    public:

    Pages(int l):len(l){}

    bool find(int page){
        for(int i=0;i<pages.size();i++){
            if(pages[i].isPage(page)){
                pages[i].refer();
                return true;
            }
        }
        return false;
    }

    void add(int page){
        Page newPage(page);
        if(pages.size() == len){
            int index = findMinimum();
            pages[index] = newPage;
        }else{
            pages.push_back(newPage);
        }
    }

    void updateHistories(){
        for(int i =0;i<pages.size();i++){
            pages[i].updateHistory();
        }
    }

    int findMinimum(){
        int min=INT_MAX,index=-1;
        for(int i=0;i<pages.size();i++){
            if(pages[i].getHistory() < min){
                min = pages[i].getHistory();
                index = i;
            }
        }
        return index;
    }
};



void Process(string refString,int frames){

    int i,pageFaults=0,hits=0;
    Pages pages(frames);
    for(i=0;i<refString.length();i++){
        pages.updateHistories();
        if(pages.find(int(refString.at(i))-48)){
            cout << "Page Hit for " << refString.at(i) << "\n";
            hits++;
        }else{
            pageFaults++;
            cout << "Page Fault for " << refString.at(i) << "\n";
            pages.add(int(refString.at(i))-48);
        }
    }
    cout << "\nNumber of page hits : " << hits << "\n";
    cout << "Number of page faults : " << pageFaults << "\n";
}

int main(){

    string refString = "70120304230323";
    int frames = 4;

    cout << "Given Reference String : " << refString << "\n\n";

    Process(refString,frames);

    cout << "\n\n\t\t\t Prepared by : Vraj Parikh 19CE088";
}

