#ifndef QVS_DBG_HPP
#define QVS_DBG_HPP

//#include <cstdio>
#include <cstdio>
#include <cerrno>
#include <cstring>
//#include <string>

#ifdef NDEBUG

#define debug(M, ...)

#else

#define debug(M, ...) fprintf(stderr,      \
			      "DEBUG %s:%d> " M "\n", \
			      __FILE__, __LINE__, ##__VA_ARGS__)
#endif //NDEBUG


#define clean_errno() errno == 0 ? "None": strerror(errno)


#define log_err(M, ...) fprintf(stderr,			\
				"[ERROR] (%s:%d: errno: %s) " M "\n",\
				__FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr,			\
				"[WARN] (%s:%d errno: %s): " M "\n",\
				__FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr,		\
				 "[WARN] (%s:%d): " M "\n",	\
				__FILE__, __LINE__, ##__VA_ARGS__)
    

#define check(A, M, ...) if(!(A)){\
	log_err(M, ##__VA_ARGS__); errno=0; goto error;}

#define sentinel(M, ...) check(0, M, ##__VA_ARGS__)

#define check_mem(A) check((A), "Out of Memory.")

#define check_debug(A, M, ...) if(!(A))\
    {debug(M, ##__VA_ARGS__); errno=0; goto error;}

#endif //_DBG_H
