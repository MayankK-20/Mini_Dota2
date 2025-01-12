//Alternate code for solving the problem.

#include<iostream>
using namespace std;

class Node{
    int position;
    int health;
    char team;
    int order;
    Node* next=nullptr;

    public:
    Node(int x, int y, char z, int a){
        position = x;
        health = y;
        team = z;
        order = a;
    }

    void push(Node* &head, int x, int y, char z, int a){
        if (head == nullptr){
            head = new Node(x, y, z, a);
            return;
        }
        if (head->next == nullptr  ||  head->position > x){
            if (head->position > x){
                Node* tmp = new Node(x, y, z, a);
                tmp->next = head;
                head = tmp;
                return;
            }
            head -> next = new Node(x, y, z, a);
            return;
        }
        Node* tmp = head;
        while (tmp->next!=nullptr && tmp->next->position<x){
            tmp = tmp->next;
        }
        if (tmp->next==nullptr){
            tmp->next=new Node(x, y, z, a);
            return;
        }
        Node* toInsert = new Node(x, y, z, a);
        toInsert->next = tmp->next;
        tmp->next = toInsert;
    }

    void fight(Node* &head){
        if (head == nullptr){
            return;
        }
        if (head->next==nullptr){
            return;
        }
        int fighting=1;
        while (fighting>0){
            fighting = 0;
            Node* tmp = head;
            Node* prev = nullptr;
            while (tmp!=nullptr && tmp->next != nullptr){
                if (tmp->team=='R' && tmp->team != tmp->next->team){
                    fighting++;
                    if (tmp->health > tmp->next->health){
                        tmp->health--;
                        Node* toDel = tmp->next;
                        tmp->next = toDel->next;
                        delete toDel;
                    }
                    else if(tmp->health < tmp->next->health){
                        tmp->next->health--;
                        if (prev==nullptr){
                            head=tmp->next;
                            Node* toDel=tmp;
                            tmp=tmp->next;
                            delete toDel;
                        }
                        else{
                            Node* toDel=tmp;
                            tmp=tmp->next;
                            prev->next = tmp;
                            delete toDel;
                        }
                    }
                    else{
                        if (prev==nullptr){
                            Node* toDel=tmp;
                            tmp=tmp->next;
                            Node* toDel2=tmp;
                            tmp=tmp->next;
                            head = tmp;
                            delete toDel;
                            delete toDel2;
                        }
                        else{
                            Node* toDel=tmp;
                            tmp=tmp->next;
                            Node* toDel2=tmp;
                            tmp=tmp->next;
                            prev->next = tmp;
                            delete toDel;
                            delete toDel2;
                        }
                    }
                }
                else{
                    prev = tmp;
                    tmp = tmp->next;
                }
            }
        }
        return;
    }

    void output(Node* head){
        if (head==nullptr){
            cout<<" ]\n";
            return;
        }
        if (head->next==nullptr){
            cout<<head->health<<" ]\n";
            return;
        }
        Node* min=head;
        Node* tmp=head;
        Node* prev=nullptr;
        while (tmp!=nullptr && tmp->next!=nullptr){
            if (tmp->next->order < min->order){
                prev=tmp;
                min=tmp->next;
            }
            tmp=tmp->next;
        }
        cout<<min->health<<", ";
        if (min==head){
            head = head->next;
            delete min;
        }
        else{
            prev->next = min->next;
            delete min;
        }
        output(head);
    }

    void display(Node* head){
        if (head == nullptr){
            cout<<"List is empty\n";
            return;
        }
        if (head->next == nullptr){
            cout<<"[ "<<head->position<<", "<<head->health<<", "<<head->team<<", "<<head->order<<" ]\n";
            return;
        }
        cout<<"[ "<<head->position<<", "<<head->health<<", "<<head->team<<", "<<head->order<<" ] --> ";
        display(head->next);
    }
};

int main(){
    
    int n;
    cout<<"Size of Array: ";
    cin>>n;
    int position[n];
    int health[n];
    string team;
    Node* head = nullptr;
    cout<<"Input positions of the heroes with a space: ";
    for (int i=0; i<n; i++){
        cin>>position[i];
    }
    cout<<"Input health of the heroes with a space: ";
    for (int i=0; i<n; i++){
        cin>>health[i];
    }
    cout<<"Input team: ";
    cin>>team;
    for (int i=0; i<n; i++){
        (*head).push(head, position[i], health[i], team[i], i);
    }
    (*head).fight(head);
    cout<<"Output: [ ";
    (*head).output(head);

    return 0;
}
