#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
extern int stop,count;
extern QString key;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    int on_pushButton_clicked();

    int reader();

    void printHex(uint8_t *buffer, size_t bufferSize);

    void clear();

    //void printHex();

    void on_pushButton_3_clicked();

    //void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
