#ifndef STARRY_SLOG_H
#define STARRY_SLOG_H

#include <sstream>
#include <filesystem>
#include "WinExport.h"

#define sTrace()    starry::SLogger(starry::SLogLevel::Trace, __FILE__, __LINE__)
#define sDebug()    starry::SLogger(starry::SLogLevel::Debug, __FILE__, __LINE__)
#define sInfo()     starry::SLogger(starry::SLogLevel::Info,  __FILE__, __LINE__)
#define sWarning()  starry::SLogger(starry::SLogLevel::Warn,  __FILE__, __LINE__)
#define sCritical() starry::SLogger(starry::SLogLevel::Error, __FILE__, __LINE__)
#define sFatal()    starry::SLogger(starry::SLogLevel::Fatal, __FILE__, __LINE__)

namespace starry {

enum SLogLevel {
    Trace,
    Debug,
    Info,
    Warn,
    Error,
    Fatal,
};

struct STARRY_SLOG_API SMessageContext {
    SLogLevel level = SLogLevel::Info;
    int line;
    const char *file = nullptr;
};

typedef void (*SLogHandler)(const SMessageContext &context, const char *message);

class STARRY_SLOG_API SLogger {
public:
    SLogger(SLogLevel level, const char *file, int line) :
        m_context({level, line, file}) {
    }

    ~SLogger() {
        if (m_context.level < s_logLevel) {
            return;
        }

        try {
            std::string message = m_oss.str();
            if (s_logHandler) {
                s_logHandler(m_context, message.c_str());
            } else {
                printf("[%s] %s:%d %s\n", toString(m_context.level), m_context.file, m_context.line, message.c_str());
            }
        } catch (...) {
            printf("Error in SLogger destructor\n");
        }
    }

    template <typename T>
    SLogger& operator<<(const T& value) {
        if (s_logLevel <= m_context.level) {
            m_oss << value;
        }
        return *this;
    }

    // Thread unsafe
    static void setLogLevel(SLogLevel level) {
        s_logLevel = level;
    }

    static SLogLevel getLogLevel() {
        return s_logLevel;
    }

    // Thread unsafe
    static void setLogHandler(SLogHandler handler) {
        s_logHandler = handler;
    }

    // Thread unsafe
    static void initialize(const char *logPath);

private:
    const char *toString(SLogLevel level) {
        switch(level) {
        case SLogLevel::Trace:
            return "Trace";
        case SLogLevel::Debug:
            return "Debug";
        case SLogLevel::Info:
            return "Info";
        case SLogLevel::Warn:
            return "Warn";
        case SLogLevel::Error:
            return "Error";
        case SLogLevel::Fatal:
            return "Fatal";
        default:
            return "UNKNOWN";
        }
    }

private:
    std::ostringstream m_oss;
    SMessageContext m_context;
    static SLogHandler s_logHandler;
    static SLogLevel s_logLevel;
    static std::filesystem::path s_logPath;
};

}

#endif
