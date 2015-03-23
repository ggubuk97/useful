#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

#ifndef USE_LOG
#define USE_LOG       1
#endif

#ifndef LOG_LEVEL
#define LOG_LEVEL     2 // 0 :VERBOS ] 1:DEBUG ] 2:INFO ] 3:ERROR
#endif

#ifndef LOG_VERBOSE
#define LOG_VERBOSE 0
#endif


#ifndef LOGTAG
#define LOGTAG  "debug" // to use different tag, define LOGTAG before including .
#endif

// for SDET automation test
#define SDETTAG "sdet "

enum { LWM_LOGV=0, LWM_LOGD, LWM_LOGI, LWM_LOGE };

#if ( USE_LOG )
#define log_printf( ... )  printf(__VA_ARGS__)

#define LOG_PRINT( ... ) do {\
            log_printf(__VA_ARGS__);\
            log_printf("\n");\
            } while(0)

#define LOG_TAG_LEVEL( TAG, LEVEL ) do {\
      printInformation( TAG, LEVEL );\
    } while(0)

#define LWMLOG( TAG, LEVEL, ... )\
    do{\
      if ( LEVEL >= LOG_LEVEL ) {\
        LOG_TAG_LEVEL( TAG, LEVEL );\
        LOG_PRINT(__VA_ARGS__);\
      } else {\
      }\
    } while(0)
#else
  #define LWMLOG( TAG, LEVEL, ... )        do{ } while(0)
#endif



#define LOG_IF_NONZERO(cond, format, args...) {   \
      if(int ret = cond) {                        \
        LWMLOG(LOGTAG, LWM_LOGE,                  \
              format ", error(%s:%d) : %s => %d", ##args,\
              __func__, __LINE__, #cond, ret);    \
      } else {                                    \
        LWMLOG(LOGTAG, LWM_LOGD, format, ##args); \
      }                                           \
    }

#define BREAK_IF_NONZERO(cond, format, args...) { \
      if(int ret = cond) {                        \
        LWMLOG(LOGTAG, LWM_LOGE,                  \
              format ", error(%s:%d) : %s => %d", ##args,\
              __func__, __LINE__, #cond, ret);    \
        break;                                    \
      } else {                                    \
        LWMLOG(LOGTAG, LWM_LOGD, format, ##args); \
      }                                           \
    }


#if ( USE_LOG )
static inline void printInformation ( const char* TAG, int lev )
{
  char  level = ' ';
  struct timeval now;
  time_t  nowTT;
  struct tm* nowTM;
  char dateTimeStr[ 24 ];
  unsigned long tid;

  switch(lev) {
    case LWM_LOGV: level = 'V'; break;
    case LWM_LOGD: level = 'D'; break;
    case LWM_LOGI: level = 'I'; break;
    case LWM_LOGE: level = 'E'; break;
  }

  fflush(stdout);
  /* if LOG_VERBOSE is 1,
   * it indicates FULL log containing tid and time information.
   * Otherwise, SIMPLE log. */
  if (  LOG_VERBOSE == 1 ) {
    gettimeofday( &now, NULL );
    nowTT = now.tv_sec;
    nowTM = localtime( &nowTT );
    strftime( dateTimeStr, sizeof( dateTimeStr ), "%H:%M:%S", nowTM );
    tid = (unsigned long) pthread_self();
    log_printf("  [%c] (%s.%03u / %#lx) [%s] ",
        level, dateTimeStr, (int)now.tv_usec/1000, tid, TAG );
  } else {
    log_printf("  [%c] [%s] ", level, TAG );
  }
  fflush(stdout);
}
#endif

