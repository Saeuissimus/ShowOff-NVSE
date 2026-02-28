#include "JohnnyEventPredefinitions.h"

SRWLOCK EventsArrayMutex = SRWLOCK_INIT;
std::vector<EventInfo> EventsArray;

#if 0
void* __fastcall GenericCreateFilter(void** Filters, UInt32 numFilters) {
	return new JohnnyEventFiltersForm(Filters, numFilters);
}
#endif

EventInfo FindHandlerInfoByChar(const char* nameToFind)
{
	SRWSharedLock lock(EventsArrayMutex);
	auto it = EventsArray.begin();
	while (it != EventsArray.end())
	{
		if (!(_stricmp((*it)->EventName, nameToFind)))
			return *it;
		it++;
	}
	return NULL;
}

EventInfo __cdecl JGCreateEvent(const char* EventName, UInt8 maxArgs, UInt8 maxFilters, void* (__fastcall* CreatorFunction)(void**, UInt32))
{
	SRWUniqueLock lock(EventsArrayMutex);
	EventInfo eventinfo = new EventInformation(EventName, maxArgs, maxFilters, CreatorFunction);
	EventsArray.push_back(eventinfo);
	return eventinfo;
}


void __cdecl JGFreeEvent(EventInfo& toRemove)
{
	SRWUniqueLock lock(EventsArrayMutex);
	if (!toRemove) return;
	auto it = std::find(std::begin(EventsArray), std::end(EventsArray), toRemove);
	if (it != EventsArray.end())
	{
		delete* it;
		it = EventsArray.erase(it);
	}
	toRemove = NULL;
}

