#ifndef REPORT_WINDOW_H
#define REPORT_WINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class ReportWindow;
}
QT_END_NAMESPACE

class ReportWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ReportWindow(QWidget *parent = nullptr);
    ~ReportWindow();

private slots:
    void updateDisplay();

private:
    Ui::ReportWindow *ui; // Esta é a classe gerada pelo Qt para o arquivo .ui
};

#endif // REPORT_WINDOW_H
