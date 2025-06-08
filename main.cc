#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>

using namespace std;

void createNote(const string name) {
    ifstream in("./" + name + ".txt");
    ofstream out(name + ".html");

    out << "<!DOCTYPE html>\n";
    out << "<html>\n";
    out << "<head>\n";
    out << "    <meta charset=\"UTF-8\">\n";
    out << "    <title>Notebook</title>\n";
    out << "    <link rel=\"stylesheet\" href=\"style.css\" />\n";
    out << "</head>\n";
    out << "<body>\n";
    out << "    <script src=\"https://cdn.jsdelivr.net/npm/marked/marked.min.js\"></script>\n";
    out << "    <div id=\"content\">\n";
    out << "        <h1>" << name << "</h1>\n";

    string line, block;
    bool md = false, latex = false, code = false;

    while (getline(in, line)) {
        if (line == "<<") {
            md = true;
            block.clear();
        } else if (line == ">>" && md && !code && !latex) {
            out << "<div class='markdown'>" << block << "</div>\n";
            md = false;
        } else if (line == "((" && !md && !latex) {
            out << "<div class='codeblock'>\n";
            code = true;
            block.clear();
        } else if (line == "))" && code) {
            out << block;
            out << "</div>";
            code = false;
        } else if (line == "{{" && !md && !code) {
            latex = true;
            block.clear();
        } else if (line == "}}" && latex) {
            out << block;
            latex = false;
        } else if (md) {
            block += line + "\n";
        } else if (code) {
            block += "<div class='code'>" + line + "</div>\n";
        } else {
            block += "<div class='latex'>\\[" + line + "\\]</div>\n";
        }
    }

    out << "    </div>\n";
    out << "    <script id=\"MathJax-script\" async src=\"https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-mml-chtml.js\"></script>\n";
    out << "    <script>\n";
    out << "      document.querySelectorAll('.markdown').forEach(block => {\n";
    out << "        block.innerHTML = marked.parse(block.textContent.trim());\n";
    out << "      });\n";
    out << "    </script>\n";


    out << "</body>\n";
    out << "</html>\n";

    in.close();
    out.close();

    #ifdef __APPLE__
        system(("open " + name + ".html").c_str());
    #elif _WIN32
        system("start notebook.html");
    #else
        system("xdg-open notebook.html");
    #endif
}

// should be either "exe create name" or "exe open name" or "exe delete name"
int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage:\n" << "./exe create <name>\n" << "./exe open <name>\n" << "./exe delete <name>" << endl;
    }

    string noteName = argv[2];
    string command = argv[1];
    string txtpath = "./" + noteName + ".txt";
    string htmlpath = "./" + noteName + ".html";

    if (command == "create") {
        ofstream file{txtpath};
        file.close();
        string cmd = "vim " + txtpath;
        system(cmd.c_str());
        createNote(txtpath);
    } else if (command == "open") {
        if (!filesystem::exists(txtpath)) {
            cerr << "That notebook doesn't exist!" << endl;
            return 1;
        }
        createNote(txtpath);
    } else {
        cerr << "Wrong command used!" << endl;
        return 1;
    }
}