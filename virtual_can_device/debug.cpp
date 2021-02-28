#include "debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "debug.h"

#include <time.h>


int Debug::debug_level = 0;
Debug::Debug(QObject *parent) : QObject(parent)
{

}

void Debug::log(int level, const char* fmt, ...)
{
    if( level <= Debug::debug_level ){
        time_t nSeconds;
        struct tm * pTM;
        time(&nSeconds);
        pTM = localtime(&nSeconds);
        if ( level == 0 )
            printf("{%02d-%02d %02d:%02d:%02d} [Error." _PROCESS "]", pTM->tm_mon,pTM->tm_mday,pTM->tm_hour, pTM->tm_min, pTM->tm_sec);
        else if ( level == 1 )
            printf("{%02d-%02d %02d:%02d:%02d} [Warning." _PROCESS "]", pTM->tm_mon,pTM->tm_mday,pTM->tm_hour, pTM->tm_min, pTM->tm_sec);
        else
            printf("{%02d-%02d %02d:%02d:%02d} [" _PROCESS "]", pTM->tm_mon,pTM->tm_mday,pTM->tm_hour, pTM->tm_min, pTM->tm_sec);


        va_list ap;
        va_start(ap, fmt);
        vprintf(fmt, ap);
        va_end(ap);
        fflush(stdout); // 清空输出缓冲区，并把缓冲区内容输出。
    }
}

void Debug::set_debug_level(int level)
{
    if ( (level < 0)||(level > 3) ){
        Debug::debug_level = 0;
    } else {
        Debug::debug_level = level;
    }
}
