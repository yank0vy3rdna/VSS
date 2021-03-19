#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include "headers.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        /* usage */
        printf("Usage: %s file\n", argv[0]);
    }

    int i;

    const char *filename = argv[1];
    FILE *file = fopen(filename, "rb");
    FILE *out_info = fopen("info.txt", "w");
    FILE *out_bin = fopen("binary_data", "wb");
    long size;
    char *data;

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);

    data = (char *) malloc(size * sizeof(char));

    fread(data, sizeof(char), size, file);


    union {
        char *ptr;
        int *num;
    } t{};

    t.ptr = &data[60];


    union {
        PE_Header *pe_head;
        char *data;
    } u{};

    u.data = &data[*t.num];

    if (u.pe_head->SizeOfOptionalHeader > 0) {

        unsigned long opt_head_start = *t.num + (24 * sizeof(char));

        char magic_str[2] = {data[opt_head_start], data[opt_head_start + 1]};

        union {
            char *str;
            short *magic;
        } v{};

        v.str = magic_str;

        if (*v.magic == 0x10b) {

            union {
                PE_Optional_Header *pe_opt_head;
                char *data;
            } w{};

            w.data = &data[opt_head_start];

            fprintf(out_info, "AddressOfEntryPoint: %#x\n\n",
                    w.pe_opt_head->AddressOfEntryPoint);
        } else if (*v.magic == 0x20b) {

            union {
                PE_Optional_Header_Plus *pe_opt_head;
                char *data;
            } w{};

            w.data = &data[opt_head_start];

            fprintf(out_info, "AddressOfEntryPoint: %#x\n\n",
                    w.pe_opt_head->AddressOfEntryPoint);

        }


        union {
            char *data;
            Section_Header *secttab;
        } s{};

        if (*v.magic == 0x10b) {
            s.data = &data[*t.num + sizeof(PE_Header) +
                           sizeof(PE_Optional_Header)];
        } else if (*v.magic == 0x20b) {
            s.data = &data[*t.num + sizeof(PE_Header) +
                           sizeof(PE_Optional_Header_Plus)];
        }

        unsigned int j;

        for (i = 0; i < u.pe_head->NumberOfSections; i++) {
            fprintf(out_info, "Name: ");

            union {
                uint64_t *name;
                char *seq;
            } name_seq{};

            name_seq.name = &s.secttab[i].Name;

            for (j = 0; j < 8; j++) {
                if (name_seq.seq[j] == 0) {
                    break;
                }
                fprintf(out_info, "%c", name_seq.seq[j]);
            }

            fprintf(out_info, "\n");

            fprintf(out_info, "VirtualSize: %x" PRId32 "\n", s.secttab[i].VirtualSize);
            fprintf(out_info, "VirtualAddress: %x" PRId32 "\n",
                    s.secttab[i].VirtualAddress);
            fprintf(out_info, "SizeOfRawData: %" PRId32 "\n", s.secttab[i].SizeOfRawData);
            fprintf(out_info, "PointerToRawData: %x" PRId32 "\n",
                    s.secttab[i].PointerToRawData);
            fprintf(out_info, "PointerToRelocations: %x" PRId32 "\n",
                    s.secttab[i].PointerToRelocations);
            fprintf(out_info, "PointerToLinenumbers: %x" PRId32 "\n",
                    s.secttab[i].PointerToLinenumbers);
            fprintf(out_info, "NumberOfRelocations: %" PRId16 "\n",
                    s.secttab[i].NumberOfRelocations);
            fprintf(out_info, "NumberOfLinenumbers: %" PRId16 "\n",
                    s.secttab[i].NumberOfLinenumbers);
            fprintf(out_info, "\n");

            if (strcmp(name_seq.seq, ".text") == 0) {
                fseek(file, s.secttab[i].PointerToRawData, SEEK_SET);
                char *binary_code = static_cast<char *>(malloc(s.secttab[i].SizeOfRawData));
                fread(binary_code, 1, s.secttab[i].SizeOfRawData, file);
                fwrite(binary_code, 1, s.secttab[i].SizeOfRawData, out_bin);
            }
        }

    }
    free(data);

    fclose(out_info);
    fclose(out_bin);
    fclose(file);

    return 0;
}
