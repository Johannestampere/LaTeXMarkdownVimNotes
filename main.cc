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

void renderNote(const string name) {
    ifstream in{"./" + name + ".txt"};
    // stores HTML code to render notebook
    ofstream out("note.html");

    // write into the html file
    out << R"(
        <html>
            <head>
                <meta charset="UTF-8">
                <title>Notebook</title>
                <link rel="stylesheet" href="style.css" />
            </head>
            <body>
                <div id="content">
                    content
                </div>

                <script type="module" src="render.ts"></script>
            </body>
        </html>
    )";

    string line, block;

    bool md = false, latex = false;

    while (getline(in, line)) {
        if (line == "<<") {
            md = true;
            block.clear();
        } else if (line == ">>" && md = true) {
            out << "<div class='markdown'>" << block << "</div>\n";
            md = false;
        } else if (line == "((") {
            latex = true;
            block.clear();
        } else if (line == "))" && latex == true) {
            out << "<div class='latex'>\\[" << block << "\\]</div>\n";
            latex = false;
        } else if (md || latex) {
            block += line + "\n";
        }
    }

}

int main() {

    return 0;
}

