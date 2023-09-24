#ifndef AZREPORTS_F_H
#define AZREPORTS_F_H

#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include <QDebug>
#include <iostream>
using namespace std;

vector<string> txt_vetorize(string file_name){

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

    if(file_name == "wiki_units.txt"){
        coleted_itens.push_back("SRVPTH001APG 10.156.84.94 APARECIDA DE GOIANIA");
        coleted_itens.push_back("SRVPTH001BLU 10.156.18.21 BLUMENAU");
        coleted_itens.push_back("SRVPTH001CDR 10.156.58.81 CAÇADOR");
    }
    else if(file_name == "wiki_vmwares.txt"){
        coleted_itens.push_back("Máquina 78");
        coleted_itens.push_back("Port Name Container Name Unid IP");
        coleted_itens.push_back("9200 srvhvm04apg vmware_exporter_apg01	APG	10.156.84.52");
        coleted_itens.push_back("9201 SRVHVM05APG vmware_exporter_apg02	APG	10.156.84.57");
        coleted_itens.push_back("9202 srvhvm03apg vmware_exporter_apg03	APG	10.156.84.51");
    }

    return coleted_itens;
}

//coletar todas as vmwares fazer comparação com a localização delas e a localização da unidade 'item' salvar todas da mesma localização no vector.
vector<QString> pick_unit_vmwares(QString short_loc){

    //vector que vai conter as vmwares da unidade.
    vector<QString> unit_vmwares;

    //obter todas as vmwares e armazenar na wiki e passar ao vector.
    vector<string> wiki_vmwares = txt_vetorize("wiki_vmwares.txt");

    //fazer comparação de localizações e salvar as que forem iguais:
    for(string line : wiki_vmwares){

        //para cada line (que é uma vmware) separar os conteudos no smatch, depois comparar a localização curta
        smatch smatch_vmware;
        regex_search(line, smatch_vmware, regex("[0-9]+\\s([A-Za-z-0-9]+)\\s\\w+\\s([A-Z]+)\\s+[0-9]+.[0-9]+.[0-9]+.[0-9]+"));


        //se a var de localização da vmware bater com a que fi passada, da unidade, push_back no nome da vmware.
        QString var_smatch = QString::fromStdString(smatch_vmware[2]);
        if(short_loc == var_smatch){

            //criar QString convertida de uma string normal
            QString vmware_name = QString::fromStdString(smatch_vmware[1]);
            unit_vmwares.push_back(vmware_name);

        }
    }

    return unit_vmwares;

}

//função que ira retornar o tipo do item
string detect_item_type(string item){

    string item_type;

    vector<string> wiki_units = txt_vetorize("wiki_units.txt");
    vector<string> wiki_vmwares = txt_vetorize("wiki_vmwares.txt");
    vector<string> wiki_az_vmwares = txt_vetorize("wiki_az_vmwares.txt");

    //loop para cada tipo, o item será passado de for em for até encontrar o seu, que retornara o tipo.
    for(string& line : wiki_units){

        regex rgx_unit("([A-Za-z]+[0-9]+([A-Za-z]+))(?:[\\t]+[0-9]+)?(?:\\s)?([0-9]+.[0-9]+.[0-9]+.[0-9]+)(?:[\\t]+)?(?:\\s)?(.*)");
        smatch smatch_unit;
        regex_search(line, smatch_unit, rgx_unit);

        //se o item for igual ao nome ou ip da unidade
        if((item == smatch_unit[1])||(item == smatch_unit[3])){
            return "unidade";
        }
    }

    for(string& line : wiki_vmwares){

        regex rgx_vmware("");
        smatch smatch_vmware;
        regex_search(line, smatch_vmware, rgx_vmware);

        //se o item for igual ao nome ou ip da unidade
        if((item == smatch_vmware[1])||(item == smatch_vmware[3])){
            return "vmware";
        }
    }

    return "Error::type";
}

vector<QString> collect_unit_data(string item){

    //empty é apenas uma vector sem nada. que será retornada caso de um problema.
    vector<QString> empty = {"Empty"};
    vector<QString> unidade_do_item;
    vector<string> unidades = txt_vetorize("wiki_units.txt");

    qDebug() << "unidades wiki:\n";
    for(string line : unidades){
        qDebug() << line << "\n";
    }

    regex rgx_unidade("([A-Za-z]+[0-9]+([A-Za-z]+))(?:[\\t]+[0-9]+)?(?:\\s)?([0-9]+.[0-9]+.[0-9]+.[0-9]+)(?:[\\t]+)?(?:\\s)?(.*)");
    smatch smatch_unidade;

    qDebug() << "entered if regex search item, rgx_unidade\n";

    //checar cada linha do vector unidades da wiki para comparar e exatrair as informacoes.
    for(string line : unidades){

        //dividir line na smatch com base na regex
        regex_search(line, smatch_unidade, rgx_unidade);

        //contar quantos itens foram coletados na smatch
        int smatch_count = 0;
        for(const auto line : smatch_unidade){
            smatch_count++;
        }

        qDebug() << "smatch_count: " << smatch_count << "\n";

        //ir de 1 em 1 nos itens da smatch, e comparar com o item passado.
        for(int i = 1; i <= smatch_count ; i++){

            string sma = smatch_unidade[i];
            qDebug() << "item: " << item << "| smatch_unidade[" << i << "]: " << sma << "\n";

            //se o elemento que foi passado no 'item' der match com um dos itens do smatch.
            if(item == smatch_unidade[i]){

                qDebug() << "Foi encontrado o item desejado. adicionando elementos ao vetor unidade_do_item.\n";

                //salvar todos os elementos do smatch no vector.
                for(const auto line : smatch_unidade){

                    QString conv_line = QString::fromStdString(line);
                    unidade_do_item.push_back(conv_line);
                }

                qDebug() << "return unidade do item: " << unidade_do_item << "\n";

                //coletar vmwares relacionadas a unidade
                QString conv_item = QString::fromStdString(item);
                QString conv_smatch = QString::fromStdString(smatch_unidade[2]);
                vector<QString> unit_vmwares = pick_unit_vmwares(conv_smatch);

                //inserir itens no vector menos o 0, pois é a correspondencia completa, nao precisamos.
                int count = 0;
                for(QString& line : unit_vmwares){

                    if(count > 0){
                        unidade_do_item.push_back(line);
                    }

                    count++;
                }

                //depois de salvar, retornar o vector, unidade do item que eu passei nesta funçao.
                return unidade_do_item;
            }
        }
    }

    return empty;
}

#endif // AZREPORTS_F_H


