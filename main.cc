#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <cstdlib>

using namespace std;

void create() {
    string noteName;
    cout << "Enter name of new notebook: ";
    getline(cin, noteName);

    string path = "./" + noteName + ".txt";
    ofstream file(path);
    file.close();

    string cmd = "vim " + path;

    system(cmd.c_str());
}

int main() {

    create();

    return 0;
}

