//
// Created by yank0vy3rdna on 18.03.2021.
//

#ifndef LAB1_HEADERS_H
#define LAB1_HEADERS_H


#include <cstdint>

typedef struct PE_Header
{
    uint8_t sig[4 * sizeof(char)]; // 4B
    uint16_t Machine; // 2B
    uint16_t NumberOfSections; // 2B
    uint32_t TimeDateStamp; // 4B
    uint32_t PointerToSymbolTable; // 4B
    uint32_t NumberOfSymbols; // 4B
    uint16_t SizeOfOptionalHeader; // 2B
    uint16_t Characteristics; // 2B
} PE_Header;

typedef struct PE_Data_Directory
{
    uint32_t RVA;
    uint32_t Size;
} PE_Data_Directory;

typedef struct PE_Optional_Header
{
    /* standard fields */
    uint16_t Magic;
    uint8_t MajorLinkerVersion;
    uint8_t MinorLinkerVersion;
    uint32_t SizeOfCode;
    uint32_t SizeOfInitializedData;
    uint32_t SizeOfUninitializedData;
    uint32_t AddressOfEntryPoint;
    uint32_t BaseOfCode;
    uint32_t BaseOfData;

    /* Windows-specific */
    uint32_t ImageBase;
    uint32_t SectionAlignment;
    uint32_t FileAlignment;
    uint16_t MajorOperatingSystemVersion;
    uint16_t MinorOperatingSystemVersion;
    uint16_t MajorImageVersion;
    uint16_t MinorImageVersion;
    uint16_t MajorSubsystemVersion;
    uint16_t MinorSubsystemVersion;
    uint32_t Win32VersionValue;
    uint32_t SizeOfImage;
    uint32_t SizeOfHeaders;
    uint32_t CheckSum;
    uint16_t Subsystem;
    uint16_t DllCharacteristics;
    uint32_t SizeOfStackReserve;
    uint32_t SizeOfStackCommit;
    uint32_t SizeOfHeapReserve;
    uint32_t SizeOfHeapCommit;
    uint32_t LoaderFlags;
    uint32_t NumberOfRvaAndSizes;

    /* data directories */
    PE_Data_Directory ExportTable;
    PE_Data_Directory ImportTable;
    PE_Data_Directory ResourceTable;
    PE_Data_Directory ExceptionTable;
    PE_Data_Directory CertificateTable;
    PE_Data_Directory BaseRelocationTable;
    PE_Data_Directory Debug;
    PE_Data_Directory Architecture;
    PE_Data_Directory GlobalPtr;
    PE_Data_Directory TLSTable;
    PE_Data_Directory LoadConfigTable;
    PE_Data_Directory BoundImport;
    PE_Data_Directory IAT;
    PE_Data_Directory DelayImportDescriptor;
    PE_Data_Directory CLRRuntimeHeader;
    PE_Data_Directory reserved;
} PE_Optional_Header;

typedef struct PE_Optional_Header_Plus
{
    /* standard fields */
    uint16_t Magic;
    uint8_t MajorLinkerVersion;
    uint8_t MinorLinkerVersion;
    uint32_t SizeOfCode;
    uint32_t SizeOfInitializedData;
    uint32_t SizeOfUninitializedData;
    uint32_t AddressOfEntryPoint;
    uint32_t BaseOfCode;
    uint32_t BaseOfData;

    /* Windows-specific */
    uint64_t ImageBase;
    uint32_t SectionAlignment;
    uint32_t FileAlignment;
    uint16_t MajorOperatingSystemVersion;
    uint16_t MinorOperatingSystemVersion;
    uint16_t MajorImageVersion;
    uint16_t MinorImageVersion;
    uint16_t MajorSubsystemVersion;
    uint16_t MinorSubsystemVersion;
    uint32_t Win32VersionValue;
    uint32_t SizeOfImage;
    uint32_t SizeOfHeaders;
    uint32_t CheckSum;
    uint16_t Subsystem;
    uint16_t DllCharacteristics;
    uint64_t SizeOfStackReserve;
    uint64_t SizeOfStackCommit;
    uint64_t SizeOfHeapReserve;
    uint64_t SizeOfHeapCommit;
    uint32_t LoaderFlags;
    uint32_t NumberOfRvaAndSizes;

    /* data directories */
    PE_Data_Directory ExportTable;
    PE_Data_Directory ImportTable;
    PE_Data_Directory ResourceTable;
    PE_Data_Directory ExceptionTable;
    PE_Data_Directory CertificateTable;
    PE_Data_Directory BaseRelocationTable;
    PE_Data_Directory Debug;
    PE_Data_Directory Architecture;
    PE_Data_Directory GlobalPtr;
    PE_Data_Directory TLSTable;
    PE_Data_Directory LoadConfigTable;
    PE_Data_Directory BoundImport;
    PE_Data_Directory IAT;
    PE_Data_Directory DelayImportDescriptor;
    PE_Data_Directory CLRRuntimeHeader;
    PE_Data_Directory reserved;
} PE_Optional_Header_Plus;

typedef struct Section_Header
{
    uint64_t Name;
    uint32_t VirtualSize;
    uint32_t VirtualAddress;
    uint32_t SizeOfRawData;
    uint32_t PointerToRawData;
    uint32_t PointerToRelocations;
    uint32_t PointerToLinenumbers;
    uint16_t NumberOfRelocations;
    uint16_t NumberOfLinenumbers;
    uint32_t Characteristics;
} Section_Header;


#endif //LAB1_HEADERS_H
