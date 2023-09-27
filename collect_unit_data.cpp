#include <vector>
#include <string>
#include <QDebug>
#include <regex>

#include "txt_vetorize.h"

using namespace std;

//coletar todas as vmwares fazer comparação com a localização delas e a localização da unidade 'item' salvar todas da mesma localização no vector.
inline vector<QString> pick_unit_vmwares(QString short_loc){

    //vector que vai conter as vmwares da localização passada.
    vector<QString> unit_vmwares;

    //obter todas as vmwares e armazenar na wiki e passar ao vector.
    vector<string> wiki_vmwares = txt_vetorize("D:\\USE\\Projects\\C++\\AZTests\txt_files\\wiki_vmwares.txt");

    //fazer comparação de localizações e salvar as que forem iguais:
    for(string line : wiki_vmwares){

        //para cada line (que é uma vmware) separar os conteudos no smatch, depois comparar a localização curta
        smatch smatch_vmware;
        regex_search(line, smatch_vmware, regex("[0-9]+\\s([A-Za-z-0-9]+)\\s\\w+\\s([A-Z]+)\\s+[0-9]+.[0-9]+.[0-9]+.[0-9]+"));

        //se a var de localização da vmware bater com a que foi passada, da unidade, push_back no nome da vmware.
        QString var_smatch = QString::fromStdString(smatch_vmware[2]);

        qDebug() << "\nline: " << line << "short_loc::" << short_loc << " | var_smatch[2]:: " << var_smatch << "\n";

        if(short_loc == var_smatch){

            qDebug() << "entered if::short_loc::varsmatch\nshort_loc: " << short_loc << "\nvar_smatch: " << var_smatch << "\n";

            //criar QString convertida de uma string normal
            QString vmware_name = QString::fromStdString(smatch_vmware[1]);
            unit_vmwares.push_back(vmware_name);
            qDebug() << "vmware_name: " << vmware_name << "\n";

        }
    }

    qDebug() << "Unit VMWares:\n";
    for(QString& line : unit_vmwares){
        qDebug() << line;
    }

    return unit_vmwares;
}

inline vector<QString> collect_unit_data(string item){

    qDebug() << "entered collect_unit_data -> item: " << item << "\n";

    //empty é apenas uma vector sem nada. que será retornada caso de um problema.
    vector<QString> empty = {"Empty"};

    //unidade_do_item conterá todo o conteúdo que será retornado.
    vector<QString> unidade_do_item;

    //vector que vai coletar as linhas do arquivo + caminho do arquivo .txt
    vector<string> unidades = txt_vetorize("D:\\USE\\Projects\\C++\\AZTests\\txt_files\\wiki_units.txt");

    qDebug() << "unidades wiki:\n";
    for(string line : unidades){
        qDebug() << line << "\n";
    }

    //regex que detecta linha da unidade e salva itens dentro de ()
    regex rgx_unidade("([A-Za-z]+[0-9]+([A-Za-z]+))(?:[\\t]+)?(?:\\s)?([0-9]+.[0-9]+.[0-9]+.[0-9]+)(?:[\\t]+)?(?:\\s)?(.*)");
    smatch smatch_unidade;

    qDebug() << "entered if regex search item, rgx_unidade\n";

    //checar cada linha do vector unidades da wiki para comparar e extrair as informacoes.
    for(string& line : unidades){

        //dividir line na smatch com base na regex
        regex_search(line, smatch_unidade, rgx_unidade);

        //contar quantos itens foram coletados na smatch
        int smatch_count = 0;
        for(const auto line : smatch_unidade){
            smatch_count++;
        }

        qDebug() << "smatch_count: " << smatch_count << "\n";

        //ir de 1 em 1 nos itens da smatch, e comparar com o item passado. não começamos por 0 afinal na smatch, 0 tem toda correspondencia regex.
        for(int i = 1; i <= smatch_count ; i++){

            //gerar string 'sma' baseada na smatch_unidade[i] < i = int i do for.
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

                //converter string item em QString item
                QString conv_item = QString::fromStdString(item);

                //localização short da unidade em [2]
                QString conv_shortloc = QString::fromStdString(smatch_unidade[2]);

                vector<QString> unit_vmwares = pick_unit_vmwares(conv_shortloc);

                //inserir itens no vector menos o 0, pois é a correspondencia completa, nao precisamos.
                int count = 0;
                for(QString& line : unit_vmwares){

                    unidade_do_item.push_back(line);
                    count++;

                }

                //depois de salvar, retornar o vector, unidade do item que eu passei nesta funçao.
                return unidade_do_item;
            }
        }
    }

    return empty;
}
