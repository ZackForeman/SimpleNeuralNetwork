#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

void importDataSet(vector<vector<double>> &orderedInput, vector<vector<double>> &orderedOutput, vector<vector<double>> &unorderedInput, vector<vector<double>> &unorderedOutput){

    fstream inputFile;
    string number;

    // Open the file.
    inputFile.open("/home/zack-ubuntu/Projects/MatrixVectorMultiple/out/Iris.csv", ios::in);

    if (!inputFile)
    {
        cout << "Could not open file 2" << endl;
    }
    // Read the numbers from the file and
    // display them.

    int i;
    while (inputFile >> number)
    {
        i=0;
        vector<double> currentInput;
        vector<double> currentOutput(3);
        stringstream ss(number);
        string word;
        while (!ss.eof()) {
            getline(ss, word, (char)',');
            if(i >= 1 && i <= 4){
                currentInput.push_back(stod(word));
            }else if(i == 5){
                if(word == "Iris-setosa"){
                    currentOutput[0]=1;
                    currentOutput[1]=0;
                    currentOutput[2]=0;
                }else if(word == "Iris-versicolor"){
                    currentOutput[0]=0;
                    currentOutput[1]=1;
                    currentOutput[2]=0;
                }else if(word == "Iris-virginica"){
                    currentOutput[0]=0;
                    currentOutput[1]=0;
                    currentOutput[2]=1;
                }else{
                    cout << "fail" << endl;
                }
            }
            i++;
        }

        orderedInput.push_back(currentInput);
        orderedOutput.push_back(currentOutput);
        unorderedInput.push_back(currentInput);
        unorderedOutput.push_back(currentOutput);
    }

    // Randomise Input 

    srand (time(NULL));
    for(int i = 0; i < unorderedInput.size(); i++){
        int nextIndex  = rand() % unorderedInput.size();

        vector<double> tempInput = unorderedInput[i];
        vector<double> tempOutput = unorderedOutput[i];

        unorderedInput[i] = unorderedInput[nextIndex];
        unorderedOutput[i] = unorderedOutput[nextIndex];

        unorderedInput[nextIndex] = tempInput;
        unorderedOutput[nextIndex] = tempOutput;

    }

    // Close the file.

    inputFile.close();
}