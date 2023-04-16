#include<iostream>
#include<cmath>
#include "NeuralNetwork.h"
#include "loadData.h"

using namespace std;

double sigmoid(double x){
    return 1/(1+exp(-x));
    //return (exp(x)-exp(-x))/(exp(x)+exp(-x));
}

double transferDerivativeSigmoid(double x){
    return sigmoid(x) * (1 - sigmoid(x));
    //return 1-(sigmoid(x)*sigmoid(x));
}

int main(){
    NeuralNetwork network;

    //Layer inputLayer(4,4,sigmoid, transferDerivativeSigmoid);
    //Layer hiddenLayer(4,4,sigmoid,transferDerivativeSigmoid);
    Layer outputLayer(4,3,sigmoid, transferDerivativeSigmoid);

    //network.addHiddenLayer(inputLayer);
    //network.addHiddenLayer(hiddenLayer);
    network.addHiddenLayer(outputLayer);

    vector<vector<double>> inputs;
    vector<vector<double>> outputs;
    vector<vector<double>> orderInputs;
    vector<vector<double>> orderOutputs;

    importDataSet(orderInputs, orderOutputs, inputs, outputs);

    vector<vector<double>> predicts;

    double sumError;
    int epochs = 10000;

    vector<double> queryInput1{
        5.1,3.5,1.4,0.2
    };
    vector<double> queryInput2{
        6.4,3.2,4.5,1.5
    };
    vector<double> queryInput3{
        5.9,3.0,5.1,1.8
    };

    vector<double> queryOutput;
    
    queryOutput = network.query(queryInput1);

    for(int i = 0; i < queryOutput.size(); i++){
        cout << queryOutput[i] << " ";
    }    
    cout << "" << endl;

    queryOutput = network.query(queryInput2);

    for(int i = 0; i < queryOutput.size(); i++){
        cout << queryOutput[i] << " ";
    }    
    cout << "" << endl;

    queryOutput = network.query(queryInput3);

    for(int i = 0; i < queryOutput.size(); i++){
        cout << queryOutput[i] << " ";
    }    
    cout << "" << endl;

    cout << "Accuracy before training : " << network.accuracy(inputs, outputs) << endl;

    NeuralNetwork best;
    double lowest = __DBL_MAX__;

    for(int i = 0; i < epochs; i++){
        sumError = 0;

        predicts = network.test(inputs);

        for(int j = 0; j < predicts.size(); j++){
            sumError += (predicts[j][0] - outputs[j][0])*(predicts[j][0] - outputs[j][0])+
            (predicts[j][1] - outputs[j][1])*(predicts[j][1] - outputs[j][1])+
            (predicts[j][2] - outputs[j][2])*(predicts[j][2] - outputs[j][2]);
        }

        //cout << sumError << endl;

        if(sumError < lowest){
            best = network;
            lowest = sumError;
        }

        network.train(inputs, outputs, 0.9);
    }

    queryOutput = network.query(queryInput1);

    for(int i = 0; i < queryOutput.size(); i++){
        cout << queryOutput[i] << " ";
    }    
    cout << "" << endl;

    queryOutput = network.query(queryInput2);

    for(int i = 0; i < queryOutput.size(); i++){
        cout << queryOutput[i] << " ";
    }    
    cout << "" << endl;

    queryOutput = network.query(queryInput3);

    for(int i = 0; i < queryOutput.size(); i++){
        cout << queryOutput[i] << " ";
    }    
    cout << "" << endl;

    queryOutput = best.query(queryInput1);

    for(int i = 0; i < queryOutput.size(); i++){
        cout << queryOutput[i] << " ";
    }    
    cout << "" << endl;

    queryOutput = best.query(queryInput2);

    for(int i = 0; i < queryOutput.size(); i++){
        cout << queryOutput[i] << " ";
    }    
    cout << "" << endl;

    queryOutput = best.query(queryInput3);

    for(int i = 0; i < queryOutput.size(); i++){
        cout << queryOutput[i] << " ";
    }    
    cout << "" << endl;

    cout << "Accuracy after training : " << network.accuracy(inputs, outputs) << endl;

    vector<vector<double>> aThirdInputs(50);
    vector<vector<double>> aThirdOutputs(50);
    vector<vector<double>> bThirdInputs(50);
    vector<vector<double>> bThirdOutputs(50);
    vector<vector<double>> cThirdInputs(50);
    vector<vector<double>> cThirdOutputs(50);

    for(int i = 0; i < 50; i++){
        aThirdInputs[i] = orderInputs[i];
        aThirdOutputs[i] = orderOutputs[i];
    }
    for(int i = 50; i < 100; i++){
        bThirdInputs[i-50] = orderInputs[i];
        bThirdOutputs[i-50] = orderOutputs[i];
    }
    for(int i = 100; i < 150; i++){
        cThirdInputs[i-100] = orderInputs[i];
        cThirdOutputs[i-100] = orderOutputs[i];
    }

    cout << "Accuracy on first set : " << network.accuracy(aThirdInputs, aThirdOutputs) << endl;
    cout << "Accuracy on second set : " << network.accuracy(bThirdInputs, bThirdOutputs) << endl;
    cout << "Accuracy on third set : " << network.accuracy(cThirdInputs, cThirdOutputs) << endl;

    // print weights and work out what is ahppening

    //network.printWeights();

    cout << "BEST: "<<endl;
    cout << "Accuracy after training : " << best.accuracy(inputs, outputs) << endl;

    cout << "Accuracy on first set : " << best.accuracy(aThirdInputs, aThirdOutputs) << endl;
    cout << "Accuracy on second set : " << best.accuracy(bThirdInputs, bThirdOutputs) << endl;
    cout << "Accuracy on third set : " << best.accuracy(cThirdInputs, cThirdOutputs) << endl;

}