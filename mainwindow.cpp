#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./azreports_f.h"
#include <QDebug>
#include <QString>

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

    //criar uma QString que pega o valor de InputItems como uma QString.
    QString TextoInserido = ui->InputItems->toPlainText();

    //converter TextoInserido para string normal antes de chamar a função abaixo.
    string item = TextoInserido.toStdString();

    //chamar funcao para detectar o tipo do item
    string item_type = detect_item_type(item);

    //chamar funcao que retornara as informacoes do item digitado
    vector<QString> unit_data = collect_unit_data(item);

    //strings unicas para cada um dos itens
    QString sep_unit_full = unit_data[0];
    QString sep_unit_hname = unit_data[1];
    QString sep_unit_shortloc = unit_data[2];
    QString sep_unit_ip = unit_data[3];
    QString sep_unit_fullloc = unit_data[4];

    qDebug() << "unit_data:\n";
    for(QString line : unit_data){
        qDebug() << line << "\n";
    }

    //variavel que ira ser exibida no programa.
    QString to_user_display_text;

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


    ui->txtb_item->setText(to_user_display_text);

}

