#include <iostream>
#include <slog/slog.h>

int main(int argc, char **argv) {
    starry::SLogger::initialize("C:/tmp/log.txt");
    sTrace() << "Hello, Starry Engine.";
    sDebug() << "Hello, Starry Engine.";
    sInfo() << "Hello, World!";
    sWarning() << "Hello, Starry Engine.";
    sCritical() << "Hello, Starry Engine.";
    sFatal() << "Hello, Starry Engine.";


    return 0;
}
