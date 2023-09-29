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

private slots:
    void on_BtnAnalisar_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
