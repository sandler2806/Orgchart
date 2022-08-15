#include <iostream>
#include "string"
#include "sources/OrgChart.hpp"


using namespace ariel;
using namespace std;
int main(){
    OrgChart<string> organization;
    string str="";
    string str2="";
    int num=0;
    bool loop=true;
    do {
        cout << "welcome to the main program," << endl;
        cout << "insert 1 to create/change the root" << endl;
        cout << "insert 2 to add child for an exist node" << endl;
        cout << "insert 3 to print the current tree" << endl;
        cout << "insert 4 to end the program" << endl;
        cin >> num;
        switch (num) {
            case 1:
                cout << "insert the root data" << endl;
                cin >> str;
                organization.add_root(str);

                break;
            case 2:
                cout << "insert the parent data" << endl;
                cin >> str;
                cout << "insert child data" << endl;
                cin >> str2;
                organization.add_sub(str,str2);
                break;
            case 3:
                cout<<organization<<endl;
                break;
            case 4:
                loop= false;
                cout<<"goodbye!";
                break;

        }

    } while (loop);



    return 1;
}