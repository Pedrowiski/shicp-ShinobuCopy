#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define buffer_size 1024

void genericFatalErrorMessage(const char *message) {
    printf("shicp: %s\n", message);
    exit(1);
}

void fileFatalErrorMessage(const char *file_name, const char *message) {
    printf("shicp: %s: %s\n", file_name, message);
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc < 3)
        genericFatalErrorMessage("Passe os arquivos ao programa\nFormato: ./shicp [remetente] [destinatário]");

    const unsigned char *sender = argv[1];
    const unsigned char *recipient = argv[2];
    char buffer[buffer_size] = {0};

    FILE *file_pointer_sender = fopen(sender, "rb");
    FILE *file_pointer_recipient = fopen(recipient, "wb");

    if (file_pointer_sender == NULL)
        fileFatalErrorMessage(sender, "O arquivo não existe");

    if (file_pointer_recipient == NULL)
        fileFatalErrorMessage(recipient, "Esse caminho não existe");

    unsigned int bytes_readed = 0;
    unsigned int bytes_writed = 0;

    do {
        bytes_readed = fread(buffer, 1, buffer_size, file_pointer_sender);
        bytes_writed = fwrite(buffer, 1, bytes_readed, file_pointer_recipient);
    } while (bytes_readed > 0);

    fclose(file_pointer_sender);
    fclose(file_pointer_recipient);

    return 0;
}
