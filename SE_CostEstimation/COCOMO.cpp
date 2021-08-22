#include <bits/stdc++.h>
using namespace std;

void calcOrganic(int loc){
    double kloc = loc/1000;
    double effort = 2.4 * pow(kloc,1.05);
    double tdev = 2.5 * pow(effort,0.38);
    cout << setprecision(4);
    cout << "Effort in person months : " << effort << "\n";
    cout << "Development period in months : " << tdev << "\n";
}

void calcSemiDetached(int loc){
    double kloc = loc/1000;
    double effort = 3.0 * pow(kloc,1.12);
    double tdev = 2.5 * pow(effort,0.35);
    cout << setprecision(4);
    cout << "Effort in person months : " << effort << "\n";
    cout << "Development period in months : " << tdev << "\n";
}

void calcEmbedded(int loc){
    double kloc = loc/1000;
    double effort = 3.6 * pow(kloc,1.20);
    double tdev = 2.5 * pow(effort,0.32);
    cout << setprecision(4);
    cout << "Effort in person months : " << effort << "\n";
    cout << "Development period in months : " << tdev << "\n";
}

int main(){
    int loc,choice;
    cout << "Enter lines of code : ";
    cin >> loc;
    cout << "\n1] Organic Development\n2] Semi-detached Development\n3] Embedded Development\n";
    cout << "\nEnter choice : ";
    cin >> choice;
    cout << "\n";
    switch(choice){
        case 1:
            calcOrganic(loc);
            break;
        case 2:
            calcSemiDetached(loc);
            break;
        case 3:
            calcEmbedded(loc);
            break;
        default:
            cout << "Wrong Choice.";
    }
    cout << "\n\n\t\t\tPrepared by :  Vraj Parikh 19CE088";
}
