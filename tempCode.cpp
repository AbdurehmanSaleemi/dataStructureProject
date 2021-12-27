#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#include <iostream>
#include <queue>
#include <list>
#include <vector>
using namespace std;

class userInfo
{
private:
    int id;
    string operationType;

public:
    userInfo()
    {
        id = 0;
        operationType = "";
    }

    // parameterized constructor
    userInfo(int id, string operationType)
    {
        this->id = id;
        this->operationType = operationType;
    }

    // --- funxtion to set userInformation
    void setUserInfo(int id, string operationType)
    {
        this->id = id;
        this->operationType = operationType;
    }

    // --- to access info out of the class
    int getUserId() const
    {
        return this->id;
    }
    string getOperationType()
    {
        return this->operationType;
    }

    void print()
    {
        cout << this->id << " " << this->operationType << endl;
    }
};

// heapItem class
template <typename T>
class operationEntity
{
public:
    T key;         // key to insert data into heap
    userInfo _usr; // object of user class
};

template <typename T>
class PriorityQueue
{
private:
    vector<operationEntity<T>> heap;
    int sizeOfHeap;     // Current number of elements in min heap
    int capacityOfHeap; // maximum possible size of min heap

public:
    PriorityQueue(int capacity)
    {
        this->capacityOfHeap = capacity;
        this->sizeOfHeap = 0;
    }

    //sort in descending order
    void sort(){
        for(int i=0;i<sizeOfHeap;i++){
            for(int j=0;j<sizeOfHeap-i-1;j++){
                if(heap[j].key<heap[j+1].key){
                    swap(heap[j],heap[j+1]);
                }
            }
        }
    }

    void insertData(int key, operationEntity<T> entity)
    {
        if (sizeOfHeap == capacityOfHeap)
        {
            cout << "Heap is full" << endl;
            return;
        }
        heap.insert(heap.begin(), entity);
        sizeOfHeap++;
        int index = sizeOfHeap - 1;
        while (index != 0 && heap[index].key < heap[(index - 1) / 2].key)
        {
            swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    //takes unsorted array and covert it into a priority queue
    PriorityQueue buildQueue(operationEntity<T> *arr)
    {
        PriorityQueue<T> pq(this->capacityOfHeap);
        for (int i = 0; i < this->capacityOfHeap; i++)
        {
            pq.insertData(arr[i]->key, arr[i]);
        }
        pq.sort();
        return pq;
    }

    T findMax()
    {
        if (sizeOfHeap == 0)
        {
            cout << "Heap is empty" << endl;
            return -1;
        }
        return heap[0].key;
    }

    T findMin()
    {
        if (sizeOfHeap == 0)
        {
            cout << "Heap is empty" << endl;
            return -1;
        }
        return heap[sizeOfHeap - 1].key;
    }

    void setKey(int priority, int index){
        heap[index].key = priority;
    }

    int size()
    {
        return sizeOfHeap;  
    }

    void clearHeap()
    {
        heap.clear();
        sizeOfHeap = 0;
    }

    // print the heap
    void print()
    {
        if (sizeOfHeap == 0)
        {
            cout << "Heap is empty" << endl;
            return;
        }
        else
        {
            for (int i = 0; i < sizeOfHeap; i++)
            {
                cout << heap[i].key << "\t";
                cout << heap[i]._usr.getOperationType() << " ";
                cout << endl;
            }
        }
        cout << endl;
    }
    void removeData(int key, operationEntity<T> entity)
    {
        if (sizeOfHeap == 0)
        {
            cout << "Heap is empty" << endl;
            return;
        }
        int index = 0;
        while (index < sizeOfHeap && heap[index].key != key)
        {
            index++;
        }
        if (index == sizeOfHeap)
        {
            cout << "Key not found" << endl;
            return;
        }
        heap[index] = heap[sizeOfHeap - 1];
        sizeOfHeap--;
        int i = index;
        
        while (i < sizeOfHeap)
        {
            if (2 * i + 1 < sizeOfHeap && heap[2 * i + 1].key < heap[i].key)
            {
                if (2 * i + 2 < sizeOfHeap && heap[2 * i + 2].key < heap[2 * i + 1].key)
                {
                    swap(heap[i], heap[2 * i + 2]);
                    i = 2 * i + 2;
                }
                else
                {
                    swap(heap[i], heap[2 * i + 1]);
                    i = 2 * i + 1;
                }
            }
            else if (2 * i + 2 < sizeOfHeap && heap[2 * i + 2].key < heap[i].key)
            {
                swap(heap[i], heap[2 * i + 2]);
                i = 2 * i + 2;
            }
            else
            {
                break;
            }
        }
    }
};



int main(){

    PriorityQueue<int> pq(5);
    pq.insert(operationEntity<int>{1, userInfo(1, "insert")});
    pq.insert(operationEntity<int>{2, userInfo(2, "insert")});
    pq.insert(operationEntity<int>{3, userInfo(3, "insert")});
    pq.insert(operationEntity<int>{4, userInfo(4, "insert")});
    pq.print();

    int *arr = new int[5];
    arr[0] = 2;
    arr[1] = 3;
    arr[2] = 4;
    arr[3] = 5;
    arr[4] = 6;
    PriorityQueue<int> pq(5);
    PriorityQueue<int> temp(5);
    operationEntity<int> *entity = new operationEntity<int>[5];
    entity[0].key = 5;
    entity[1].key = 2;
    entity[2].key = 7;
    entity[3].key = 1;
    entity[4].key = 3;
    for (int i = 0; i < 5; i++)
    {
        entity[i]._usr.setUserInfo(i, "insert");
        pq.insertData(entity[i]);
    }
    temp = pq.buildQueue(entity);
    temp.print();
    //pq.print();
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
}