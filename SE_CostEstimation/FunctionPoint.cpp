#include <bits/stdc++.h>
using namespace std;

int table[5][3] = {
    {3,4,6},
    {4,5,7},
    {3,4,6},
    {7,10,15},
    {5,7,10}
};

vector<pair<int,int>> getInputs(){

    vector<pair<int,int>> factors;
    int weight,rate;

    cout << "\nRate Scale for weights: 0] Low, 1] Average, 2] High\n\n";

    cout << "Enter User Inputs Weight : ";
    cin >> weight;
    cout << "Enter User Inputs Rate : ";
    cin >> rate;
    factors.push_back({rate,weight});

    cout << "\nEnter User Outputs Weight : ";
    cin >> weight;
    cout << "Enter User Outputs Rate : ";
    cin >> rate;
    factors.push_back({rate,weight});

    cout << "\nEnter User Inquiries Weight : ";
    cin >> weight;
    cout << "Enter User Inquiries Rate : ";
    cin >> rate;
    factors.push_back({rate,weight});

    cout << "\nEnter User Files Weight : ";
    cin >> weight;
    cout << "Enter User Files Rate : ";
    cin >> rate;
    factors.push_back({rate,weight});

    cout << "\nEnter External Interface Weight : ";
    cin >> weight;
    cout << "Enter External Interface Rate : ";
    cin >> rate;
    factors.push_back({rate,weight});

    return factors;
}

int getScale(){

    int scale;

    cout << "Rate Scale for factors: 0] No Influence, 1] Incidental, 2] Moderate, 3] Average, 4] Significant, 5] Essential\n\n";
    cout << "Enter Scale : ";
    cin >> scale;

    return scale;
}

double calcF(int scale){
    return (double)(14 * scale);
}

double calcCAF(int scale){
    double CAF = (0.65 + (0.01 * calcF(scale)));
    cout << "Complexity Adjustment Factor (CAF) : " << CAF << "\n";
    return CAF;
}

double calcUFP(vector<pair<int,int>> factors){
    double sum = 0;
    for(int i=0;i<factors.size();i++){
        sum += (factors[i].second * table[i][factors[i].first]);
    }
    cout << "Unadjusted Function Point (UFP) : " << sum << "\n";
    return sum;
}

void calcFP(int scale,vector<pair<int,int>> factors){
    double FP = (calcUFP(factors) * calcCAF(scale));
    cout << "Calculated Function Point (FP) : " << FP << "\n";
}

int main(){

    int scale = getScale();
    vector<pair<int,int>> factors = getInputs();

    cout << "\nFunctional Point Analysis : \n";
    calcFP(scale,factors);
    cout << "\n\n\t\t\tPrepared by: Vraj Parikh 19CE088";
}
