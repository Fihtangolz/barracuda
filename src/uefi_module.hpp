//
// Created by mrsmith on 08.07.18.
//

#ifndef KERNEL_UEFI_MODULE_HPP
#define KERNEL_UEFI_MODULE_HPP

// Unified Extensible Firmware Interface
// Base on Version 2.7 Errata A August 2017
namespace UEFI {
    //UEFI's defined type TODO
    typedef int UINT32;
    typedef int UINT64;
    typedef int INTN;
    typedef void VOID;
    typedef bool BOOLEAN;
    typedef unsigned int UINTN;
    typedef int CHAR16;
    typedef int UINT16;
    typedef int UINT8;
    typedef int INT16;

    typedef int EFI_TIME_CAPABILITIES;
    typedef int EFI_MEMORY_DESCRIPTOR;
    typedef int EFI_PHYSICAL_ADDRESS;

    typedef struct {
        UINT64 Signature;
        UINT32 Revision;
        UINT32 HeaderSize;
        UINT32 CRC32;
        UINT32 Reserved;
    } EFI_TABLE_HEADER;

    enum class EFI_STATUS:INTN{
        EFI_SUCCESS,
        EFI_LOAD_ERROR,
        EFI_INVALID_PARAMETER,
        EFI_UNSUPPORTED,
        EFI_BAD_BUFFER_SIZE,
        EFI_BUFFER_TOO_SMALL,
        EFI_NOT_READY,
        EFI_DEVICE_ERROR,
        EFI_WRITE_PROTECTED,
        EFI_OUT_OF_RESOURCES,
        EFI_VOLUME_CORRUPTED,
        EFI_VOLUME_FULL,
        EFI_NO_MEDIA,
        EFI_MEDIA_CHANGED,
        EFI_NOT_FOUND,
        EFI_ACCESS_DENIED,
        EFI_NO_MAPPING,
        EFI_TIMEOUT,
        EFI_NOT_STARTED,
        EFI_ALREADY_STARTED,
        EFI_ABORTED,
        EFI_ICMP_ERROR,
        EFI_TFTP_ERROR,
        EFI_PROTOCOL_ERROR,
        EFI_INCOMPATIBLE_VERSION,
        EFI_SECURITY_VIOLATION,
        EFI_CRC_ERROR,
        EFI_END_OF_MEDIA,
        EFI_END_OF_FILE,
        EFI_WARN_UNKNOWN_GLYPH,
        EFI_WARN_DELETE_FAILURE,
        EFI_WARN_WRITE_FAILURE,
    };

#define OUT
#define IN
#define OPTIONAL

    typedef struct {
        UINT16 Year;  // 1900 – 9999
        UINT8 Month;  // 1 – 12
        UINT8 Day;    // 1 – 31
        UINT8 Hour;   // 0 – 23
        UINT8 Minute; // 0 – 59
        UINT8 Second; // 0 – 59
        UINT8 Pad1;
        UINT32 Nanosecond; // 0 – 999,999,999
        INT16 TimeZone;    // -1440 to 1440 or 2047
        UINT8 Daylight;
        UINT8 Pad2;
    } EFI_TIME;

    typedef struct {
        UINT32 Data1;
        UINT16 Data2;
        UINT16 Data3;
        UINT8 Data4[8];
    } EFI_GUID;

    typedef enum {
        EfiResetCold,
        EfiResetWarm,
        EfiResetShutdown,
        EfiResetPlatformSpecific,
    } EFI_RESET_TYPE;

    typedef struct {
        EFI_GUID CapsuleGuid;
        UINT32 HeaderSize;
        UINT32 Flags;
        UINT32 CapsuleImageSize;
    } EFI_CAPSULE_HEADER;



    typedef EFI_STATUS (*EFI_GET_TIME)(
            OUT EFI_TIME *Time,
            OUT EFI_TIME_CAPABILITIES *Capabilities OPTIONAL
    );

    typedef EFI_STATUS (*EFI_SET_TIME)(
            IN EFI_TIME *Time
    );

    typedef EFI_STATUS (*EFI_GET_WAKEUP_TIME)(
            OUT BOOLEAN *Enabled,
            OUT BOOLEAN *Pending,
            OUT EFI_TIME *Time
    );

