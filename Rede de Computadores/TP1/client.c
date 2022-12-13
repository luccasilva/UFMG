#include "common.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFSZ 1024

void usage(int argc, char **argv) {
    printf("usage: %s <server IP> <server port>\n", argv[0]);
    printf("exemple: %s 127.0.0.1 5151\n", argv[0]);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
    if (argc < 3){
        usage(argc, argv);
    }

    struct sockaddr_storage storage;
    if( 0 != addrparse(argv[1], argv[2], &storage) ){
        usage(argc, argv);
    }

    // Inicializar Socket
    int s;
    s = socket(storage.ss_family, SOCK_STREAM, 0);
    if( s == -1 ){
        logexit("socket");
    }

    // Inicializar Conexao
    struct sockaddr *addr = (struct sockaddr *)(&storage);
    if( 0 != connect(s, addr, sizeof(storage)) ){
        logexit("connect");
    }

    char addrstr[BUFSZ];
    addrtostr(addr, addrstr, BUFSZ);

    printf("connected to %s \n", addrstr);

    char msg[BUFSZ];
    char res[BUFSZ];

    while(1) {
        fflush(stdin);
        memset(msg, 0, BUFSZ);
        memset(res, 0, BUFSZ);

        //Leitura e envio da mensagem pro servidor
        scanf("%[^\n]%*c", msg);
        if(strcmp(msg, "\n") != 0){
            int msglen = send(s, msg, strlen(msg), 0);

            //Tratamento de erro da mensagem enviada
            if (msglen != strlen(msg)) {
                logexit("send");
            }

            //Mensagem recebida do servidor
            recv(s, res, BUFSZ, 0);

            //Caso exit -> encerrar conexao
            if (strcmp(res, "exit") == 0) {
                break;
            }
            printf("%s", res);
        }
    }
    close(s);
    exit(EXIT_SUCCESS);
}
