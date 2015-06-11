#ifndef ASSERT_H
#define ASSERT_H
#include <OS.hpp>

#define v_ASSERT(expr) do { if(!expr) { \
    OS::get()->Log("v_ASSERT("#expr") failed in %s, on %i, in %s\n", \
            __FILE__,__LINE__,__PRETTY_FUNCTION__); \
    exit(1); \
}} while(0) 

#define v_ASSERTstr(expr, str) do { if(!expr) { \
    OS::get()->Log("v_ASSERT("#expr") failed in %s, on %i, in %s\n\t\"%s\"\n", \
            __FILE__,__LINE__,__PRETTY_FUNCTION__, str); \
    exit(1); \
}} while(0) 

#endif //ASSERT_H
