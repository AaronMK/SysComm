#ifndef _SYS_COMM_CONFIG_H_
#define _SYS_COMM_CONFIG_H_

#if !defined(SYS_COMM_DYNAMIC) || !defined(_WIN32)
#	define SYS_COMM_EXPORT
#else
#	ifdef SYS_COMM_BUILD
#		define SYS_COMM_EXPORT __declspec(dllexport)
#	else
#		define SYS_COMM_EXPORT __declspec(dllimport)
#	endif
#endif

#endif // _SYS_COMM_CONFIG_H_