#pragma once

void log_error(const char *file, int line, const char *func, const char *format, ...);
// ERROR macro
#define ERROR(format, ...) log_error(__FILE__, __LINE__, __func__, format, ##__VA_ARGS__)

