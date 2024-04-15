#ifndef STARRY_WIN_EXPORT_H
#define STARRY_WIN_EXPORT_H

#ifdef STARRY_SLOG_DLL
#define STARRY_SLOG_API __declspec(dllexport)
#else
#define STARRY_SLOG_API __declspec(dllimport)
#endif

#endif
