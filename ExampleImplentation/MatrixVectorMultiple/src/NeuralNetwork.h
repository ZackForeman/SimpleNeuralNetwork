#include <vector>
#include <functional>
#include "layer.h"

using namespace std;


class NeuralNetwork{
    vector<Layer> layers;
    int inputLayerSize;
    int ouputLayerSize;

    public:
        void addHiddenLayer(Layer hidden){
            layers.push_back(hidden);
        }

        vector<vector<double>> test(vector<vector<double>> input){
            for(int i = 0; i < layers.size(); i++){
                layers[i].setTrain(false);
            }

            vector<vector<double>> output(input.size());
            for(int i = 0; i < input.size(); i++){
                for(int j = 0; j < layers.size(); j++){
                    input[i] = layers[j].forwardPropagate(input[i]);
                }
                output[i] = input[i];
            }
            return output;
        }

        vector<double> query(vector<double> input){
            for(int j = 0; j < layers.size(); j++){
                input = layers[j].forwardPropagate(input);
            }
            return input;
        }

        void train(vector<vector<double>> input, vector<vector<double>> output, double learningRate){
            for(int i = 0; i < layers.size(); i++){
                layers[i].setTrain(true);
            }

            vector<double> currentInput;
            vector<double> propError;

            for(int i = 0; i < input.size(); i++){
                currentInput = input[i];

                for(int j = 0; j < layers.size(); j++){
                    currentInput = layers[j].forwardPropagate(currentInput);
                }                
                for(int j = layers.size()-1; j >= 0; j--){             
                    if(j == layers.size()-1){
                        propError = layers[j].calculateInitialError(output[i]);;                

                    }else{
                        propError = layers[j].backPropagate(propError);
                   
                    }
                }

                for(int j = 0; j < layers.size(); j++){
                    layers[j].updateWeights(learningRate);

                }

            }
 
        }

        double accuracy(vector<vector<double>> input, vector<vector<double>> output){
            vector<vector<double>> predicted = test(input);
            vector<int> argMaxPredicted(predicted.size());
            vector<int> argMaxOutput(output.size());

            argmax(predicted, argMaxPredicted);
            argmax(output, argMaxOutput);
            
            double correct = 0;
            double total = (double) output.size();
            for(int i = 0; i < argMaxPredicted.size(); i++){
                if(argMaxPredicted[i] == argMaxOutput[i]){
                    correct++;
                }
            }
            
            return (correct/total)*100;

        }

        void printWeights(){
            for(int i = 0; i < layers.size(); i++){
                layers[i].printWeight();
                cout << "" << endl;
            }
        }


};