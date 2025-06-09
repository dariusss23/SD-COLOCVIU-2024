/*

#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

int h[1005];

struct Node{
    int val;
    Node* next;
};

int parent(int i){
    return i/2;
}

int left (int i){
    return 2*i;
}

int right (int i){
    return 2*i+1;
}

void HeapUp(int k){
    int dad = parent(k);
    while (dad >= 1 && h[dad] > h[k]){
        swap (h[dad], h[k]);
        k = dad;
        dad = parent(k);
    }
}

void HeapDown(int k, int dim){
    while (left(k) <= dim){
        int smallest = left(k);
        int r = right(k);

        if (r <= dim && h[r] < h[smallest])
            smallest = r;

        if (h[k] > h[smallest]){
            swap(h[k], h[smallest]);
            k=smallest;
        }
        else break;
    }
}

void add(int val, int &dim){
    h[++dim] = val;
    HeapUp(dim);
}

int extractMin(int &dim){
    if (dim==0) return -1;
    int min = h[1];
    h[1] = h[dim--];
    HeapDown(1,dim);
    return min;
}

int main()
{
    int n;
    cin>>n;
    int nr=0;
    for (int i=1;i<=n;i++){
        int optiune;
        cin>>optiune;
        if (optiune == 1){
            int nod;
            cin>>nod;
            add(nod, nr);
        }
        else{
            cout << extractMin(nr) << '\n';
        }
    }
    return 0;
}

*/

/*

#include <iostream>
#include <stack>

using namespace std;

int n, a[1005], NG[1005];

stack <int> st;

int main(){
    cin>>n;
    for (int i=1;i<=n;i++)
        cin>>a[i];

    for (int i=1;i<=n;i++){
        NG[i]=-1;
        if (st.empty()==true) st.push(i);
        else{
            while (st.empty()==false &&  a[i]>a[st.top()]){
                NG[st.top()]=a[i];
                st.pop();
            }
            st.push(i);
        }
    }

    for (int i=1;i<=n;i++){
        cout<<NG[i]<<" ";
    }
    return 0;
}

*/

/*

#include <iostream>

using namespace std;

int h[1005];

int parent(int i){
    return i/2;
}

int left(int i){
    return 2*i;
}

int right(int i){
    return 2*i+1;
}

void HeapUp(int k){
    int t = parent(k);
    while (t>=1 && h[t]>h[k]){
        swap(h[k], h[t]);
        k=t;
        t=parent(k);
    }

}

void HeapDown(int k, int dim){
    while (left(k)<=dim){
        int best = left(k);
        int r = right(k);

        if (r <= dim && h[r] < h[best])
            best = r;

        if (h[k] > h[best])
            swap(h[k], h[best]);
        else break;

        k = best;
    }
}

int extractHeap(int &dim){
    if (dim==0) return -1;
    int minim = h[1];
    h[1]=h[dim--];
    HeapDown(1, dim);
    return minim;
}

void add(int val, int &dim){
    h[++dim]=val;
    HeapUp(dim);
}

int main(){
    int n, nr=0;
    cin>>n;
    for (int i=1;i<=n;i++){
        int x;
        cin>>x;
        add(x, nr);
    }

    while (nr){
        cout<<extractHeap(nr)<<" ";
    }
}

*/

/*

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

*/


#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

struct elemHeap {
    int dist;
    int val;
};

elemHeap h[1005];

int parent(int i) { return i/2; }
int left(int i) { return 2*i; }
int right(int i) { return 2*i+1; }

bool better(elemHeap a, elemHeap b) {
    if (a.dist!=b.dist) return a.dist > b.dist;
    return a.val > b.val;
}

void HeapUp(int k) {
    int d = parent(k);
    while (d >= 1 && better(h[k],h[d])) {
        swap(h[k],h[d]);
        k = d;
        d = parent(k);
    }
}

void HeapDown(int k, int dim) {
    while (left(k)<=dim) {
        int best = left(k);
        int r = right(k);
        if (r <= dim && better(h[r], h[best]))
            best = r;

        if (better(h[best], h[k])) {
            swap(h[k], h[best]);
            k = best;
        } else break;
    }
}

void addHeap(int& dim, int dist, int val) {
    h[++dim]={dist, val};
    HeapUp(dim);
}

bool cmp(elemHeap a, elemHeap b) {
    return a.val<b.val;
}

int main() {
    int n,k,x,dim=0;
    cin>>n>>k>>x;

    for (int i=1;i<=n;i++) {
        int val;
        cin>>val;
        int dist = abs(val - x);
        if (dim<k) {
            addHeap(dim, dist, val);
        }
        else if ( dist<h[1].dist ||(dist == h[1].dist && val < h[1].val) ) {
                h[1] = {dist, val};
                HeapDown(1, dim);
              }
    }

    sort(h+1,h+k+1,cmp);
    for (int i=1;i<=k;i++)
        cout<<h[i].val<< " ";
}
