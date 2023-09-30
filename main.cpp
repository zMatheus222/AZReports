#include "mainwindow.h"
#include <QApplication>
#include <vector>
#include <string>

#include <QGuiApplication>
#include <QPixmap>

//#include "txt_vetorize.h"

using namespace std;

int main(int argc, char *argv[]){

    QApplication a(argc, argv);

    //inserir icone
    QIcon icon(QPixmap(CURRENT_SOURCE_DIR "/icon/azr-icon.ico"));
    QApplication::setWindowIcon(icon);

    //definir icone para 'a'
    a.setWindowIcon(icon);

    MainWindow w;
    w.show();
    return a.exec();

}
