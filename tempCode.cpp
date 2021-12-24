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

    // PriorityQueue<int> pq(5);
    // pq.insert(operationEntity<int>{1, userInfo(1, "insert")});
    // pq.insert(operationEntity<int>{2, userInfo(2, "insert")});
    // pq.insert(operationEntity<int>{3, userInfo(3, "insert")});
    // pq.insert(operationEntity<int>{4, userInfo(4, "insert")});
    // pq.print();

    // int *arr = new int[5];
    // arr[0] = 2;
    // arr[1] = 3;
    // arr[2] = 4;
    // arr[3] = 5;
    // arr[4] = 6;
    // PriorityQueue<int> pq(5);
    // PriorityQueue<int> temp(5);
    // operationEntity<int> *entity = new operationEntity<int>[5];
    // entity[0].key = 5;
    // entity[1].key = 2;
    // entity[2].key = 7;
    // entity[3].key = 1;
    // entity[4].key = 3;
    // for (int i = 0; i < 5; i++)
    // {
    //     entity[i]._usr.setUserInfo(i, "insert");
    //     pq.insertData(entity[i]);
    // }
    // temp = pq.buildQueue(entity);
    // temp.print();
    // //pq.print();
    // PriorityQueue<int> pq1(5);
    // if (temp.findMax() != -1)
    // {
    //     cout << "Max = " << temp.findMax() << endl;
    // }
    // // if (pq1.findMin() != -1)
    // // {
    // //     cout << temp.findMin() << endl;
    // // }
    // temp.size();

    // temp.clearHeap();

    // //after clearing heap
    // temp.print();