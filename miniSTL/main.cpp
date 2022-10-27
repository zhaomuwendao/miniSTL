#include "bits/stdc++.h"
using namespace std;
#include "Vector.h"
class Person{
public:
    Person(){
        cout<<"构造函数"<<endl;
    }
    ~Person(){
        cout<<"析构函数"<<endl;
    }
    Person(Person &p){
        cout<<"拷贝构造"<<endl;
    }
    Person(const Person& p) {
        cout << "const 拷贝构造" << endl;
    }
};
int main(){
    miniSTL::Vector<int> v(10);
    for(int i=0;i<10;i++){
        v[i]=i;
    }
    v.erase(0);
    for(auto i:v){
        cout<<i<<endl;
    }
}