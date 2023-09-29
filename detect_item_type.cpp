#include <string>
#include <regex>
#include <qDebug>

using namespace std;

//função que ira retornar o tipo do item
inline string detect_item_type(QString item, vector<QString> wiki_units, vector<QString> wiki_vmwares, vector<QString> wiki_servidores){

    string item_type;

    qDebug() << "detect_item_type::string item: " << item << "\n";

    //loop para cada tipo, o item será passado de for em for até encontrar o seu, que retornara o tipo.
    for(QString& line : wiki_units){

        string conv_line = line.toStdString();
        string conv_item = item.toStdString();

        regex rgx_unit("([A-Za-z]+[0-9]+[A-Za-z]+)\\t([0-9]+.[0-9]+.[0-9]+.[0-9]+)\\t([A-Za-z-Á-Ú-á-ú]+)");
        smatch smatch_unit;
        regex_search(conv_line, smatch_unit, rgx_unit);

        //se o item for igual ao nome ou ip da unidade
        if((conv_item == smatch_unit[1])||(conv_item == smatch_unit[2])){
            qDebug() << "returned item_type: unidade\n";
            return "unidade";
        }
    }

    for(QString& line : wiki_vmwares){

        string conv_line = line.toStdString();
        string conv_item = item.toStdString();

        qDebug() << "for::line::wiki_vmwares " << line << "\nitem: " << item << "\n";

        regex rgx_vmware("([0-9]+)\\t([A-Za-z]+[0-9]+[A-Za-z]+)\\t([0-9_A-Za-z]+)\\t([A-Za-z]+)\\t([0-9]+.[0-9]+.[0-9]+.[0-9]+)");
        smatch smatch_vmware;
        regex_search(conv_line, smatch_vmware, rgx_vmware);

        string sma_1 = smatch_vmware[1];
        string sma_2 = smatch_vmware[2];
        string sma_3 = smatch_vmware[3];
        string sma_4 = smatch_vmware[4];
        string sma_5 = smatch_vmware[5];
        qDebug() << "smatch_vmware[1]: " << sma_1 << "\nsmatch_vmware[2]: " << sma_2 << "\nsmatch_vmware[3]: " << sma_3 << "\nsmatch_vmware[4]: " << sma_4 << "\nsmatch_vmware[5]: " << sma_5 << "\n";

        //se o item for igual ao nome ou ip da unidade
        if((conv_item == smatch_vmware[2])||(conv_item == smatch_vmware[3])||(conv_item == smatch_vmware[5])){
            qDebug() << "returned item_type: vmware\n";
            return "vmware";
        }
    }
    for(QString& line : wiki_servidores){

        qDebug() << "entered line : wiki_servidores";

        string conv_line = line.toStdString();
        string conv_item = item.toStdString();

        regex rgx_unit("^([0-9]+.[0-9]+.[0-9]+.[0-9]+.)\t?([A-Za-z]+[0-9]+[A-Za-z]+)\t(.*)");
        smatch smatch_unit;
        regex_search(conv_line, smatch_unit, rgx_unit);

        //se o item for igual ao nome ou ip da unidade
        if((conv_item == smatch_unit[1])||(conv_item == smatch_unit[2])){
            qDebug() << "returned item_type: servidor\n";
            return "servidor";
        }
    }

    return "Error::type";
}
