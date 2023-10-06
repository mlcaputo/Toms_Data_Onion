#include "FileReader.h"
#include <string>
#include <vector>
#include <fstream> 
using namespace std;

string readFile(string name){
    string output = "";
    string fileStream;

    ifstream file(name);

    while(getline(file, fileStream)){
        output += fileStream;
    }

    file.close();

    return output;

}

void makeTextFile(string name, string text){
    ofstream out(name);
    out << text;
    out.close();
}

