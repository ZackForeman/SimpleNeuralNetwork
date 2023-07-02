#include <iostream>
#include <cmath>
#include "vectorMath.h"

using namespace std;

double sigmoid(double x){
    return 1/(1+exp(-x));
}

double transferDerivativeSigmoid(double x){
    return x * (1 - x);
}

int main(){
    vector<double> v1 = {2,1,0};
    vector<vector<double>> m1 = {{1,0},{-1,-3},{2,1}};
    vector<double> b1 = {1,2};
    vector<double> out1(2);

    MulMatVec(m1, v1, out1);

    SumVecVec(out1, b1, out1);

    FunVec(sigmoid, out1, out1);

    for(int i = 0; i < out1.size(); i++){
        cout << out1[i] << endl;
    }

    vector<double> v2;
    v2 = v1;
    v2.push_back(1);
    vector<vector<double>> m2;
    m2 = m1;
    m2.push_back(b1);
    vector<double> out2(2);

    MulMatVec(m2,v2,out2);

    FunVec(sigmoid, out2, out2);

    for(int i = 0; i < out1.size(); i++){
        cout << out2[i] << endl;
    }   
}

