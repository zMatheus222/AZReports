#ifndef TXT_VETORIZE_H
#define TXT_VETORIZE_H

#include <vector>
#include <string>
#include <fstream>
#include <qDebug>
#include <regex>

using namespace std;

inline vector<QString> txt_vetorize(QString file_name){

    string conv_file_name = file_name.toStdString();

    qDebug() << "file_name: " << file_name << "";

    vector<QString> coleted_itens;

    ifstream txt_file(conv_file_name);

    if(txt_file.is_open()){
        qDebug() << "arquivo: " << file_name << "foi aberto corretamente.";
    }
    else{
        qDebug() << "arquivo: " << file_name << "nao foi aberto corretamente.";
    }

    string actual_line;
    while(getline(txt_file, actual_line)){

        //correções de texto -> -> ->

        smatch smatch_line;

        //se o regex search abaixo (comparar linha atual com a regex) for true entrar no if.
        if(regex_search(actual_line, smatch_line, regex("[0-9]+\t[A-Za-z]+[0-9]+[A-Za-z]+\t[A-Za-z_0-9]+\t([A-Za-z]+)\t[0-9]+.[0-9]+.[0-9]+.[0-9]+"))){
            //se a actual_line contiver SSP, corrige para SPO (correção para vmwares de são paulo na wiki)
            string vmware_short_loc = smatch_line[1];

            if(vmware_short_loc == "SSP"){
                //trocar valor da actual_line para "SPO"
                actual_line = regex_replace(actual_line, regex("SSP"), "SPO");
                qDebug() << "corrigido SSP -> SPO : actual_line: " << actual_line;
            }

        }

        // <- <- <- correções de texto

        QString conv_actual_line = QString::fromStdString(actual_line);
        coleted_itens.push_back(conv_actual_line);

    }

    //fechar o arquivo antes de retornar.
    txt_file.close();

    return coleted_itens;
}

#endif
