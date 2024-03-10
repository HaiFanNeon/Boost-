#pragma once

#include <iostream>
#include <time.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>

#define SIZE 1024

#define Info 0
#define Debug 1
#define Warning 2
#define Error 3
#define Fatal 4

#define Screen 1
#define Onefile 2
#define Classfile 3

#define LogFile "boost_log.txt"

namespace HaiFan_Log
{
    class Log
    {
    public:
        Log()
        {
            printMethod = Onefile;
            path = "./";
        }
        std::string levelToString(int level)
        {
            switch (level)
            {
            case Info:
                return "Info";
            case Debug:
                return "Debug";
            case Warning:
                return "Warning";
            case Error:
                return "Error";
            case Fatal:
                return "Fatal";
            default:
                return "None";
            }
        }

        // void logmessage(int level, const char *format, ...)
        // {
        //     time_t t = time(nullptr);
        //     struct tm *ctime = localtime(&t);
        //     char leftbuffer[SIZE];
        //     snprintf(leftbuffer, sizeof(leftbuffer), "[%s][%d-%d-%d %d:%d:%d]", levelToString(level).c_str(),
        //              ctime->tm_year + 1900, ctime->tm_mon + 1, ctime->tm_mday,
        //              ctime->tm_hour, ctime->tm_min, ctime->tm_sec);

        //     // va_list s;
        //     // va_start(s, format);
        //     char rightbuffer[SIZE];
        //     vsnprintf(rightbuffer, sizeof(rightbuffer), format, s);
        //     // va_end(s);

        //     // 格式：默认部分+自定义部分
        //     char logtxt[SIZE * 2];
        //     snprintf(logtxt, sizeof(logtxt), "%s %s\n", leftbuffer, rightbuffer);

        //     // printf("%s", logtxt); // 暂时打印
        //     printLog(level, logtxt);
        // }
        void printLog(int level, const std::string &logtxt)
        {
            switch (printMethod)
            {
            case Screen:
                std::cout << logtxt << std::endl;
                break;
            case Onefile:
                printOneFile(LogFile, logtxt);
                break;
            case Classfile:
                printClassFile(level, logtxt);
                break;
            default:
                break;
            }
        }
        void printOneFile(const std::string &logname, const std::string &logtxt)
        {
            std::string _logname = path + logname;
            int fd = open(_logname.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0666); // "log.txt"
            if (fd < 0) std::cerr << "open file" << std::endl;
            write(fd, logtxt.c_str(), logtxt.size());
            close(fd);
        }
        void printClassFile(int level, const std::string &logtxt)
        {
            std::string filename = LogFile;
            filename += ".";
            filename += levelToString(level); // "log.txt.Debug/Warning/Fatal"
            printOneFile(filename, logtxt);
        }

        ~Log()
        {
        }
        void operator()(int level, const char *format, ...)
        {
            time_t t = time(nullptr);
            struct tm *ctime = localtime(&t);
            char leftbuffer[SIZE];
            snprintf(leftbuffer, sizeof(leftbuffer), "[%s][%d-%d-%d %d:%d:%d]", levelToString(level).c_str(),
                     ctime->tm_year + 1900, ctime->tm_mon + 1, ctime->tm_mday,
                     ctime->tm_hour, ctime->tm_min, ctime->tm_sec);

            va_list s;
            va_start(s, format);
            char rightbuffer[SIZE];
            vsnprintf(rightbuffer, sizeof(rightbuffer), format, s);
            va_end(s);

            // 格式：默认部分+自定义部分
            char logtxt[SIZE * 2];
            snprintf(logtxt, sizeof(logtxt), "%s %s\n", leftbuffer, rightbuffer);

            // printf("%s", logtxt); // 暂时打印
            printLog(level, logtxt);
        }

    private:
        int printMethod;
        std::string path;
    };

}