#include "mainwindow.h"
#include <QApplication>
#include <vector>
#include <string>

//#include "txt_vetorize.h"

using namespace std;

int main(int argc, char *argv[]){

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}
