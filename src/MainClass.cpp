#include <QCoreApplication>
#include <QTimer>
#include <QDir>
#include <QDateTime>
#include "MainClass.h"

MainClass *MainClass::rialSelf;

//Ctrl+C handler
//void SigInt_Handler(int n_signal){
void MainClass::handleSignal(int num){
    qDebug()<<"Welcome to Signal handled: "<<num;
    //Stop thread
    if(consoleThread.get()->isRunning()) consoleThread->requestInterruption();
    else QCoreApplication::quit();
/*
#warning need fix
    QCoreApplication::quit();*/
}


//This is part of MainClass's constructor to init signal-slot
void MainClass::Console_SIGNAL_SETTINGS(){
    //When tmk_thread started then run tmk_worker logic (run() method)
    connect(consoleThread.get(), &QThread::started, consoleWorker.get(), &ConsoleWorker::run);
    //When worker emit signal "finished" then thread quit
    connect(consoleWorker.get(), &ConsoleWorker::finished, consoleThread.get(), &QThread::quit);
    //Main thread analyze what happens with another threads in threadIsFinished()
    connect(consoleThread.get(), &QThread::finished, this, &MainClass::threadIsFinished);

    consoleWorker->moveToThread(consoleThread.get()); //transfer object worker (no parent!) to thread tmk_thread
}


MainClass::MainClass(QObject *parent)
    :QObject(parent)
    ,consoleWorker(new ConsoleWorker()) //родителя нет, ибо "The object cannot be moved if it has a parent."
    ,consoleThread(new QThread(this)) //родитель есть (не обязательно)
{
    MainClass::setSignalHandlerObject(this); //for Ctrl+C
    Console_SIGNAL_SETTINGS();
    consoleThread->start();
}


//Обработчик вызывается когда thread finish
void MainClass::threadIsFinished()
{
    //If you have multimp threads you can analizy which finish
    if(consoleThread.get()->isFinished()){
        qDebug() << "threadIsFinished";
    }
    QCoreApplication::quit();
}

