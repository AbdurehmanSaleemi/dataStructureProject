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

    void sort()
    {
        for (int i = 0; i < sizeOfHeap; i++)
        {
            for (int j = 0; j < sizeOfHeap - i - 1; j++)
            {
                if (heap[j].key < heap[j + 1].key)
                {
                    swap(heap[j], heap[j + 1]);
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
};

template <typename T>
struct Node
{
    PriorityQueue<T> *userQueue;
    int size;
    // Node* next;
    T fileId;

    Node()
    {
        userQueue = new PriorityQueue<T>(20);
        this->size = 20;
    }
    Node(int size)
    {
        userQueue = new PriorityQueue<T>(size);
        this->size = size;
    }

    T getFileId()
    {
        return fileId;
    }
};

template <class T>
class HashTable
{
private:
    list<Node<T>> *files;
    int sizeOfTable;

public:
    HashTable()
    {
        this->sizeOfTable = 20;
        files = new list<Node<T>>[sizeOfTable];
    }
    HashTable(int size)
    {
        this->sizeOfTable = size;
        files = new list<Node<T>>[sizeOfTable];
    }

    int calculateHash(int key)
    {
        return key % sizeOfTable;
    }

    void insert(T fileId)
    {
        int hash = calculateHash(fileId);
        Node<T> *node = new Node<T>(20);
        node->fileId = fileId;
        files[hash].push_back(*node);
    }

    void print()
    {
        for (int i = 0; i < sizeOfTable; i++)
        {
            cout << "Hash value " << i << ": ";
            for (auto it = files[i].begin(); it != files[i].end(); it++)
            {
                cout << it->fileId << " ";
                if(it->userQueue->size() != 0){
                    it->userQueue->print();
                }
            }
            cout << endl;
        }
    }

    void request_access(int user_id, int file_id)
    {
        int check = 0;                  // to keep the check in loop
        int f = calculateHash(file_id); // to calculate the index by hashing
        for (auto it = files[f].begin(); it != files[f].end(); it++)
        {
            if (it->fileId == file_id) // it will see whether the file id exists
            {
                check = 1;
                break;
            }
        }
        if (check != 1) // if the file id doesnot exist, exit from the program
        {
            cout << "\n-------------The file ID you entered doesnot "
                    "exist------------\n";
            return;
        }

        // if file id exist, we will take the users priority
        cout << "\nNow, we need your priority!";
        cout << "\nFor inputting a number for priority, input 1 and for "
                "specifying a priority as highest or lowest, press any other "
                "number\n";
        int a;
        cin >> a;
        // only these two if else conditions are left in this function, rest the
        // function is complete
        auto it = files[f].begin();
        if (a == 1)
        {
            cout << "\nEnter your priority: ";
            int priority;
            cin >> priority;
            operationEntity<T> *entity = new operationEntity<T>;
            entity->key = priority;
            entity->_usr.setUserInfo(user_id, "Read");
            it->userQueue->insertData(priority, *entity);
        }
        else
        {
            // in this else condition, take highest or lowest and then find max or
            // min  priority and insert accordingly
        }
    }

    ~HashTable()
    {
        delete[] files;
    }
};

int main()
{
    HashTable<int> table(20);
    table.insert(5100);
    table.insert(5200);
    table.insert(5300);
    table.insert(5101);
    table.insert(6101);
    table.insert(6102);
    table.insert(55103);
    table.insert(66102);
    table.insert(6103);
    table.request_access(001, 5300);
    cout << endl;
    table.print();
    return 0;
}