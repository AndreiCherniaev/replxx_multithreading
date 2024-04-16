#include <QCoreApplication>
#include <signal.h>
#include "main.h"
#include "MainClass.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName(QUOTE(MYPROJECT_NAME));
    QCoreApplication::setApplicationVersion(QUOTE(CMAKE_PROJECT_VERSION));
    MainClass mainClass(QCoreApplication::instance());

#ifdef Q_OS_UNIX
        struct sigaction hup;
        hup.sa_handler = mainClass.callSignalHandler;
        sigemptyset(&hup.sa_mask);
        hup.sa_flags = 0;
        hup.sa_flags |= SA_RESTART;
        if(sigaction(SIGINT, &hup, 0))
            return 1;
#else
    #warning you should use any Linux disto to get Ctrl+C exit functionality
#endif

    int ret= QCoreApplication::exec();
    return ret;

    return a.exec();
}
