#include <stdio.h>
#include <stdlib.h>

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

    FILE *file_pointer_sender = fopen(sender, "rb");
    FILE *file_pointer_recipient = fopen(recipient, "wb");

    if (file_pointer_sender == NULL)
        fileFatalErrorMessage(sender, "O arquivo não existe");

    if (file_pointer_recipient == NULL)
        fileFatalErrorMessage(recipient, "Esse caminho não existe");

    signed char file_reader;

    while ((file_reader = fgetc(file_pointer_sender)) != EOF)
        fputc(file_reader, file_pointer_recipient);

    return 0;
}
