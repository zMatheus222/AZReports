#include <string>
#include <regex>

#include "txt_vetorize.h"

using namespace std;

//função que ira retornar o tipo do item
inline string detect_item_type(string item){

    string item_type;

    vector<string> wiki_units = txt_vetorize("D:\\USE\\Projects\\C++\\AZTests\\txt_files\\wiki_units.txt");
    vector<string> wiki_vmwares = txt_vetorize("D:\\USE\\Projects\\C++\\AZTests\\txt_files\\wiki_vmwares.txt");
    vector<string> wiki_az_vmwares = txt_vetorize("D:\\USE\\Projects\\C++\\AZTests\\txt_files\\wiki_az_vmwares.txt");

    qDebug() << "detect_item_type::string item: " << item << "\n";

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

        qDebug() << "for::line::wiki_vmwares " << line << "\nitem: " << item << "\n";

        regex rgx_vmware("([0-9]+)\\t([A-Za-z]+[0-9]+[A-Za-z]+)\\t([0-9_A-Za-z]+)\\t([A-Za-z]+)\\t([0-9]+.[0-9]+.[0-9]+.[0-9]+)");
        smatch smatch_vmware;
        regex_search(line, smatch_vmware, rgx_vmware);

        string sma_1 = smatch_vmware[1];
        string sma_2 = smatch_vmware[2];
        string sma_3 = smatch_vmware[3];
        string sma_4 = smatch_vmware[4];
        string sma_5 = smatch_vmware[5];
        qDebug() << "smatch_vmware[1]: " << sma_1 << "\nsmatch_vmware[2]: " << sma_2 << "\nsmatch_vmware[3]: " << sma_3 << "\nsmatch_vmware[4]: " << sma_4 << "\nsmatch_vmware[5]: " << sma_5 << "\n";

        //se o item for igual ao nome ou ip da unidade
        if((item == smatch_vmware[2])||(item == smatch_vmware[3])||(item == smatch_vmware[5])){
            return "vmware";
        }
    }

    return "Error::type";
}
