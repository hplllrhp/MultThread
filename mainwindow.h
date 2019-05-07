#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QVBoxLayout>
#include "threadfromqthread.h"
#include <QTimer>
#include <QDebug>
#include "threadobject.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void heartTimeOut();

    void receiveMessage(const QString &str);

    void progress(int val);

    void onQThreadFinished();

    void on_runLocalThread_clicked();

    void onLocalThreadDestroy(QObject *obj);

    void onButtonObjectMove2ThreadClicked();
    void onButtonObjectMove2Thread2Clicked();
    void onButtonObjectThreadStopClicked();
    void startObjThread();

private:
    Ui::MainWindow *ui;
    ThreadFromQthread *m_thread;
    QTimer *m_heart;
    ThreadFromQthread *m_cunrrentRunLocalThread;
    QThread m_objThread;
    ThreadObject* m_obj;

signals:
    void startObjThreadWork1();
    void startObjThreadWork2();

};

#endif // MAINWINDOW_H
