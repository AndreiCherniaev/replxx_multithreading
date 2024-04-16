#pragma once

#include <QThread>
#include "ConsoleWorker.h"

class MainClass : public QObject
{
    Q_OBJECT
    QScopedPointer<ConsoleWorker> consoleWorker;
    QScopedPointer<QThread> consoleThread;

    void Console_SIGNAL_SETTINGS();

public:
    //Thanks https://github.com/AndreiCherniaev/QCoreApplication_quit_example
    static MainClass* mainClassSelf;
    void handleSignal(int num);
    static void setSignalHandlerObject(MainClass* newRealSelf) {
        MainClass::mainClassSelf= newRealSelf;
    }
    static void callSignalHandler(int num){ //num is number of handler, in case of SIGINT (Ctrl+C) it is 2
        mainClassSelf->handleSignal(num);
    }

    explicit MainClass(QObject *parent = 0);

public slots:
    void threadIsFinished();
};
