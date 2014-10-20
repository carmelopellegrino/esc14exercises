#ifndef ESC_API_H
#define ESC_API_H

#define ESC_TYPE_INT 0
#define ESC_TYPE_FLOAT 1
#define ESC_TYPE_DOUBLE 2

#define ESC_ACCURACY_DEFAULT 1e-10

#ifdef __cplusplus
extern "C" 
#endif
int esc_start(const char* address, const char* ex_id, const char* username, const char* password);

#ifdef __cplusplus
extern "C" 
#endif
int esc_finish(void* ptr, int count, int esc_datatype_id, double accuracy);

#ifdef __cplusplus
extern "C" 
#endif
int esc_start_auto_(const char* file);

#ifdef __cplusplus
#include <cstring>
#else
#include "string.h"
#endif

inline char *my_basename(char *path)
{
    char *base = strrchr(path, '/');
    return base ? base+1 : path;
}

#define ESC_DEFAULT_ENDPOINT "192.168.1.10:5202"
#define ESC_START_DEFAULT_SEED(username,password,default_seed) esc_start(ESC_DEFAULT_ENDPOINT,my_basename(__FILE__),username,password)
#define ESC_START(username,password) esc_start(ESC_DEFAULT_ENDPOINT,my_basename(__FILE__),username,password)
#define ESC_FINISH(solution,n,type,accuracy) esc_finish(solution,n,type,accuracy)

#define esc_start_auto() esc_start_auto_(__FILE__)

#endif
