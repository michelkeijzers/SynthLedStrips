#pragma once

class MemoryUtils
{
public:
    /// returns used heap size in bytes or negative if heap is corrupted.
    static long HeapUsed();

private:
    MemoryUtils();
};
