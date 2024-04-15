#pragma once

#include <QCoreApplication>
#include <QObject>
#include <QThread>
#include <QTimer>
#include <QDebug>
#include <QCommandLineParser>
#include "replxx.hxx"

class ConsoleWorker : public QObject
{
    Q_OBJECT
    replxx::Replxx rx;
public:
    explicit ConsoleWorker(QObject *parent = nullptr);

public slots:
    void run(); //метод с пользовательскими алгоритмами, которые могут быть оформлены в этом методе внутри while(1)

signals:
    void finished(); //сигнал, по которому будем завершать нить, после завершения метода run()
};

