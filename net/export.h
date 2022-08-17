#ifndef NET_LIBRARY
#define NET_EXPORT __declspec(dllexport)
#else
#define NET_EXPORT __declspec(dllimport)
#endif