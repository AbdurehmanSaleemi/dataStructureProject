#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class userInfo{
private:
    int id;
    string operationType;
public:
    userInfo(){
        id = 0;
        operationType = "";
    }

    // parameterized constructor
    userInfo(int id, string operationType){
        this->id = id;
        this->operationType = operationType;
    }

    // --- funxtion to set userInformation
    void setUserInfo(int id, string operationType){
        this->id = id;
        this->operationType = operationType;
    }

    // --- to access info out of the class
    int getUserId() const{
        return this->id;
    }
    string getOperationType(){
        return this->operationType;
    }

    void print(){
        cout << this->id << " " << this->operationType << endl;
    }

};


// heapItem class
template <typename T>
class operationEntity{
public:
    T key;            // key to insert data into heap
    userInfo _usr;      // object of user class
};

template <typename T>
class PriorityQueue{
private:
    vector<operationEntity<T>> heap;
    int sizeOfHeap;                 // Current number of elements in min heap
    int capacityOfHeap;             // maximum possible size of min heap

public:

    PriorityQueue(int capacity){
        this->capacityOfHeap = capacity;
        this->sizeOfHeap = 0;
    }

    PriorityQueue buildQueue(operationEntity<T> * arr){
        for(int i = 0; i < capacityOfHeap; i++){
            heap.insert(heap.end(), arr[i]);
        }
        return *this;
    }

    void insert(operationEntity<T> entity){
        if(sizeOfHeap == capacityOfHeap){
            cout << "Heap is full" << endl;
            return;
        }
        heap.push_back(entity);
        sizeOfHeap++;
        int index = sizeOfHeap - 1;
        while(index != 0 && heap[index].key < heap[(index - 1) / 2].key){
            swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    T findMax(){
        return heap[0];     // return first index
    }

    T findMin(){
        return heap[heap.size()];   // return last index
    }

    // print the heap
    void print(){
        for(int i = 0; i < sizeOfHeap; i++){
            cout << heap[i].key << " ";
            cout << heap[i]._usr.getOperationType() << " ";
            cout << endl;
        }
        cout << endl;
    }
};


int main(){

    // PriorityQueue<int> pq(5);
    // pq.insert(operationEntity<int>{1, userInfo(1, "insert")});
    // pq.insert(operationEntity<int>{2, userInfo(2, "insert")});
    // pq.insert(operationEntity<int>{3, userInfo(3, "insert")});
    // pq.insert(operationEntity<int>{4, userInfo(4, "insert")});
    // pq.print();

    int *arr = new int[5];
    arr[0] = 2; arr[1] = 3; arr[2] = 4; arr[3] = 5; arr[4] = 6;
    PriorityQueue<int> pq(5);
    PriorityQueue<int> temp(5);
    operationEntity <int> *entity = new operationEntity<int>[5];
    for(int i = 0; i < 5; i++){
        entity[i].key = arr[i];
        entity[i]._usr.setUserInfo(i, "insert");
        pq.insert(entity[i]);
    }
    temp = pq.buildQueue(entity);
    temp.print();
    return 0;
}