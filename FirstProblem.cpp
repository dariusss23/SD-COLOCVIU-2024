#include <iostream>
#include <string>
#include <cstring>

using namespace std;

string s;
int n;

struct Node{
    string info;
    Node* next;
};

void addFirst(Node* &head, string value){
    Node *p = new Node;
    p->next = head;
    p->info = value;
    head=p;
}

string top(Node* head){
    return head->info;
}

void popFirst(Node* &head){
    if (head){
        Node* oldHead = head;
        head=head->next;
        delete oldHead;
    }
}

bool emptyS(Node* head){
    return head == nullptr;
}

int main(){
    Node* head = nullptr;
    cin>>n;
    cin.ignore();
    for (int i=1;i<=n;i++){
        getline(cin, s);
        if (s == "pwd"){
            if (emptyS(head)==true) cout<<'/'<<'\n';
            else cout<<top(head)<<'\n';
        }
        else{
            if (s.substr(0,3) == "cd "){
                string path = s.substr(3);
                if (path == ".."){
                    if (emptyS(head) == false){
                        popFirst(head);
                    }
                }
                else addFirst(head, path);
            }
        }
    }
}
