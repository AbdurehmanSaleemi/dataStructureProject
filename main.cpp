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


template <typename T>
class operationEntry{
private:
    T key;            // key to insert data into heap
    userInfo _usr;      // object of user class
};



int main(){
}