#pragma once

#include <QCoreApplication>
#include <QObject>
#include <QThread>
#include <QDebug>
#include <QCommandLineParser>
#include "replxx.hxx"

using Replxx = replxx::Replxx;

class ConsoleWorker : public QObject
{
    Q_OBJECT
public:
    Replxx rx;
    explicit ConsoleWorker(QObject *parent = nullptr);

public slots:
    void run(); //метод с пользовательскими алгоритмами, которые могут быть оформлены в этом методе внутри while(1)

signals:
    void finished(); //сигнал, по которому будем завершать нить, после завершения метода run()
};

