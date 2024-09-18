#ifndef DEBUG_HPP
#define DEBUG_HPP



#define DEBUG
#ifdef DEBUG 

#define DEBUG_STMT(stmt) stmt

#else

#define DEBUG_STMT(stmt) {}

#endif 

#endif
