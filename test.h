/**
 * @brief Test Include functions
 * @author Michael Burmeister
 * @date January 26, 2021
 * @version 1.0
 * 
*/

typedef s32_t (*somefunc)(u32_t address, u32_t size);

#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif
