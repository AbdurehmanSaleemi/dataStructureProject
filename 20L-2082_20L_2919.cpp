#include <iostream>
#include <queue>
#include <list>
#include <vector>
#include <fstream>
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
        operationType = " ";
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
    vector<operationEntity<T>> heap; // vector to store heap
    int sizeOfHeap;                  // Current number of elements in min heap
    int capacityOfHeap;              // maximum possible size of min heap

public:
    PriorityQueue(int capacity)
    {
        this->capacityOfHeap = capacity;
        this->sizeOfHeap = 0;
    }

    void setCapacity(int capacity)
    {
        this->capacityOfHeap = capacity;
    }

    //sort in descending order
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

    // insert data into heap
    void insertData(int key, operationEntity<T> entity)
    {
        if (sizeOfHeap == capacityOfHeap)
        {
            cout << "Heap is full" << endl;
            return;
        }
        else
        {
            heap.insert(heap.begin(), entity);
            sizeOfHeap++;
            int index = sizeOfHeap - 1;
            while (index != 0 && heap[index].key < heap[(index - 1) / 2].key)
            {
                swap(heap[index], heap[(index - 1) / 2]);
                index = (index - 1) / 2;
            }
        }
    }

    //takes unsorted array and covert it into a priority queue
    PriorityQueue buildQueue(PriorityQueue *arr)
    {
        PriorityQueue<T> pq(arr->capacityOfHeap);
        for (int i = 0; i < arr->capacityOfHeap; i++)
        {
            pq.insertData(arr->heap[i].key, arr->heap[i]);
        }
        pq.sort();
        return pq;
    }

    // build the queue
    void buildQueue()
    {
        sort();
    }

    //returns the minimum element of the heap
    T findMax()
    {
        if (sizeOfHeap == 0)
        {
            cout << "Heap is empty" << endl;
            return -1;
        }
        return heap[0].key;
    }

    //returns the minimum element of the heap
    T findMin()
    {
        if (sizeOfHeap == 0)
        {
            cout << "Heap is empty" << endl;
            return -1;
        }
        return heap[sizeOfHeap - 1].key;
    }

    // set the key of the element at index i
    void setKey(int priority, int index)
    {
        heap[index].key = priority;
    }

    // return current heap size
    int size()
    {
        return sizeOfHeap;
    }

    // clear the heap completely
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
                cout << heap[i]._usr.getUserId() << "\t";
                cout << heap[i]._usr.getOperationType() << " ";
                cout << endl;
            }
        }
        cout << endl;
    }

    // this function is used to remove user from the queue based on his key(priority)
    void removeData(int key)
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
        int parent = (index - 1) / 2;
        while (index > 0 && heap[index].key < heap[parent].key)
        {
            swap(heap[index], heap[parent]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    // these functions are returning private data
    int getUserId()
    {
        return heap[0]._usr.getUserId();
    }

    string getOperationType()
    {
        return heap[0]._usr.getOperationType();
    }

    T getKey()
    {
        return heap[0].key;
    }

    bool isEmpty()
    {
        if (heap.empty() == true)
        {
            return true;
        }
        else
        {
            false;
        }
    }

    userInfo getUserInfo()
    {
        return heap[0]._usr;
    }
};

template <typename T>
struct Node
{
    PriorityQueue<T> *userQueue;
    PriorityQueue<T> *tempQueue;
    T fileId;

    // default constructor
    Node()
    {
        userQueue = new PriorityQueue<T>(100);
        tempQueue = new PriorityQueue<T>(100);
        fileId = 0;
    }

    // parameterized constructor
    Node(int size)
    {
        userQueue = new PriorityQueue<T>(size + 100);
        tempQueue = new PriorityQueue<T>(size + 100);
        fileId = 0;
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
    int sizeOfList;

public:
    HashTable()
    {
        this->sizeOfTable = 20;
        files = new list<Node<T>>[sizeOfTable];
        this->sizeOfList = 0;
    }
    HashTable(int size)
    {
        this->sizeOfTable = size;
        files = new list<Node<T>>[sizeOfTable];
        this->sizeOfList = 0;
    }

    //hash function
    int calculateHash(int key)
    {
        return key % sizeOfTable;
    }

    // this function will take fileId as parameter and insert it into the hash table
    void insert(T fileId)
    {
        int hash = calculateHash(fileId);
        Node<T> *node = new Node<T>(100);
        auto it = files[hash].begin();
        while (it != files[hash].end())
        {
            if (it->getFileId() == fileId)
            {
                return;
            }
            it++;
        }
        node->fileId = fileId;
        files[hash].push_back(*node);
    }

    int getSize(int fileId)
    {
        int index = calculateHash(fileId);
        for (auto it = files[index].begin(); it != files[index].end(); it++)
        {
            if (it->getFileId() == fileId)
            {
                return it->userQueue->size();
            }
        }
        return -1;
    }

    // This function is used to print the files in the hash Table
    void print()
    {
        for (int i = 0; i < sizeOfTable; i++)
        {
            for (auto it = files[i].begin(); it != files[i].end(); it++)
            {
                if (files[i].size() == 0)
                {
                    break;
                }
                cout << it->fileId << " ";
                if (it->userQueue->size() != 0)
                {
                    cout << endl;
                    PriorityQueue<T> pq = *it->userQueue;
                    pq.print();
                }
                cout << endl;
            }
        }
    }

    // request file access and enter the user in queue
    void requestAccess(int userId, int priority, int fileId, string accessType)
    {
        int hash = calculateHash(fileId);
        auto it = files[hash].begin();
        while (it != files[hash].end())
        {
            if (it->fileId == fileId)
            {
                operationEntity<T> *entity = new operationEntity<T>;
                entity->key = priority;
                entity->_usr.setUserInfo(userId, accessType);
                it->userQueue->insertData(priority, *entity);
                cout << "Added in the Queue\n";
                break;
            }
            it++;
        }
    }

    // it will update userQueue according to the priorities
    void buildQueueForFile(int fileId)
    {
        int hash = calculateHash(fileId);
        auto it = files[hash].begin();
        while (it != files[hash].end())
        {
            if (it->fileId == fileId)
            {
                it->userQueue->buildQueue();
                break;
            }
            it++;
        }
    }

    // this function will release file access and remove the user from queue
    void grantAndReleaseAccess(int fileId)
    {
        int tempSize = 0;
        int hash = calculateHash(fileId);
        auto it = files[hash].begin();
        while (it != files[hash].end())
        {
            if (it->fileId == fileId)
            {
                tempSize = it->userQueue->size();
                if (it->userQueue->getOperationType() == "Read")
                {
                    while (it->userQueue->getOperationType() == "Read" && tempSize != 0)
                    {
                        operationEntity<T> *entity = new operationEntity<T>;
                        entity->key = it->userQueue->getKey();
                        entity->_usr = it->userQueue->getUserInfo();
                        it->tempQueue->insertData(it->userQueue->getKey(), *entity);
                        it->userQueue->removeData(it->userQueue->getKey());
                        buildQueueForFile(fileId);
                        tempSize--;
                    }
                    break;
                    return;
                }
                else
                {
                    operationEntity<T> *entity = new operationEntity<T>;
                    entity->key = it->userQueue->getKey();
                    entity->_usr = it->userQueue->getUserInfo();
                    it->tempQueue->insertData(it->userQueue->getKey(), *entity);
                    it->userQueue->removeData(it->userQueue->getKey());
                    buildQueueForFile(fileId);
                    tempSize--;
                    break;
                    return;
                }
            }
            it++;
        }
    }

    // this function will print users currently accessing the file
    void printUserAccessingFile(int fileId)
    {
        int hash = calculateHash(fileId);
        auto it = files[hash].begin();
        while (it != files[hash].end())
        {
            if (it->fileId == fileId)
            {
                cout << "Users accessing the file: " << it->fileId << "\n";
                it->tempQueue->print();
                break;
                return;
            }
            it++;
        }
        //cout << "File not Found\n";
    }

    void printFileQueue(int fileId)
    {
        int hash = calculateHash(fileId);
        auto it = files[hash].begin();
        while (it != files[hash].end())
        {
            if (it->fileId == fileId)
            {
                cout << "Users in the queue: " << it->fileId << "\n";
                it->userQueue->print();
                break;
                return;
            }
            it++;
        }
        //cout << "File not Found\n";
    }

    void userInWaiting(int fileId)
    {
        int hash = calculateHash(fileId);
        auto it = files[hash].begin();
        while (it != files[hash].end())
        {
            if (it->fileId == fileId)
            {
                cout << "Users in the Waiting List: " << it->fileId << "\n";
                it->userQueue->print();
                break;
                return;
            }
            it++;
        }
        //cout << "File not Found\n";
    }

    ~HashTable()
    {
        delete[] files;
    }
};

void readFromFile(string filename)
{
    HashTable<int> hashTable(20);
    ifstream file;
    file.open(filename);
    string line;
    int userId[100], fileId[100], priority[100];
    string accessType[100];
    int i = 0;
    if (file.is_open())
    {
        while (!file.eof())
        {
            file >> userId[i] >> priority[i] >> fileId[i] >> accessType[i];
            hashTable.insert(fileId[i]);
            hashTable.requestAccess(userId[i], priority[i], fileId[i], accessType[i]);
            hashTable.buildQueueForFile(fileId[i]);
            i++;
        }
    }
    cout << hashTable.getSize(7010) << endl;
    cout << "---------------------------\n";
    hashTable.printFileQueue(7010);
    hashTable.grantAndReleaseAccess(7010);
    cout << "---------------------------\n";
    hashTable.printUserAccessingFile(7010);
    cout << "---------------------------\n";
    hashTable.userInWaiting(7010);

    file.close();
}

int main()
{
    // HashTable<int> table(20);
    // table.insert(5100);
    // table.insert(5200);
    // table.insert(5300);
    // table.insert(5101);
    // table.insert(6101);
    // table.insert(6102);
    // table.insert(55103);
    // table.insert(66102);
    // table.insert(6103);
    // table.requestAccess(001, 5, 5300, "Read");
    // table.requestAccess(002, 2, 5300, "Read");
    // table.requestAccess(003, 1, 5300, "Write");
    // table.requestAccess(004, 8, 5300, "Read");
    // table.requestAccess(005, 4, 5300, "Write");
    // table.requestAccess(006, 10, 5300, "Read");
    // table.requestAccess(007, 12, 5300, "Read");
    // table.buildQueueForFile(5300);
    // cout << endl;
    // table.print();
    // cout << endl;
    // table.grantAndReleaseAccess(5300);
    // cout << endl;
    // table.printUserAccessingFile(5300);
    // cout << endl;
    // table.print();
    readFromFile("file.txt");
    return 0;
}