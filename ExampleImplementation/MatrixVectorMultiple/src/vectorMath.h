#include <vector>
#include <functional>

using namespace std;

void MulMatVec(vector<vector<double>> &m, vector<double> &v, vector<double> &out){
    int matRows = m.size();
    int matCols = m[0].size();

    double total = 0;

    for(int i = 0; i < matCols; i++){
        total = 0;
        for(int j = 0; j < matRows; j++){
            total += v[j] * m[j][i];
        }
        out[i] = total;
    } 

}

void MulScaVec(double &s, vector<double> &v, vector<double> &out){
    for(int i = 0; i < v.size(); i++){
        out[i] = s * v[i];
    }
}

void MulScaMat(double &s, vector<vector<double>> &m, vector<vector<double>> &out){
    for(int i = 0; i < m.size(); i++){
        for(int j = 0; j < m[0].size(); j++){
            out[i][j] = s * m[i][j];
        }
    }
}

void SumVecVec(vector<double> &v1, vector<double> &v2, vector<double> &out){
    for(int i = 0; i < v1.size(); i++){
        out[i] = v1[i] + v2[i];
    }
}

void SumMatMat(vector<vector<double>> &m1, vector<vector<double>> &m2, vector<vector<double>> &out){
    for(int i = 0; i < m1.size(); i++){
        for(int j = 0; j < m1[0].size(); j++){
            out[i][j] = m1[i][j] + m2[i][j]; // for functions like this loop over the vector functions            
        }
    }
}

void MulVecVec(vector<double> &v1, vector<double> &v2, vector<double> &out){
    for(int i = 0; i < v1.size(); i++){
        out[i] = v1[i] * v2[i];
    }
}

void FunVec(function<double(double)> func, vector<double> &v1, vector<double> &out){
    for(int i = 0; i < v1.size(); i++){
        out[i] = func(v1[i]);
    }
}

void RanVec(vector<double> &v){
    srand((unsigned) time(NULL));
    for(int i = 0; i < v.size(); i++){
        v[i] = (float) rand()/RAND_MAX;
    }

}

void RanMat(vector<vector<double>> &m){
    srand((unsigned) time(NULL));
    for(int i = 0; i < m.size(); i++){
        RanVec(m[i]);
    }
}

void InvertMatrix(vector<vector<double>> &m, vector<vector<double>> &out){
    for(int i = 0; i < m.size(); i++){
        for(int j = 0; j < m[0].size(); j++){
            out[j][i] = m[i][j];        
        }        
    }
}

void ColRowMat(vector<double> &c, vector<double> &r, vector<vector<double>> &m){
    for(int i = 0; i < c.size(); i++){
        for(int j = 0; j < r.size(); j++){
            m[i][j] = c[i]*r[j];
        }
    }
}

void argmax(vector<vector<double>> &v, vector<int> &index){
    int max;
    double current;

    for(int i = 0; i < v.size(); i++){
        current = 0;
        max = 0;
        for(int j = 0; j < v[0].size(); j++){
            if(v[i][j] > current){
                max = j;
                current = v[i][j];
            }
        }
        index[i] = max;

    } 
}

