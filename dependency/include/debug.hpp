#ifndef DEBUG_HPP
#define DEBUG_HPP



#define DEBUG
#ifdef DEBUG 

#define DEBUG_STMT(stmt) stmt

#else

#define DEBUG_STMT(stmt) {}

#endif 
#define DEBUG_LOG(msg) DEBUG_STMT(printf("%s\n", msg))
#define DEBUG_LOGF(fmt, args...) DEBUG_STMT(printf(fmt, args))

#endif
