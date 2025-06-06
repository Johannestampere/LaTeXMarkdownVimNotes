#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

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
        } else if (line == "{{" && !md && !latex) {
            out << "<div class='codeblock'>\n";
            code = true;
            block.clear();
        } else if (line == "}}" && code) {
            out << block;
            out << "</div>";
            code = false;
        } else if (line == "((" && !md && !code) {
            latex = true;
            block.clear();
        } else if (line == "))" && latex) {
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

int main() {
    string noteName;
    cout << "Notebook name: ";
    getline(cin, noteName);

    string path = "./" + noteName + ".txt";
    ofstream file{path};
    file.close();

    string cmd = "vim " + path;
    system(cmd.c_str());

    createNote(noteName);

    return 0;
}