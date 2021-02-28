#ifndef DEBUG_H
#define DEBUG_H

#include <QObject>

#define _PROCESS "Virtual CAN"

#define _DEBUG_DETAIL 	(3)
#define _DEBUG_INFO 	(2)
#define _DEBUG_WARRING 	(1)
#define _DEBUG_ERROR 	(0)

#define NONE         "\033[0m\n"
#define RED          "\033[0;32;31m"
#define LIGHT_RED    "\033[1;31m"
#define GREEN        "\033[0;32;32m"
#define LIGHT_GREEN  "\033[1;32m"
#define BLUE         "\033[0;32;34m"
#define LIGHT_BLUE   "\033[1;34m"
#define DARY_GRAY    "\033[1;30m"
#define CYAN         "\033[0;36m"
#define LIGHT_CYAN   "\033[1;36m"
#define PURPLE       "\033[0;35m"
#define LIGHT_PURPLE "\033[1;35m"
#define BROWN        "\033[0;33m"
#define YELLOW       "\033[1;33m"
#define LIGHT_GRAY   "\033[0;37m"
#define WHITE        "\033[1;37m"

class Debug : public QObject
{
    Q_OBJECT
public:
    explicit Debug(QObject *parent = 0);

    static int debug_level;
    static void log(int level, const char* fmt, ...);
    static void set_debug_level(int level);

signals:

public slots:
};

#endif // DEBUG_H
