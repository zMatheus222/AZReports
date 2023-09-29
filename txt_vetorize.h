#ifndef TXT_VETORIZE_H
#define TXT_VETORIZE_H

#include <vector>
#include <string>
#include <fstream>
#include <qDebug>

using namespace std;

inline vector<QString> txt_vetorize(QString file_name){

    string conv_file_name = file_name.toStdString();

    qDebug() << "file_name: " << file_name << "\n";

    vector<QString> coleted_itens;

    ifstream txt_file(conv_file_name);

    if(txt_file.is_open()){
        qDebug() << "arquivo: " << file_name << "foi aberto corretamente.\n";
    }
    else{
        qDebug() << "arquivo: " << file_name << "nao foi aberto corretamente.\n";
    }

    string actual_line;
    while(getline(txt_file, actual_line)){

        QString conv_actual_line = QString::fromStdString(actual_line);
        coleted_itens.push_back(conv_actual_line);
    }

    return coleted_itens;
}

#endif
