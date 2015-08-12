#ifndef MEMORY_H
#define MEMORY_H

#include "CacheInterface.h"

class Memory : public CacheInterface {
  public:
    Memory(int length);
    void CacheEvent(SSEEvent* event);
    deque<string> GetEventsSinceId(string lastId);
    deque<string> GetAllEvents();
    int GetSizeOfCachedEvents();
    CacheConfig _config;

  private:
    deque<string> _cache_keys;
    map<string, SSEEventPtr> _cache_data;
};
#endif
