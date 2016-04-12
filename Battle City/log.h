#ifndef LOG_H
#define LOG_H

#include <QFile>
#include <QDateTime>
#include <QDebug>
#include <QTextStream>

class Log
{
public:
    static void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);
    Log();
    ~Log();
};

#endif // LOG_H
