#include <iostream>
#include <queue>
#include <vector>
using namespace std;

void showPriorityQueue(priority_queue<int> pq){
    while(!pq.empty()){
        cout << pq.top() << "  " << endl;
        pq.pop();
    }
}



int main(){
    priority_queue<int> pq;
    pq.push(10);
    pq.push(50);
    pq.push(30);
    pq.push(40);
    showPriorityQueue(pq);
    return 0;
}