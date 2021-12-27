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

    void setCapacity(int capacity)
    {
        this->capacityOfHeap = capacity;
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

    void buildQueue(){
        sort();
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

    int getUserId(){
        return heap[0]._usr.getUserId();
    }

    string getOperationType(){
        return heap[0]._usr.getOperationType();
    }

    T getKey(){
        return heap[0].key;
    }

    userInfo getUserInfo(){
        return heap[0]._usr;
    }
};

template <typename T>
struct Node
{
    PriorityQueue<T> *userQueue;
    int size;
    PriorityQueue<T> *tempQueue;
    T fileId;

    Node()
    {
        userQueue = new PriorityQueue<T>(20);
        tempQueue = new PriorityQueue<T>(20);
        this->size = 20;
    }
    Node(int size)
    {
        userQueue = new PriorityQueue<T>(size);
        tempQueue = new PriorityQueue<T>(size);
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
                    cout << endl;
                    PriorityQueue<T> pq = *it->userQueue;
                    pq.print();
                }
            }
            cout << endl;
        }
    }

    // request file access and enter the user in queue
    void requestAccess(int userId, int priority, int fileId, string accessType){
        int hash = calculateHash(fileId);
        auto it = files[hash].begin();
        while(it != files[hash].end()){
            if(it->fileId == fileId){
                operationEntity<T> *entity = new operationEntity<T>;
                entity->key = priority;
                entity->_usr.setUserInfo(userId, accessType);
                it->userQueue->insertData(priority,*entity);
                cout << "Added in the Queue\n";
                break;
            }
            it++;
        }
    }

    void buildQueueForFile(int fileId){
        int hash = calculateHash(fileId);
        auto it = files[hash].begin();
        while(it != files[hash].end()){
            if(it->fileId == fileId){
                it->userQueue->buildQueue();
                break;
            }
            it++;
        }
    }

    void releaseAccess(int fileId){
        int hash = calculateHash(fileId);
        auto it = files[hash].begin();
        while(it != files[hash].end()){
            if(it->fileId == fileId){
                if(it->userQueue->getOperationType() == "Read"){
                    while(it->userQueue->getOperationType() == "Read"){
                        operationEntity<T> *entity = new operationEntity<T>;
                        entity->key = it->userQueue->getKey();
                        entity->_usr = it->userQueue->getUserInfo();
                        it->tempQueue->insertData(it->userQueue->getKey(),*entity);
                        it->userQueue->removeData(it->userQueue->getKey());
                        buildQueueForFile(fileId);
                    }
                    break;
                }
                else{
                    operationEntity<T> *entity = new operationEntity<T>;
                    entity->key = it->userQueue->getKey();
                    entity->_usr = it->userQueue->getUserInfo();
                    it->tempQueue->insertData(it->userQueue->getKey(),*entity);
                    it->userQueue->removeData(it->userQueue->getKey());
                    buildQueueForFile(fileId);
                }
            }
            it++;
        }
    }

    void printUserAccessingFile(int fileId){
        int hash = calculateHash(fileId);
        auto it = files[hash].begin();
        while(it != files[hash].end()){
            if(it->fileId == fileId){
                cout << "Users accessing the file: ";
                it->tempQueue->print();
                break;
            }
            it++;
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
    table.requestAccess(001, 5, 5300, "Read");
    table.requestAccess(002, 2, 5300, "Read");
    table.requestAccess(003, 1, 5300, "Write");
    table.requestAccess(004, 8, 5300, "Read");
    table.requestAccess(005, 4, 5300, "Write");
    table.requestAccess(006, 10, 5300, "Read");
    table.requestAccess(007, 12, 5300, "Read");
    table.buildQueueForFile(5300);
    cout << endl;
    table.print();
    cout << endl;
    table.releaseAccess(5300);
    cout << endl;
    table.printUserAccessingFile(5300);
    cout << endl;
    table.print();
    return 0;
}