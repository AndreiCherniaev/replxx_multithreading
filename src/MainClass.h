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
    static MainClass* rialSelf; //https://stackoverflow.com/questions/54467652/how-to-set-sa-handlerint-pointer-to-function-which-is-member-of-a-class-i
    void handleSignal(int num);
    static void setSignalHandlerObject(MainClass* newRealSelf) {
        MainClass::rialSelf= newRealSelf;
    }
    static void callSignalHandler(int num){ //num is number of handler, in case of SIGINT (Ctrl+C) it is 2
        rialSelf->handleSignal(num);
    }

    explicit MainClass(QObject *parent = 0);

public slots:
    void threadIsFinished();
};
