#include <bits/stdc++.h>
using namespace std;

class Queue{

    struct Node{
        int page;
        struct Node* next;
    };

    Node* head;
    int len;
    int max_size;

    public:

    Queue(int size):max_size(size){
        head = NULL;
        len = 0;
    }

    // Create a new page entry
    Node* create(int i){
        Node* ptr = (Node*)malloc(sizeof(Node));;
        ptr->page = i;
        ptr->next = NULL;
        return ptr;
    }

    // Add a new page entry
    void add(int i){
        Node* ptr = create(i);
        if(head == NULL){
            head = ptr;
            len++;
            cout << "\n";
        }else{
            if(len == max_size){
                _delete();
            }else{
                cout << "\n";
            }
            Node* temp = head;
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = ptr;
            len++;
        }
    }

    void display(){
        Node* temp = head;
        while(temp != NULL){
            cout << temp->page << "\n";
            temp = temp->next;
        }
        cout << "\n";
    }

    // Delete the first page entry
    void _delete(){
        Node* temp = head;
        if(len == 1){
            head = NULL;
            len = 0;
        }else if (len == 2){
            head = head->next;
            head->next = NULL;
            len = 1;
        }else{
            head = head->next;
            len--;
        }
        cout << "Page " << temp->page << " was replaced.\n";
        free(temp);
    }

    // Find an existing page entry
    bool find(int page){
        if(head == NULL) return false;
        Node* temp = head;
        while(temp != NULL){
            if(temp->page == page){
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    int size(){
        return len;
    }
};

void FIFO(string refString,int frames){

    int i,pageFaults=0,hits=0;
    Queue pages(frames);
    for(i=0;i<refString.length();i++){
        if(pages.find(int(refString.at(i))-48)){
            cout << "Page Hit for " << refString.at(i) << "\n";
            hits++;
        }else{
            pageFaults++;
            cout << "Page Fault for " << refString.at(i) << ". ";
            pages.add(int(refString.at(i))-48);
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

    FIFO(refString,frames);

    cout << "\n\t\t\t Prepared by : Vraj Parikh 19CE088";
}
