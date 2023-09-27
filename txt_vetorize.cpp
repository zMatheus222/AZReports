#include <vector>
#include <string>
#include <fstream>
#include <qDebug>

using namespace std;

inline vector<string> txt_vetorize(string file_name){

    qDebug() << "file_name: " << file_name << "\n";

    vector<string> coleted_itens;

    ifstream txt_file(file_name);

    if(txt_file.is_open()){
        qDebug() << "arquivo: " << file_name << "foi aberto corretamente.\n";
    }
    else{
        qDebug() << "arquivo: " << file_name << "nao foi aberto corretamente.\n";
    }

    string actual_line;
    while(getline(txt_file, actual_line)){
        coleted_itens.push_back(actual_line);
    }

    return coleted_itens;
}
