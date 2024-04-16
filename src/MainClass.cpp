#include <QCoreApplication>
#include <QTimer>
#include <QDir>
#include <QDateTime>
#include "MainClass.h"
#include "replxx.hxx"

MainClass *MainClass::mainClassSelf;

//Ctrl+C handler
void MainClass::handleSignal(int num){
    qDebug() << "Welcome to Signal handled: " << num;
    //Stop thread
    if(consoleThread.get()->isRunning()){
        //I am not sure that it is best practice to call object consoleWorker->rx from anther thread but in most cases it should works...
        //Best practice will be use signal-slot system for it, but replxx doesn't use Qt inside...
        consoleWorker->rx.emulate_key_press(Replxx::KEY::control( 'C' )); //thanks https://github.com/AmokHuginnsson/replxx/issues/132#issuecomment-972951849
    }else QCoreApplication::quit();
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

    // //I am not sure that it is best practice to call object consoleWorker->rx from anther thread but in most cases it should works...
    // //Best practice will be use signal-slot system for it, but replxx doesn't use Qt inside...
    // QTimer::singleShot(5000, [this]{
    //     consoleWorker->rx.emulate_key_press(Replxx::KEY::control( 'C' )); //thanks https://github.com/AmokHuginnsson/replxx/issues/132#issuecomment-972951849
    // });
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

