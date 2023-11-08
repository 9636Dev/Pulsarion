#pragma once
#include "Pulsarion/Core/PulsarionCore.h"

#ifdef PLS_PLATFORM_WINDOWS
#include <winerror.h>
#else
#error "Pulsarion ErrorCodes only supports Windows!"
#endif

namespace Pulsarion:Error
{
    #ifdef PLS_PLATFORM_WINDOWS

    enum class ErrorCode
    {
        Success = S_OK,
        InvalidArguments = E_INVALIDARG,
        OutOfMemory = E_OUTOFMEMORY,
        NoInterface = E_NOINTERFACE,
        NotImpl = E_NOTIMPL,
        UnexpectedFailure = E_UNEXPECTED,
        FileNotFound = ERROR_FILE_NOT_FOUND,
        PathNotFound = ERROR_PATH_NOT_FOUND,
        AccessDenied = ERROR_ACCESS_DENIED,
        InvalidHandle = ERROR_INVALID_HANDLE,
        NotEnoughMemory = ERROR_NOT_ENOUGH_MEMORY,
        InvalidData = ERROR_INVALID_DATA,
        InvalidDrive = ERROR_INVALID_DRIVE,
        NoMoreFiles = ERROR_NO_MORE_FILES,
        WriteProtect = ERROR_WRITE_PROTECT,
        BadUnit = ERROR_BAD_UNIT,
        NotReady = ERROR_NOT_READY,
        BadCommand = ERROR_BAD_COMMAND,
        CRC = ERROR_CRC,
        BadLength = ERROR_BAD_LENGTH,
        Seek = ERROR_SEEK,
        NotDosDisk = ERROR_NOT_DOS_DISK,
        SectorNotFound = ERROR_SECTOR_NOT_FOUND,
        OutOfPaper = ERROR_OUT_OF_PAPER,
        WriteFault = ERROR_WRITE_FAULT,
        ReadFault = ERROR_READ_FAULT,
        GenFailure = ERROR_GEN_FAILURE,
        SharingViolation = ERROR_SHARING_VIOLATION,
        LockViolation = ERROR_LOCK_VIOLATION,
        WrongDisk = ERROR_WRONG_DISK,
        SharingBufferExceeded = ERROR_SHARING_BUFFER_EXCEEDED,
        HandleEof = ERROR_HANDLE_EOF,
        HandleDiskFull = ERROR_HANDLE_DISK_FULL,
        NotSupported = ERROR_NOT_SUPPORTED,
        RemNotList = ERROR_REM_NOT_LIST,
        DupName = ERROR_DUP_NAME,
        BadNetPath = ERROR_BAD_NETPATH
    };

    #else
    #error "Pulsarion ErrorCodes only supports Windows!"
    #endif

    namespace File
    {
        // Error codes related to file operators and the filesystem
        constexpr ErrorCode FileNotFound = ErrorCode::FileNotFound;
        constexpr ErrorCode PathNotFound = ErrorCode::PathNotFound;
        constexpr ErrorCode AccessDenied = ErrorCode::AccessDenied;
        constexpr ErrorCode InvalidHandle = ErrorCode::InvalidHandle;
        constexpr ErrorCode NotEnoughMemory = ErrorCode::NotEnoughMemory;
        constexpr ErrorCode InvalidDrive = ErrorCode::InvalidDrive;
    }
}
