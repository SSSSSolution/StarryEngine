#include "slog/slog.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace starry {

SLogLevel SLogger::s_logLevel = SLogLevel::Trace;

SLogHandler SLogger::s_logHandler = nullptr;

std::filesystem::path SLogger::s_logPath = "";

std::shared_ptr<spdlog::logger> g_spdLogger = nullptr;

std::string addFileLineToMsg(const SMessageContext &context, const char *msg) {
    std::string ret;

    std::string fileName;
    if (context.file != nullptr) {
        fileName = std::filesystem::path(context.file).filename().string();
    }

    return std::string("[") + fileName + ":" + std::to_string(context.line) + std::string("] ") + msg;
}

void SLogger::initialize(const char *logPath) {
    if (!g_spdLogger) {
        SLogger::s_logPath = logPath;
        g_spdLogger = spdlog::basic_logger_mt("SLogger", SLogger::s_logPath.string());
        spdlog::set_default_logger(g_spdLogger);
        spdlog::set_level(spdlog::level::trace);
        spdlog::set_pattern("[%l] [%Y-%m-%d %H:%M:%S.%e] %v");
    }

    SLogger::setLogHandler([](const SMessageContext &context, const char *msg){
        if (g_spdLogger) {
            switch (context.level) {
            case SLogLevel::Trace:
                g_spdLogger->trace(msg);
                break;
            case SLogLevel::Debug:
                g_spdLogger->debug(msg);
                break;
            case SLogLevel::Info:
                g_spdLogger->info(msg);
                break;
            case SLogLevel::Warn:
                g_spdLogger->warn(addFileLineToMsg(context, msg));
                break;
            case SLogLevel::Error:
                g_spdLogger->error(addFileLineToMsg(context, msg));
                break;
            case SLogLevel::Fatal:
                g_spdLogger->critical(addFileLineToMsg(context, msg));
                break;
            }

            g_spdLogger->flush();
        }
    });
}



}
