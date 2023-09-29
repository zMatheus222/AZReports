#include <vector>
#include <string>
#include <QDebug>
#include <regex>

using namespace std;


inline vector<QString> collect_servidores_data(QString item, vector<QString> wiki_servidores){

    qDebug() << "entered collect_servidor_data -> item: " << item << "\n";

    //empty é apenas uma vector sem nada. que será retornada caso de um problema.
    vector<QString> empty = {"Empty"};

    //unidade_do_item conterá todo o conteúdo que será retornado.
    vector<QString> servidor_do_item;

    /*
    qDebug() << "unidades wiki:\n";
    for(string line : wiki_units){
        qDebug() << line << "\n";
    }
    */

    //regex que detecta linha da unidade e salva itens dentro de ()
    regex rgx_servidor("^([0-9]+.[0-9]+.[0-9]+.[0-9]+.)\t?([A-Za-z]+[0-9]+[A-Za-z]+)\t(.*)");
    smatch smatch_servidor;

    qDebug() << "entered pre-string& line : wiki_servidores\n";

    //checar cada linha do vector unidades da wiki para comparar e extrair as informacoes.
    for(QString& line : wiki_servidores){

        string conv_line = line.toStdString();
        string conv_item = item.toStdString();

        //dividir line na smatch com base na regex
        regex_search(conv_line, smatch_servidor, rgx_servidor);

        //contar quantos itens foram coletados na smatch
        int smatch_count = 0;
        for(const auto conv_line : smatch_servidor){
            smatch_count++;
        }

        qDebug() << "smatch_count: " << smatch_count << "\n";

        //ir de 1 em 1 nos itens da smatch, e comparar com o item passado. não começamos por 0 afinal na smatch, 0 tem toda correspondencia regex.
        for(int i = 1; i <= smatch_count ; i++){

            //gerar string 'sma' baseada na smatch_unidade[i] < i = int i do for.
            string sma = smatch_servidor[i];
            qDebug() << "item: " << conv_item << "| smatch_servidor[" << i << "]: " << sma << "\n";

            //se o elemento que foi passado no 'item' der match com um dos itens do smatch.
            if(conv_item == smatch_servidor[i]){

                qDebug() << "Foi encontrado o item desejado. adicionando elementos ao vetor servidor_do_item.\n";

                //salvar todos os elementos do smatch no vector.
                for(const auto line : smatch_servidor){

                    QString conv_line = QString::fromStdString(line);
                    servidor_do_item.push_back(conv_line);

                    qDebug() << "for::const::auto::conv_line: " << conv_line << "\n";

                }

                qDebug() << "return servidor do item: " << servidor_do_item << "\n";

                //coletar vmwares da maquina aqui


                //depois de salvar, retornar o vector, unidade do item que eu passei nesta funçao.
                return servidor_do_item;
            }
        }
    }

    return empty;
}
