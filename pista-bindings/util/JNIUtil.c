
#include <stdio.h>
#include "JNIUtil.h"

void c_unbuf() {
	setvbuf(stdout, NULL, _IOLBF, 0);
	setvbuf(stderr, NULL, _IOLBF, 0);
}

