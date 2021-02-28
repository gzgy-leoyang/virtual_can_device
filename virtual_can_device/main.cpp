#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>

#include "can_net.h"
#include "debug.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCoreApplication::setApplicationName("Virtual CAN Device");

    QCommandLineParser parser;
    parser.setApplicationDescription("Virtual CAN Device");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsCompactedShortOptions);

    QCommandLineOption dev_name_option(QStringList() << "n" << "name",
                                        "device name",
                                        "vcu",
                                        "vcu");
    parser.addOption(dev_name_option);


    QCommandLineOption debug_option(QStringList() << "d" << "debug",
                                    "Debug.log level (default is 0)",
                                    "Level"
                                    "0");
    parser.addOption(debug_option);



    parser.process(a);

    int dd = parser.value(debug_option).toInt();
    Debug::set_debug_level( dd );
    QString dev_name = parser.value(dev_name_option);
    Debug::log( _DEBUG_ERROR,"Virtual CAN : %s" NONE, dev_name.toLatin1().data());

    Can_net* net = new Can_net( dev_name );

    return a.exec();
}
