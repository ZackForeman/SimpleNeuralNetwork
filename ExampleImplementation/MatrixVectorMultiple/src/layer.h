#include <vector>
#include <functional>
#include "vectorMath.h"

using namespace std;

class Layer{
    int inputSize;
    int outputSize;
    vector<vector<double>> weight;
    //vector<double> bias;
    vector<double> lastOutput;
    vector<double> lastInput;
    vector<double> lastError;
    bool trainMode = true;
    function<double(double)> activation;
    function<double(double)> activationDerivative;
    
    public:
        Layer(int iSize, int oSize, function<double(double)> a, function<double(double)> t){
            inputSize = iSize+1;
            outputSize = oSize;
            vector<vector<double>> w(inputSize, vector<double> (outputSize));
            RanMat(w);
            weight = w;
            /*vector<double> b(outputSize);
            RanVec(b);
            bias = b;*/
            vector<double> l(outputSize);
            lastOutput = l;
            activation = a;
            activationDerivative = t;
        }

        void setTrain(bool m){
            trainMode = m;
        }

        vector<double> forwardPropagate(vector<double> input){
            vector<double> output(outputSize);
            /*MulMatVec(weight, input, output);
            SumVecVec(output, bias, output);
            FunVec(activation, output, output);*/

            input.push_back(1);
            MulMatVec(weight, input, output);
            FunVec(activation, output, output);

            if(trainMode){
                lastOutput = output;
                lastInput = input;
            }
            return output;                        
        }

        vector<double> calculateInitialError(vector<double> &expected){
            vector<double> error(expected.size());
            vector<double> negExpected(expected.size());
            vector<double> actDerivative(expected.size());
            vector<double> recalcValue(lastOutput.size());
            double invert = -1;

            MulMatVec(weight, lastInput, recalcValue);            
            MulScaVec(invert, expected, negExpected);
            SumVecVec(lastOutput, negExpected, error);
            FunVec(activationDerivative, recalcValue, actDerivative);
            MulVecVec(error, actDerivative, error);
            
            lastError = error;
            vector<double> propError(inputSize-1);
            vector<vector<double>> invertMatrix(outputSize, vector<double> (inputSize));
            InvertMatrix(weight, invertMatrix);
            MulMatVec(invertMatrix, error, propError);            

            return propError;

        }

        vector<double> backPropagate(vector<double> error){
            vector<double> newError(error.size());
            vector<double> delta;
            vector<double> actDerivative(lastOutput.size());
            vector<double> recalcValue(lastOutput.size());

            MulMatVec(weight, lastInput, recalcValue); 
            FunVec(activationDerivative, recalcValue, actDerivative);
            MulVecVec(error, actDerivative, newError);

            lastError = newError;
            vector<double> propError(inputSize-1);            
            vector<vector<double>> invertMatrix(outputSize, vector<double> (inputSize));
            InvertMatrix(weight, invertMatrix); 
            MulMatVec(invertMatrix, error, propError);

            return propError;
        }

        void updateWeights(double &learningRate){
            vector<vector<double>> newWeight(inputSize, vector<double> (outputSize));
            double negLearningRate = learningRate*-1;

            vector<vector<double>> delta(lastInput.size(), vector<double>(lastError.size()));

            ColRowMat(lastInput, lastError, delta);
            
            MulScaMat(negLearningRate, delta, delta);

            SumMatMat(weight, delta, newWeight);

            weight = newWeight;
        }

        void printWeight(){
            for(int i = 0; i < weight.size(); i++){
                for(int j = 0; j < weight[0].size(); j++){
                    cout << weight[i][j] << " ";                
                }
                cout << "" << endl;
            }
        }
};