    typedef EFI_STATUS (*EFI_SET_WAKEUP_TIME)(
            IN BOOLEAN Enable,
            IN EFI_TIME *Time OPTIONAL
    );

    typedef EFI_STATUS (*EFI_SET_VIRTUAL_ADDRESS_MAP)(
            IN UINTN MemoryMapSize,
            IN UINTN DescriptorSize,
            IN UINT32 DescriptorVersion,
            IN EFI_MEMORY_DESCRIPTOR *VirtualMap
    );

    typedef EFI_STATUS (*EFI_CONVERT_POINTER)(
            IN UINTN DebugDisposition,
            IN VOID **Address
    );

    typedef EFI_STATUS (*EFI_GET_VARIABLE)(
            IN CHAR16 *VariableName,
            IN EFI_GUID *VendorGuid,
            OUT UINT32 *Attributes OPTIONAL,
            IN OUT UINTN *DataSize,
            OUT VOID *Data OPTIONAL
    );

    typedef EFI_STATUS (*EFI_GET_NEXT_VARIABLE_NAME)(
            IN OUT UINTN *VariableNameSize,
            IN OUT CHAR16 *VariableName,
            IN OUT EFI_GUID *VendorGuid
    );

    typedef EFI_STATUS (*EFI_SET_VARIABLE)(
            IN CHAR16 *VariableName,
            IN EFI_GUID *VendorGuid,
            IN UINT32 Attributes,
            IN UINTN DataSize,
            IN VOID *Data
    );

    typedef EFI_STATUS (*EFI_GET_NEXT_HIGH_MONO_COUNT)(
            OUT UINT32 *HighCount
    );

    typedef VOID (*EFI_RESET_SYSTEM) (
            IN EFI_RESET_TYPE ResetType,
            IN EFI_STATUS ResetStatus,
            IN UINTN DataSize,
            IN VOID *ResetData OPTIONAL
    );

    typedef EFI_STATUS (*EFI_UPDATE_CAPSULE)(
            IN EFI_CAPSULE_HEADER **CapsuleHeaderArray,
            IN UINTN CapsuleCount,
            IN EFI_PHYSICAL_ADDRESS ScatterGatherList OPTIONAL
    );

    typedef EFI_STATUS (*EFI_QUERY_CAPSULE_CAPABILITIES)(
            IN EFI_CAPSULE_HEADER **CapsuleHeaderArray,
            IN UINTN CapsuleCount,
            OUT UINT64 *MaximumCapsuleSize,
            OUT EFI_RESET_TYPE *ResetType
    );

    typedef EFI_STATUS (*EFI_QUERY_VARIABLE_INFO)(
            IN UINT32 Attributes,
            OUT UINT64 *MaximumVariableStorageSize,
            OUT UINT64 *RemainingVariableStorageSize,
            OUT UINT64 *MaximumVariableSize
    );

    typedef struct {
        EFI_TABLE_HEADER Hdr;

        // Time Services
        EFI_GET_TIME GetTime;
        EFI_SET_TIME SetTime;
        EFI_GET_WAKEUP_TIME GetWakeupTime;
        EFI_SET_WAKEUP_TIME SetWakeupTime;

        // Virtual Memory Services
        EFI_SET_VIRTUAL_ADDRESS_MAP SetVirtualAddressMap;
        EFI_CONVERT_POINTER ConvertPointer;

        // Variable Services
        EFI_GET_VARIABLE GetVariable;
        EFI_GET_NEXT_VARIABLE_NAME GetNextVariableName;
        EFI_SET_VARIABLE SetVariable;

        // Miscellaneous Services
        EFI_GET_NEXT_HIGH_MONO_COUNT GetNextHighMonotonicCount;
        EFI_RESET_SYSTEM ResetSystem;

        //UEFI 2.0 Capsule Services
        EFI_UPDATE_CAPSULE UpdateCapsule;
        EFI_QUERY_CAPSULE_CAPABILITIES QueryCapsuleCapabilities;

        // Miscellaneous UEFI 2.0 Service
        EFI_QUERY_VARIABLE_INFO QueryVariableInfo;
    } EFI_RUNTIME_SERVICES;
}

#endif //KERNEL_UEFI_MODULE_HPP
