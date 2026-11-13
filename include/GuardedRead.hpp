#pragma once

// guardread1: while this is above zero on a thread, that thread is reading
// memory that may have been freed under it (a destroyed object's slot) inside
// its own __try/__except. The crash handlers let such an access violation go
// to that __except instead of treating it as a crash.
inline thread_local int g_aliceGuardedReadDepth = 0;
