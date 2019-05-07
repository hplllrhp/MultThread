#include "threadfromqthread.h"

ThreadFromQthread::ThreadFromQthread(QObject *par):QThread (par)
  ,m_runcount(20)
{

}
ThreadFromQthread::~ThreadFromQthread()
{
    qDebug()<<"ThreadFromQThread::~ThreadFromQThread()";
}
void ThreadFromQthread::setsomething()
{
    msleep(500);
    emit message(QString("%1->%2,thread id:%3").arg(__FILE__).arg(__FUNCTION__).arg((int)QThread::currentThreadId()));
}
void ThreadFromQthread::getsomething()
{
    msleep(500);
    emit message(QString("%1->%2,thread id:%3").arg(__FILE__).arg(__FUNCTION__).arg((int)QThread::currentThreadId()));
}
void ThreadFromQthread::setruncount(int count)
{
    m_runcount = count;
    emit message(QString("%1->%2,thread id:%3").arg(__FILE__).arg(__FUNCTION__).arg((int)QThread::currentThreadId()));
}
void ThreadFromQthread::run()
{
    int count = 0;
    m_isCanRun = true;//标记可以运行
    QString str = QString("%1->%2,thread id:%3").arg(__FILE__).arg(__FUNCTION__).arg((int)QThread::currentThreadId());
    emit message(str);
    while (1)
    {
        sleep(1);
        ++count;
        emit progress(((float)count/m_runcount)*100);
        emit message(QString("ThreadFromQThread::run times:%1").arg(count));
        dosomething();
        if(m_runcount == count)
        {
//            break;
            count = 0;
        }
        QMutexLocker locker(&m_lock);
        if(!m_isCanRun)//在每次循环判断是否可以运行，如果不行就退出循环
        {
            return;
        }
        m_isCanRun = ~m_isCanRun;
    }
}
void ThreadFromQthread::dosomething()
{
    msleep(500);
    emit message(QString("%1->%2,thread id:%3").arg(__FILE__).arg(__FUNCTION__).arg((int)QThread::currentThreadId()));
}

void ThreadFromQthread::stopImmediately()
{
    QMutexLocker locker(&m_lock);
    m_isCanRun = false;
}
