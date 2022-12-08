#pragma once

#include "Instrumentor.h"

#define DEBUG false

#if DEBUG

#define INIT_TIMER(name) Instrumentor::Get().BeginSession(name);
#define END_TIMER Instrumentor::Get().EndSession();
#define TIME_IT(name) InstrumentationTimer timer(name);

#else

#define TIME_IT(name)
#define INIT_TIMER(name)
#define END_TIMER

#endif // DEBUG