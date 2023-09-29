#ifndef COLLECT_VMWARE_DATA_H
#define COLLECT_VMWARE_DATA_H

#include <vector>
#include <string>
#include <QDebug>
#include <regex>

using namespace std;

inline vector<QString> collect_vmware_data(QString item, vector<QString> wiki_vmwares){

    //apenas um vector vazio para retornar nada (se isso for retornado é um problema)
    vector<QString> empty = {"Empty"};

    //declaração de var pois não pode ser declarada dentro do if.
    string vmware_machine;

    qDebug() << "entered collect_vmware_data -> item: " << item << "\n";

    //vmware_do_item contem todo conteúdo que será retornado.
    vector<QString> vmware_do_item;

    /*
    qDebug() << "vmwares wiki:\n";
    for(string line : wiki_vmwares){
        qDebug() << line << "\n";
    }
    */

    //regex que vai ajudar a detectar a maquina que a vmware está
    regex rgx_vm_machine("M(?:[\\]?[A-Za-z]+[0-9]+[\\][A-Za-z]+[0-9]+[A-Za-z]+)?(?:[á-úA-Za-z]+)?\\s+([0-9]+)");
    smatch smatch_vm_machine;

    //regex que detecta linha da vmware e salva itens dentro de ()
    regex rgx_vmware("([0-9]+)\\t([A-Za-z]+[0-9]+[A-Za-z]+)\\t([A-Za-z_0-9]+)\\t([A-Za-z]+)\\t([0-9]+.[0-9]+.[0-9]+.[0-9]+)");
    smatch smatch_vmware;


    //passar de 1 em 1 nos itens da wiki_vmwares
    for(QString& line : wiki_vmwares){

        //converter QString em string pois o regex não lê QString
        string conv_line = line.toStdString();
        string conv_item = item.toStdString();

        qDebug() << "line::vmwares: " << line << "\nitem: " << item << "\n";

        //pegar de qual maquina esta vmware faz parte//rgx_sch_matched_machine recebe true ou false dependendo se deu match ou não
        bool rgx_sch_matched_machine = regex_search(conv_line, smatch_vm_machine, rgx_vm_machine);

        //separar itens de cada vmware na smatch baseado na regex e retornar verdadeiro ou falso se bateu a linha com a regex de vmware
        bool rgx_sch_matched_vmware = regex_search(conv_line, smatch_vmware, rgx_vmware);

        //se estivermos em uma linha onde possui "Máquina 78", ative este if para salvar a maquina, se for outro tipo de linha não salvamos, e o valor da ultima maquina encontrada fica armazenado.
        if(rgx_sch_matched_machine == true){

            //salvar numero da maquina na var vmware_machine
            vmware_machine = smatch_vm_machine[1];

            qDebug() << "vmware_machine:" << vmware_machine << "\n";

        }
        else if(rgx_sch_matched_vmware == true){

            //contar quantos itens foram coletados na smatch
            int smatch_count = 0;
            for(const auto line : smatch_vmware){
                smatch_count++;
            }

            qDebug() << "pre for int i smatch_count: " << smatch_count << " item: " << item << "\n";

            //ir de 1 em 1 nos itens da smatch, e comparar com o item passado. não começamos por 0 afinal na smatch, 0 tem toda correspondencia regex.
            for(int i = 1; i <= smatch_count; i++){

                qDebug() << "for::smatch_count: entered for int i[" << i << "]\n";

                //se o elemento que foi passado no 'item' der match com algum dos itens do smatch.
                if(conv_item == smatch_vmware[i]){

                    string sma_v1 = smatch_vmware[i];
                    qDebug() << "entered if::item::smatch_vmware[i]: " << sma_v1 << "\n";

                    for(const auto line : smatch_vmware){

                        qDebug() << "const::auto::line: " << &line << "\n";

                        //converter line (string) para QString
                        QString conv_line = QString::fromStdString(line);
                        //fazer pushback da line convertida para o vector.
                        vmware_do_item.push_back(conv_line);

                    }

                    //depois de adicionar todos os itens a vector, por fim converter var da maquina que ela pertence para QString e fazer push_back.
                    QString conv_machine = QString::fromStdString(vmware_machine);
                    vmware_do_item.push_back(conv_machine);

                }

                qDebug() << "for::vmware_do_item: ";
                for(QString& line : vmware_do_item){
                    qDebug() << line;
                }

                //só retornar vector se vmware_do_item (o vetor) tiver conteudo. senão continuar no for.
                if(vmware_do_item.size() > 0){
                    return vmware_do_item;
                }

            }
        }
        else{
            //entrar em else se a linha não corresponder a Maquina ou uma linha comum com todas as informações de vmware
            qDebug() << "entered else SXXXXX::line " << line << "\n";
        }

    }

    return empty;
}


#endif // COLLECT_VMWARE_DATA_H
