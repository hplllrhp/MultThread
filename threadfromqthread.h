#ifndef THREADFROMQTHREAD_H
#define THREADFROMQTHREAD_H
#include <QThread>
#include <QDebug>
#include <QMutex>

class ThreadFromQthread:public QThread//继承Qthread
{
    Q_OBJECT
public:
    ThreadFromQthread();
signals:
    void message(const QString& info);
    void progress(int present);
public:
    ThreadFromQthread(QObject* par);
    ~ThreadFromQthread();
    void setsomething();//进行500ms延迟
    void getsomething();//进行了500ms的延迟
    void setruncount(int count);
    void run();
    void dosomething();
private:
    int m_runcount;

    QMutex m_lock;
    bool m_isCanRun;

public slots:
    void stopImmediately();
};

#endif // THREADFROMQTHREAD_H
