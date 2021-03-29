#ifdef _WINDOWS

#include <malloc.h>
#include "MemoryUtils.h"

/* static */ long MemoryUtils::HeapUsed()
{
    /// returns used heap size in bytes or negative if heap is corrupted.
    _HEAPINFO info = { 0, 0, 0 };
    long used = 0;
    int rc;

    while ((rc=_heapwalk(&info)) == _HEAPOK)
    {
        if (info._useflag == _USEDENTRY)
            used += info._size;
    }
    if (rc != _HEAPEND && rc != _HEAPEMPTY)
        used = (used?-used:-1);

    return used;
}

#endif
