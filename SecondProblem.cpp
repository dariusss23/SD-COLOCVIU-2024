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
