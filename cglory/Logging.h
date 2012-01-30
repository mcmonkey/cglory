#pragma once

#define LOGGING
#define L_SECTION_EVENTS 0

#define L_SECTION_API_MAX 255

#ifdef LOGGING
	#define LOG(s, m) log(s, m)
	#define WARNING(s, m) warning(s, m)
	#define ERROR(s, m) error(s, m)
#else
	#define LOG(s, m)
	#define WARNING(s, m)
	#define ERROR(s, m)
#endif

namespace logging
{
	void log(int section, char* message);
	void warning(int section, char* message);
	void error(int section, char* message);
}