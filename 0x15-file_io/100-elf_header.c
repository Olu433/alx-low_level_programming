#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>

void print_error(char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(98);
}

void print_elf_header(char *filename) {
    int fd;
    Elf64_Ehdr elf_header;

    if ((fd = open(filename, O_RDONLY)) == -1)
        print_error("Error: Cannot open file");

    if (lseek(fd, 0, SEEK_SET) == -1)
        print_error("Error: Cannot seek file");

    if (read(fd, &elf_header, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr))
        print_error("Error: Cannot read file");

    if (elf_header.e_ident[EI_MAG0] != ELFMAG0 ||
        elf_header.e_ident[EI_MAG1] != ELFMAG1 ||
        elf_header.e_ident[EI_MAG2] != ELFMAG2 ||
        elf_header.e_ident[EI_MAG3] != ELFMAG3)
        print_error("Error: Not an ELF file");

    printf("Magic:   ");
    for (int i = 0; i < EI_NIDENT; i++)
        printf("%02x ", elf_header.e_ident[i]);
    printf("\n");

    printf("Class:   %s\n", elf_header.e_ident[EI_CLASS] == ELFCLASS32 ? "ELF32" : "ELF64");
    printf("Data:    %s\n", elf_header.e_ident[EI_DATA] == ELFDATA2LSB ? "2's complement, little endian" : "2's complement, big endian");
    printf("Version: %d\n", elf_header.e_ident[EI_VERSION]);
    printf("OS/ABI:  %d\n", elf_header.e_ident[EI_OSABI]);
    printf("ABI Version: %d\n", elf_header.e_ident[EI_ABIVERSION]);

    printf("Type:    ");
    switch (elf_header.e_type) {
        case ET_NONE:
            printf("NONE (No file type)\n");
            break;
        case ET_REL:
            printf("REL (Relocatable file)\n");
            break;
        case ET_EXEC:
            printf("EXEC (Executable file)\n");
            break;
        case ET_DYN:
            printf("DYN (Shared object file)\n");
            break;
        case ET_CORE:
            printf("CORE (Core file)\n");
            break;
        default:
            printf("<unknown>\n");
            break;
    }

    printf("Entry point address: 0x%lx\n", elf_header.e_entry);

    printf("\nFormat:  the same as readelf -h (version 2.26.1)\n");

    close(fd);
}

int main(int argc, char **argv) {
    if (argc != 2)
        print_error("Usage: elf_header elf_filename");

    print_elf_header(argv[1]);

    return 0;
}
