#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


//Disjoint Set class with move function added (move element a to set b)
//time complexities: move O(ack-1(n)), union O(ack-1(n)), sameSet O(ack-1(n))
//ack-1(n) is the very-slowly growing inverse ackermann function (very close to O(1))
//no error checking, inputs > n or < 0 will seg-fault
struct DisjointSet {
private:
    struct node;
    struct group;
    struct node {
        group *parent;
        ll value;
    };
    struct group {
        group *parent;
        ll sum, size;
    };
    vector<group> groups;
    vector<node> nodes;
    group* find(ll i) {
        if(i < 0 || i > n) return nullptr;
        group *temp = nodes[i].parent;
        while(temp != temp->parent) {
            temp = temp->parent;
        }
        nodes[i].parent = temp;//path compression
        return temp;
    }
    int numOfGroups, n;
public:
    DisjointSet(ll n) {//input the number of nodes
        this->n = numOfGroups = n;
        nodes.resize(n+1);
        groups.resize(n+1);
        for(ll i = 0; i <= n; i++) {
            groups[i].sum = nodes[i].value = i;
            groups[i].parent = nodes[i].parent = &groups[i];
            groups[i].size = 1;
        }
    }
    void move(ll a, ll b) {//move first node to second's group
        group *groupA = find(a), *groupB = find(b);
        if(groupA == groupB || groupA == nullptr || groupB == nullptr) return;//same group
        //update sum
        groupA->sum -= a;
        groupB->sum += a;
        //update size
        groupA->size--;
        groupB->size++;
        //update node pointers
        nodes[a].parent = groupB;
    }
    void merge(ll a, ll b) {//union
        group *groupA = find(a), *groupB = find(b);
        if(groupA == groupB || groupA == nullptr || groupB == nullptr) return;//same group
        numOfGroups--;
        if(groupA->size > groupB->size) {//union by size
            /*moving all nodes from group b to group a*/
            //update sums
            groupA->sum += groupB->sum;
            groupB->sum = 0;
            //update size
            groupA->size += groupB->size;
            groupB->size = 0;
            groupB->parent = groupA;
        } else {
            /*moving all nodes from group a to group b*/
            //update sums
            groupB->sum += groupA->sum;
            groupA->sum = 0;
            //update size
            groupB->size += groupA->size;
            groupA->size = 0;
            groupA->parent = groupB;
        }
    }
    void print(ll n) {cout << find(n)->size << ' ' << find(n)->sum << endl;}
    bool sameSet(ll a, ll b) {return find(a) == find(b);}
    int numGroups() {return this->numOfGroups;}
};

vector<int> p(1000001,-1);//change size here if needed
int find(int x) {return p[x] < 0 ? x : p[x] = find(p[x]);}
void merge(int x, int y) {
    if((x=find(x)) == (y=find(y))) return;
    if(p[y] < p[x]) swap(x,y);
    p[x] += p[y];
    p[y] = x;
}

int main() {
    ll n, k;
    while(cin >> n >> k) {
        DisjointSet ds(n);
        while(k--) {
            ll opp, a, b;
            cin >> opp;
            switch(opp) {
            case 1://union
                cin >> a >> b;
                ds.merge(a, b);
                break;
            case 2://move
                cin >> a >> b;
                ds.move(a, b);
                break;
            case 3://print
                cin >> a;
                ds.print(a);
                break;
            }
        }
    }
    return 0;
}
