#ifndef OPENGLPROJECT_LOGGER_H
#define OPENGLPROJECT_LOGGER_H

class Logger {
public:
    static void Info(const char* message);
    static void Warning(const char* message);
    static void Error(const char* message);
};

#endif //OPENGLPROJECT_LOGGER_H
