// Criador de imagem DSK para HD MSX-DOS FAT 16
// Apos criacao, arquivo deve ser propriamente formatado no Nextor DOS
// Daniel Vicentini - 28 de junho de 2025
// Criado com ajuda de IA ;-)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MIN_SIZE_MB 32
#define MAX_SIZE_MB 4096
#define SECTOR_SIZE 512
#define DSK_FILENAME "msxdos_image.dsk"

// Prototipos
void create_fat16_image(const char *filename, int size_mb);

int main() {
    printf("=== Criador de Imagem HD MSX-DOS FAT16 (c) 2025 ===\n");

    int size_mb;
    printf("Digite o tamanho do disco (MB) [%d - %d]: ", MIN_SIZE_MB, MAX_SIZE_MB);
    if (scanf("%d", &size_mb) != 1) {
        fprintf(stderr, "Erro: entrada invalida.\n");
        return 1;
    }

    if (size_mb < MIN_SIZE_MB || size_mb > MAX_SIZE_MB) {
        fprintf(stderr, "Erro: o tamanho deve estar entre %d e %d MB.\n", MIN_SIZE_MB, MAX_SIZE_MB);
        return 1;
    }

    create_fat16_image(DSK_FILENAME, size_mb);

    printf("Imagem %s criada com sucesso com %d MB.\nNo MSX-Basic rodar o comando 'call fdisk' para formatar o disco.\n", DSK_FILENAME, size_mb);
    return 0;
}

// Cria imagem de disco simulando uma estrutura FAT16 simples
void create_fat16_image(const char *filename, int size_mb) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("Erro ao criar imagem");
        exit(1);
    }

    uint64_t total_size = (uint64_t)size_mb * 1024 * 1024;

    // Cabecalho simples do setor de boot FAT16 (não totalmente funcional)
    uint8_t boot_sector[SECTOR_SIZE] = {
        0xEB, 0x3C, 0x90,                       // JMP + NOP
        'M', 'S', 'D', 'O', 'S', '5', '.', '0', // OEM Name
        0x00, 0x02,                             // Bytes por setor (512)
        0x01,                                   // Setores por cluster
        0x01, 0x00,                             // Reservado
        0x02,                                   // N. FATs
        0x00, 0x02,                             // Max root entries
        0x00, 0x00,                             // Total setores (se < 32MB)
        0xF8,                                   // Midia removivel
        0x01, 0x00,                             // Setores por FAT
        0x3F, 0x00,                             // Setores por trilha
        0xFF, 0x00,                             // Cabecas
        0x00, 0x00, 0x00, 0x00,                 // Setores ocultos
        0x00, 0x00, 0x00, 0x00,                 // Total setores (grande)
        // ... preenchido depois
    };

    // Escreve setor de boot
    fwrite(boot_sector, 1, SECTOR_SIZE, fp);

    // Preenche o restante do primeiro cluster com 0
    uint8_t zero[SECTOR_SIZE] = {0};
    for (int i = 1; i < 64; i++) {
        fwrite(zero, 1, SECTOR_SIZE, fp);
    }

    // Escreve o restante do disco com 0
    uint64_t written = SECTOR_SIZE * 64;
    while (written < total_size) {
        fwrite(zero, 1, SECTOR_SIZE, fp);
        written += SECTOR_SIZE;
    }

    fclose(fp);
}