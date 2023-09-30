#include "mainwindow.h"
#include <QDebug>
#include <QString>
#include <thread>
#include <chrono>

#include "./ui_mainwindow.h"
#include "item_queue.cpp"
#include "txt_vetorize.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //[recarregando vectors feito processo "private" em mainwindow.h] vector que vai coletar as linhas do arquivo .txt + caminho do arquivo .txt
    wiki_units = txt_vetorize("D:\\USE\\Projects\\C++\\AZTests\\txt_files\\wiki_units.txt");
    wiki_vmwares = txt_vetorize("D:\\USE\\Projects\\C++\\AZTests\\txt_files\\wiki_vmwares.txt");
    wiki_servidores = txt_vetorize("D:\\USE\\Projects\\C++\\AZTests\\txt_files\\wiki_serverlist.txt");

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
    QString item = ui->InputItems->toPlainText();
    string input_text = item.toStdString();

    //SRVOBS007DCR,SRVHVM005BLU,vmware_exporter_cch02,SRVPHT001MAU,SRVPHT001SPO
    //dividir itens separados por virgula e adiciolados a um vector.

    string::iterator start = input_text.begin();
    string::iterator end = input_text.begin();
    vector<QString> digited_item_list;

    while (end != input_text.end()) {

        // Encontre a próxima vírgula
        while (end != input_text.end() && *end != ',') {
            ++end;
        }

        // Extraia o item da string e converta-o para QString
        string item(start, end);
        digited_item_list.push_back(QString::fromStdString(item));

        // Avance o iterator 'end' para o próximo caractere, se não for o fim da string
        if (end != input_text.end()) {
            ++end;
        }

        // Avance o iterator 'start' para o próximo caractere
        start = end;
    }

    qDebug() << "\nQString line: digited_item_list";
    for(QString& line : digited_item_list){
        qDebug() << line;
    }

    //exibir vector conforme o botão é apertado, ou seja proximo avança um numero e anterior volta um numero
    item_list = item_queue(digited_item_list, wiki_units, wiki_vmwares, wiki_servidores);

    qDebug() << "\nQString& actual_item : item_list : count: " << count;
    for(QString& actual_item : item_list){
        qDebug() << actual_item << "\n";
    }

    updateDisplay();

}

//atualizar na tela as informações, com base no size e conteudo do vector
void MainWindow::updateDisplay() {

    if (count >= 0 && count < item_list.size()) {
        ui->txtb_item->setText(item_list[count]);
    }

}

//quando o botão proximo for clicado aumentar um valor
void MainWindow::on_BtnNext_clicked() {
    if (count < item_list.size() - 1) {
        ++count;
        updateDisplay();
    }
}

//quando o botão anterior for clicado diminuir um valor
void MainWindow::on_BtnPrev_clicked() {
    if (count > 0) {
        --count;
        updateDisplay();
    }
}

