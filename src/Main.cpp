#include <iostream>
#include "../include/Session.h"
using namespace std;

int main(int argc, char** argv){
//    if(argc!=2)
//    {
//        cout << "usage splflix input_file" << endl;
//        return 0;
//    }
    string path = "../include/config2.json";
    Session s(path);
    s.start();
    Session s2 = std::move(s);
    s2.start();
    return 0;
}