#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//para poder recarregar estas vectors em mainwindow
private:
    std::vector<QString> wiki_units;
    std::vector<QString> wiki_vmwares;
    std::vector<QString> wiki_servidores;

    //vector que irá armazenar todos os itens digitados pelo usuário.
    std::vector<QString> item_list;

    int count = 0;

private slots:
    void on_BtnAnalisar_clicked();
    void on_BtnNext_clicked();
    void on_BtnPrev_clicked();
    void updateDisplay();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
