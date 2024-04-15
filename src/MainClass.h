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
    explicit MainClass(QObject *parent = 0);

public slots:
    void threadIsFinished();
};
