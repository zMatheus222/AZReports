#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QString>

#include "collect_unit_data.cpp"
#include "collect_vmware_data.cpp"
#include "detect_item_type.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->header_txt_browser->setText("AZReports - Analise");
    //ui->header_txt_browser->selectAll(); //destaca o texto inteiro, tornando-o pronto para ser modificado de alguma forma
    ui->header_txt_browser->setAlignment(Qt::AlignCenter); //alinha o texto selecionado
}

MainWindow::~MainWindow()
{
    delete ui;
}

//quando o botao for pressionado, pega o texto da ui InputItems e salva na var, depois exibe na ui txtb_item com setText.
void MainWindow::on_BtnAnalisar_clicked(){

    //declaração dos vectors.
    vector<QString> unit_data;
    vector<QString> vmware_data;

    //criar uma QString que pega o valor de InputItems como uma QString.
    QString TextoInserido = ui->InputItems->toPlainText();

    //converter TextoInserido para string normal antes de chamar a função abaixo.
    string item = TextoInserido.toStdString();

    //chamar funcao para detectar o tipo do item
    string item_type = detect_item_type(item);

    //variavel que ira ser exibida no programa.
    QString to_user_display_text;

    qDebug() << "item_type: " << item_type << "\n";

    //detectar o tipo do item, então escolher a função referente a ela.
    if(item_type == "unidade"){

        qDebug() << "entered if - item_type: unidade";
        //chamar funcao que retornara as informacoes do item digitado
        unit_data = collect_unit_data(item);

        //strings unicas para cada um dos itens
        QString sep_unit_full = unit_data[0];
        QString sep_unit_hname = unit_data[1];
        QString sep_unit_shortloc = unit_data[2];
        QString sep_unit_ip = unit_data[3];
        QString sep_unit_fullloc = unit_data[4];

        qDebug() << "unit_data:\n";
        qDebug() << "[0]unit_full: " << sep_unit_full << "\n";
        qDebug() << "[1]unit_name:" << sep_unit_hname << "\n";
        qDebug() << "[2]unit_shortloc:" << sep_unit_shortloc << "\n";
        qDebug() << "[3]unit_ip:" << sep_unit_ip << "\n";
        qDebug() << "[4]unit_full_loc:" << sep_unit_fullloc << "\n";

        //conta quantos itens tem no vector
        int data_size = unit_data.size();
        qDebug() << "data_size: " << data_size << "\n";

        //variavel que salva as vmwares referentes a uma unidade
        QString unit_vmwares;

        //salvar vmwares coletadas em uma string unica. a partir da linha 5 na vector, que é quando começa as vmwares
        int count = 0;
        for(QString& line : unit_data){
            if(count >= 5){
                unit_vmwares = unit_vmwares + line + "\n";
            }
            count++;
        }

        qDebug() << "entered data_size == 5";
        //exibir os itens da Unidade + lista de vmwares desta unidade.
        to_user_display_text =
            "Nome: " + sep_unit_hname + "\n" +
            "Ip: " + sep_unit_ip + "\n" +
            "Localização: (" + sep_unit_shortloc + ") " + sep_unit_fullloc + "\n" +
            "\nVMWares associadas:\n" + unit_vmwares + "\n";

        qDebug() << "unit_vmwares:\n" << unit_vmwares << "\n";

    }
    else if(item_type == "vmware"){

        qDebug() << "entered if - item_type: vmware";
        //chamar funcao que retornara as informacoes do item digitado
        vmware_data = collect_vmware_data(item);

        //strings unicas para cada um dos itens
        QString sep_vmware_full = vmware_data[0];
        QString sep_vmware_port = vmware_data[1];
        QString sep_vmware_hname = vmware_data[2];
        QString sep_vmware_container_name = vmware_data[3];
        QString sep_vmware_shortloc = vmware_data[4];
        QString sep_vmware_ip = vmware_data[5];
        QString sep_vmware_machine = vmware_data[6];

        qDebug() << "vmware_data:\n";
        qDebug() << "[0]vmware_full: " << sep_vmware_full << "\n";
        qDebug() << "[1]sep_vmware_port:" << sep_vmware_port << "\n";
        qDebug() << "[2]sep_vmware_hname:" << sep_vmware_hname << "\n";
        qDebug() << "[3]sep_vmware_container_name:" << sep_vmware_container_name << "\n";
        qDebug() << "[4]sep_vmware_shortloc:" << sep_vmware_shortloc << "\n";
        qDebug() << "[5]sep_vmware_ip:" << sep_vmware_ip << "\n";

        to_user_display_text =
            "Nome: " + sep_vmware_hname + "\n" +
            "Maquina: " + sep_vmware_machine + "\n" +
            "container name: " + sep_vmware_container_name +"\n" +
            "Localização: " + "(" + sep_vmware_shortloc + ")" + "\n" + //adicionar localização completa aqui.
            "ip: " + sep_vmware_ip +"\n" +
            "port: " + sep_vmware_port + "\n";

    }


    ui->txtb_item->setText(to_user_display_text);

}

