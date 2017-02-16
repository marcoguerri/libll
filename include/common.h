#ifndef __COMMON_H__
#define __COMMON_H__

#define ads_likely(x)       __builtin_expect((x),1)
#define ads_unlikely(x)     __builtin_expect((x),0)

#endif 
