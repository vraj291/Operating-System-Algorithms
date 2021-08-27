#include <bits/stdc++.h>
using namespace std;

class CircularQueue{

    struct Page{
        int page;
        int ref;
        struct Page* next;
    };
    Page* head;
    Page* curr;
    int len;
    int maxsize;

    public:

    CircularQueue(int l): maxsize(l),head(NULL),curr(NULL),len(0){}

    Page* createPage(int page){
        Page* ptr = (Page*)malloc(sizeof(Page));;
        ptr->page = page;
        ptr->ref = 0;
        ptr->next = head;
        return ptr;
    }

    void insertAtEnd(Page* page){
        len++;
        if(head == NULL){
            page->next = page;
            head = page;
        }else{
            Page* temp=head;
            while(temp->next != head){
                temp = temp->next;
            }
            temp->next = page;
        }
        if(len == maxsize){
            curr = head;
        }
    }

    void display(){
        Page* temp = head;
        if(temp == NULL) return;
        while(temp->next != head){
            cout << temp->page << "\n";
            temp = temp->next;
        }
        cout << temp->page << "\n";
        cout << "\n";
    }

    void insertAtPos(Page* page){
        Page *prev=NULL;
        while(curr->ref == 1){
            prev = curr;
            curr->ref = 0;
            curr = curr->next;
        }
        cout << "Page " << curr->page << " replaced.\n";
        page->next = curr->next;
        if(prev == NULL){
            Page* temp = head;
            while(temp->next != curr){
                temp = temp->next;
            }
            temp->next = page;
        }else{
            prev->next = page;
        }
        if(curr == head){
            head = page;
        }
        curr = curr->next;
    }

    void add(int page){

        Page* newPage = createPage(page);
        if(len >= maxsize){
            insertAtPos(newPage);
        }else{
            insertAtEnd(newPage);
        }
    }

    bool find(int page){
        Page* temp = head;
        if(temp == NULL){
            return false;
        }
        while(temp->next != head){
            if(temp->page == page){
                temp->ref = 1;
                return true;
            }
            temp = temp->next;
        }
        if(temp->page == page){
            temp->ref = 1;
            return true;
        }
        return false;
    }
};

void SecondChance(string refString,int frames){
    int i,pageFaults=0,hits=0;
    CircularQueue pages(frames);
    for(i=0;i<refString.length();i++){
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

    string refString = "041424342404142434";
    int frames = 3;

    cout << "Given Reference String : " << refString << "\n\n";

    SecondChance(refString,frames);

    cout << "\n\n\t\t\t Prepared by : Vraj Parikh 19CE088";
}
