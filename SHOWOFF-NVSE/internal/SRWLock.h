#pragma once
#include <windows.h>

class SRWSharedLock {
public:
    SRWSharedLock(PSRWLOCK apLock) : pLock(apLock) { AcquireSRWLockShared(pLock); }
    SRWSharedLock(SRWLOCK& arLock) : pLock(&arLock) { AcquireSRWLockShared(pLock); }
    ~SRWSharedLock() { ReleaseSRWLockShared(pLock); }
private:
    PSRWLOCK pLock;
};

class SRWUniqueLock {
public:
    SRWUniqueLock(PSRWLOCK apLock) : pLock(apLock) { AcquireSRWLockExclusive(pLock); }
    SRWUniqueLock(SRWLOCK& arLock) : pLock(&arLock) { AcquireSRWLockExclusive(pLock); }
    ~SRWUniqueLock() { ReleaseSRWLockExclusive(pLock); }
private:
    PSRWLOCK pLock;
};