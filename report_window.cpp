#include "mainwindow.h"
#include "report_window.h"
#include "./ui_report_window.h"

using namespace std;

extern vector<QString> item_list;
extern int count_change;

void ReportWindow::updateDisplay() {

    if (count_change >= 0 && count_change < item_list.size()) {
        ui->txtb_item2->setText(item_list[count_change]);
    }

}

ReportWindow::ReportWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReportWindow)
{
    ui->setupUi(this);

    ui->header_txt_browser2->setText("AZReports - Ações");
    ui->header_txt_browser2->setAlignment(Qt::AlignCenter); //alinha o texto selecionado

    qDebug() << "pre::actual_item_list::count_change: " << count_change;


    QString actual_item_list = item_list[count_change];

    updateDisplay();

    qDebug() << actual_item_list;

}

ReportWindow::~ReportWindow()
{
    delete ui;
}
