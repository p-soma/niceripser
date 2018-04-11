/**
    File: niceripser.cpp
    Author: Paul Soma

    program to take a ripser output file and save the persistence in each
    dimension as a comma-delimited text file

    usage: niceripser [filename] 
  */

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>

using std::cout;
using std::string;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::strcmp;


int main(int argc, char* argv[])
{
    // comand line arg
    string ripserFile = argv[1];    // ripser output file name
    
    // open ripser input file
    ifstream f(ripserFile);

    string line;

    // store the 3 header lines in a file "header.txt"
    ofstream headerFile("header.txt");
    for (int i = 1; i <= 3; i++)
    {
        getline(f,line);
        headerFile << line << "\n";
    }
    headerFile.close();

    // get rid of the line "persistence in dimension 0:"
    getline(f,line);

    // create output file for dimension 0 persistence

    int dim = 0;
    string outFileName = "dim_0.txt";
    ofstream outFile(outFileName);

    while(getline(f, line))
    {
       
        // each dimension is preceded by a line such as:
        //      "persistence intervals in dim 0:"
        // thus we have a new dimension each time we see "persistence"
        if (line.find("persistence") != string::npos) 
        {
            dim++;
            // close the previous output file
            outFile.close();
            // open an output text file for this dimension
            outFileName = "dim_" + std::to_string(dim) + ".txt";
            outFile.open(outFileName);
            continue;
        }

        // parse each line and add to file

        line.erase(0, line.find("[") + 1);      // remove leading " ["
        line.pop_back();                        // remove trailing ")"

        // in the case of infinite persistence, assign a death time of -0.1
        if (line.find(' ') == line.length()-1) 
        {
            line.pop_back();
            line.append("-0.1");
        }

        outFile << line << "\n"; 
 
    }

    outFile.close();

    f.close();

    return 0;

}
