#include <QString>
#include <string>

#include "collect_unit_data.cpp"
#include "collect_vmware_data.h"
#include "collect_servidores_data.cpp"
#include "detect_item_type.cpp"

//vector que irá armazenar os itens separados por ,
inline vector<QString> item_queue(vector<QString> item_list, vector<QString> wiki_units,vector<QString> wiki_vmwares,vector<QString> wiki_servidores){

    //declaração dos vectors.
    vector<QString> unit_data;
    vector<QString> vmware_data;
    vector<QString> servidores_data;
    vector<QString> coleted_item_list;

    //para cada item de item_list fazer uma analise.
    for(const QString& actual_item : item_list){

        qDebug() << "\n\nactual_item: " << actual_item << "\n\n";

        //converter para string normal
        string conv_actual_item = actual_item.toStdString();

        //chamar funcao para detectar o tipo do item
        QString item_type = detect_item_type(actual_item, wiki_units, wiki_vmwares, wiki_servidores);

        //variavel que ira ser exibida no programa.
        QString to_user_display_text;

        //detectar o tipo do item, então escolher a função referente a ela.
        if(item_type == "unidade"){

            //chamar funcao que retornara as informacoes do item digitado
            unit_data = collect_unit_data(actual_item, wiki_units, wiki_vmwares);

            //strings unicas para cada um dos itens
            //QString sep_unit_full = unit_data[0];
            QString sep_unit_hname = unit_data[1];
            QString sep_unit_shortloc = unit_data[2];
            QString sep_unit_ip = unit_data[3];
            QString sep_unit_fullloc = unit_data[4];

            //conta quantos itens tem no vector
            int data_size = unit_data.size();
            qDebug() << "data_size: " << data_size << "\n";

            //variavel que salva as vmwares referentes a uma unidade
            QString unit_vmwares;

            //salvar vmwares coletadas em uma string unica. a partir da linha 5 na vector, que é quando começa as vmwares
            int count = 0;
            for(QString& line : unit_data){

                qDebug() << "mainwindow.cpp::line: " << line << "\n";

                if(count >= 5){
                    unit_vmwares = unit_vmwares + line + "\n";
                }
                count++;
            }

            //exibir os itens da Unidade + lista de vmwares desta unidade.
            to_user_display_text = "<span style='color: orange;'>Informações da Unidade:</span>";
            to_user_display_text += "\nNome: <span style='color: #90EE90; font-weight: bold;'>" + sep_unit_hname + "</span>\n";
            to_user_display_text += "Ip: "+ sep_unit_ip + "\n";
            to_user_display_text += "Localização: (" + sep_unit_shortloc + ") " + sep_unit_fullloc + "\n";
            to_user_display_text += "\n<span style='color: orange;'>VMWares associadas:</span>\n" + unit_vmwares + "\n";

            //substituir os \n da string acima por <br>
            to_user_display_text.replace("\n", "<br>");

            coleted_item_list.push_back(to_user_display_text);

        }
        else if(item_type == "vmware"){

            //chamar funcao que retornara as informacoes do item digitado
            vmware_data = collect_vmware_data(actual_item, wiki_vmwares);

            //strings unicas para cada um dos itens
            //QString sep_vmware_full = vmware_data[0];
            QString sep_vmware_port = vmware_data[1];
            QString sep_vmware_hname = vmware_data[2];
            QString sep_vmware_container_name = vmware_data[3];
            QString sep_vmware_shortloc = vmware_data[4];
            QString sep_vmware_ip = vmware_data[5];
            QString sep_vmware_machine = vmware_data[6];

            //exibir os itens do servidor
            to_user_display_text = "<span style='color: orange;'>Informações da VMWare:</span>";
            to_user_display_text += "\nNome: <span style='color: #41c4f4; font-weight: bold;'>" + sep_vmware_hname + "</span>\n";
            to_user_display_text += "Maquina: " + sep_vmware_machine + "\n";
            to_user_display_text += "container name: " + sep_vmware_container_name +"\n";
            to_user_display_text += "Localização: (" + sep_vmware_shortloc + ")" + "\n";
            to_user_display_text += "ip: " + sep_vmware_ip +"\n";
            to_user_display_text += "port: " + sep_vmware_port + "\n";

            //substituir os \n da string acima por <br>
            to_user_display_text.replace("\n", "<br>");

            coleted_item_list.push_back(to_user_display_text);

        }
        else if(item_type == "servidor"){

            //chamar funcao que retornara as informacoes do item digitado
            servidores_data = collect_servidores_data(actual_item, wiki_servidores);

            //strings unicas para cada um dos itens
            //QString sep_servidor_full = servidores_data[0];
            QString sep_servidor_ip = servidores_data[1];
            QString sep_servidor_hname = servidores_data[2];
            QString sep_servidor_descr = servidores_data[3];

            //exibir os itens do servidor
            to_user_display_text = "<span style='color: orange;'>Informações do Servidor:</span>";
            to_user_display_text += "\nNome: <span style='color: magenta; font-weight: bold;'>" + sep_servidor_hname + "</span>\n";
            to_user_display_text += "Ip: "+ sep_servidor_ip + "\n";
            to_user_display_text += "Descrição: "+ sep_servidor_descr + "\n";

            //substituir os \n da string acima por <br>
            to_user_display_text.replace("\n", "<br>");

            coleted_item_list.push_back(to_user_display_text);

            qDebug() << "finalized 'servidor'";

        }

    }

    qDebug() << "return coleted_item_list";
    return coleted_item_list;

}
