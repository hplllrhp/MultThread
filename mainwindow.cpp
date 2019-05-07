#include "mainwindow.h"
#include "ui_mainwindow.h"
//QThread只有run函数是在新线程里的，其他所有函数都在QThread生成的线程里
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //控件初始化
    ui->horizontalSliderHeartBeat->setRange(0,100);
    ui->horizontalSliderHeartBeat->setValue(0);
    ui->horizontalSliderProgress->setRange(0,100);
    ui->horizontalSliderProgress->setValue(0);
    m_heart = new QTimer(this);
    m_heart->setInterval(100);
    m_thread = new ThreadFromQthread(this);
//子类初始化
    m_cunrrentRunLocalThread = nullptr;
    //按钮信号槽关联
    connect(m_heart,&QTimer::timeout,this,&MainWindow::heartTimeOut);
    connect(m_thread,&ThreadFromQthread::message
            ,this,&MainWindow::receiveMessage);
    connect(m_thread,&ThreadFromQthread::progress
            ,this,&MainWindow::progress);
    connect(m_thread,&QThread::finished
            ,this,&MainWindow::onQThreadFinished);

    m_heart->start();

}
MainWindow::~MainWindow()
{
    qDebug() << "start destroy widget";
    m_thread->stopImmediately();//由于此线程的父对象是Widget，因此退出时需要进行判断
    m_thread->wait();//这一句是主线程等待子线程结束才能继续往下执行样能确保过程是单一往下进行的，也就是不会说子线程还没结束完，主线程就destrioy掉了
    delete ui;
    qDebug() << "end destroy widget";
}
void MainWindow::heartTimeOut()
{
    static int s_heartCount=0;
    ++s_heartCount;
    if(s_heartCount > 100)
    {
        s_heartCount = 0;
    }
    ui->horizontalSliderHeartBeat->setValue(s_heartCount);
}

void MainWindow::receiveMessage(const QString &str)
{
    ui->textBrowser->append(str);
}

void MainWindow::progress(int val)
{
    ui->horizontalSliderProgress->setValue(val);
}

void MainWindow::onQThreadFinished()
{
    ui->textBrowser->append("ThreadFromQThread finish");
}

void MainWindow::on_pushButton_clicked()
{
//    int nCount = ui->stackedWidget->count();
//    int nIndex = ui->stackedWidget->currentIndex();

//    // 获取下一个需要显示的页面索引
//    ++nIndex;

//    // 当需要显示的页面索引大于等于总页面时，切换至首页
//    if (nIndex >= nCount)
//        nIndex = 0;

    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_3_clicked()//onButtonQThreadClicked
{
    ui->horizontalSliderProgress->setValue(0);
    if(m_thread->isRunning())
    {
        return;
    }
    m_thread->start();
}

void MainWindow::on_pushButton_4_clicked()
{
    m_thread->getsomething();
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->textBrowser->append("m_thread->quit() but not work");

    m_thread->stopImmediately();
    m_thread->quit();
}

void MainWindow::on_pushButton_7_clicked()//onButtonQthread1SetSomethingClicked
{
    m_thread->setsomething();
}

void MainWindow::on_pushButton_6_clicked()//
{
    m_thread->terminate();
}

void MainWindow::on_pushButton_8_clicked()
{
    m_thread->dosomething();
}

void MainWindow::on_runLocalThread_clicked()
{
//    局部线程的创建
    if(m_cunrrentRunLocalThread)
    {
        m_cunrrentRunLocalThread->stopImmediately();
    }
    ThreadFromQthread * thread  = new ThreadFromQthread(nullptr);
    connect(thread,&ThreadFromQthread::message
            ,this,&MainWindow::receiveMessage);
    connect(thread,&ThreadFromQthread::progress
            ,this,&MainWindow::progress);
    connect(thread,&QThread::finished
            ,this,&MainWindow::onQThreadFinished);
    connect(thread,&QThread::finished
            ,thread,&QObject::deleteLater);//线程结束后调用deleteLater来销毁分配的内存
   connect(thread,&QThread::destroyed,this,&MainWindow::onLocalThreadDestroy);
    m_cunrrentRunLocalThread = thread;
    thread->start();
}
void MainWindow::onLocalThreadDestroy(QObject *obj)
{
    if(m_cunrrentRunLocalThread == obj)
    {
        m_cunrrentRunLocalThread = nullptr;
    }
}
