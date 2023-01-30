#ifndef UTILS_H_
#define UTILS_H_

#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <cstring>

#define INFO __FILE__, __LINE__
enum{

TRACE_LEVEL_ERROR = 0,
TRACE_LEVEL_WARNING,
TRACE_LEVEL_NORMAL,
TRACE_LEVEL_DEBUG,
TRACE_LEVEL_DISABLE
};


void traceEvent(int eventTraceLevel,
		       const char* file, const int line, const char * format, ...);

#endif