#ifndef UTILS_H_
#define UTILS_H_

#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <cstring>

#define INFO __FILE__, __LINE__

inline char log_file_path[] = ""; 
inline int TRACE_LEVEL = 3;
enum{

TRACE_LEVEL_ERROR = 0,
TRACE_LEVEL_WARNING,
TRACE_LEVEL_NORMAL,
TRACE_LEVEL_DEBUG,
TRACE_LEVEL_DISABLE
};

enum RC {
  RC_SUCCESS = 0,
  RC_UNDEFINED,
  RC_SOCKET_ERROR,
  RC_RECV_ERROR,
  RC_SENT_ERROR,
  RC_CONNECTION_ERROR,
  RC_ACCEPT_ERROR,
  RC_UNIMPLEMENTED
};

void traceEvent(int traceLevel, int eventTraceLevel,
		       const char* file, const int line, const char * format, ...);

//char *tuppercase(char *str);



#endif