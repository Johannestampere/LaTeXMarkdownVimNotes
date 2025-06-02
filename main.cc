#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <cstdlib>

using namespace std;
using namespace std::filesystem;

void create() {
    string noteName;
    cout << "Enter name of new notebook: " << endl;
    getline(cin, noteName);

    string path = "./" + noteName + ".txt";
    ofstream file(noteName);
    file.close();

    string cmd = "vim " + path;

    system(cmd.c_str());
}

int main() {



    return 0;
}

