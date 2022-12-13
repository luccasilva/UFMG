#include "common.h"

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <math.h>
#include <stdio.h>

#define BUFSZ 1024
#define MAX_EQUIP 10

pthread_t tid_send;
pthread_t tid_recv;

struct Equip_s
{
    int ids[MAX_EQUIP];
    int myId;
} Equip_default = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 0};
typedef struct Equip_s Equip;

int sendConnection = 1;
int recvConnection = 1;

Equip equip;

struct client_data
{
    int s;
};

void usage(int argc, char **argv)
{
    printf("usage: %s <server IP> <server port>\n", argv[0]);
    printf("exemple: %s 127.0.0.1 51511\n", argv[0]);
    exit(EXIT_FAILURE);
}

void substring(char s[], char sub[], int p, int l)
{
    int c = 0;
    while (c < l)
    {
        sub[c] = s[p + c - 1];
        c++;
    }
    sub[c] = '\0';
}

float getTemperature()
{
    float scale = rand() / (float)RAND_MAX;
    return scale * 10;
}

void list()
{
    char list[BUFSZ] = "";
    char id[4] = "";

    for (int i = 0; i < MAX_EQUIP; ++i)
    {
        if (equip.ids[i] == 1)
        {
            snprintf(id, 4, "0%d ", i + 1);
            strcat(list, id);
        }
    }
    printf("%s\n", list);
}

int req_inf(char msg[BUFSZ], int csock)
{
    char id[BUFSZ] = "";
    substring(msg, id, 27, strlen(msg));
    char *idRes = strtok(id, "\n");
    int intId = atoi(idRes);

    int finalId1 = equip.myId;
    int finalId2 = intId;

    if (equip.myId == 10)
        finalId1 = 0;

    if (intId == 10)
        finalId2 = 0;

    snprintf(msg, 1024, "REQ_INF(0%d, 0%d)\n", finalId1, finalId2);
    int sentmsgLength = send(csock, msg, strlen(msg), 0);
    if (sentmsgLength != strlen(msg))
    {
        logexit("send");
    }
    return 1;
}

int res_add(char res[BUFSZ], int size)
{
    char id[BUFSZ] = "";
    substring(res, id, 10, size);
    char *idRes = strtok(id, ")");
    int intId = atoi(idRes);

    if (equip.myId == 0)
    {
        equip.myId = intId;
        equip.ids[intId - 1] = 2;
        printf("New ID: 0%d\n", intId);
    }

    if (equip.ids[intId - 1] == 0)
    {
        equip.ids[intId - 1] = 1;
        printf("Equipment 0%d added\n", intId);
    }
    return 1;
}

int res_list(char res[BUFSZ], int size)
{
    char arrayId[BUFSZ] = "";
    substring(res, arrayId, 10, size);
    char *ids = strtok(arrayId, ")");

    for (int i = 0; i < MAX_EQUIP; ++i)
    {
        char c = ids[i * 2];
        if (c == '1' && equip.ids[i] == 0)
        {
            equip.ids[i] = 1;
        }
    }

    return 1;
}

int req_rem(char res[BUFSZ], int size)
{
    char id[BUFSZ] = "";
    substring(res, id, 9, size);
    char *idRes = strtok(id, ")");
    int intId = atoi(idRes);

    equip.ids[intId - 1] = 0;
    printf("Equipment 0%d removed\n", intId);

    return 1;
}

int requested_inf(char *msg, int size, int csock)
{
    char id1[BUFSZ] = "";
    substring(msg, id1, 9, size);
    strtok(id1, ",");
    int intId1 = atoi(id1);

    char id2[BUFSZ] = "";
    substring(msg, id2, 12, size);
    strtok(id2, "\n");
    int intId2 = atoi(id2);

    printf("requested information\n");

    int finalId1 = intId1;
    int finalId2 = intId2;

    if (intId1 == 10)
        finalId1 = 0;

    if (intId2 == 10)
        finalId2 = 0;

    snprintf(msg, 1024, "RES_INF(0%d, 0%d, %.2f)\n", finalId2, finalId1, getTemperature());
    int sentmsgLength = send(csock, msg, strlen(msg), 0);
    if (sentmsgLength != strlen(msg))
    {
        logexit("send");
    }
    return 1;
}

int res_inf(char *msg, int size, int csock)
{
    char id[BUFSZ] = "";
    substring(msg, id, 9, size);
    strtok(id, ",");
    int intId = atoi(id);

    int finalId = intId;

    if (intId == 0)
        finalId = 10;

    char payload[20] = "";
    substring(msg, payload, 17, size);
    strtok(payload, ")");

    printf("Value from 0%d: %s\n", finalId, payload);

    return 1;
}

int parseSendCommand(char info[BUFSZ])
{
    char cmd[BUFSZ] = "";
    memcpy(cmd, info, strlen(info) + 1);
    char *command = strtok(cmd, "0");

    if (strcmp(command, "close connection") == 0)
    {
        return 1;
    }
    else if (strcmp(command, "list equipment") == 0)
    {
        return 2;
    }
    else if (strcmp(command, "request information from ") == 0)
    {
        return 3;
    }
    return -1;
}

void *send_thread(void *data)
{
    struct client_data *cdata = (struct client_data *)data;
    while (sendConnection)
    {
        char msg[BUFSZ];
        memset(msg, 0, BUFSZ);
        int sentmsgLength = 0;
        // Leitura e envio da mensagem pro servidor
        scanf("%[^\n]%*c", msg);
        int cmdType = parseSendCommand(msg);
        switch (cmdType)
        {
        case 1:
            snprintf(msg, 1024, "REQ_REM(0%d)\n", equip.myId);
            sentmsgLength = send(cdata->s, msg, strlen(msg), 0);
            if (sentmsgLength != strlen(msg))
            {
                logexit("send");
            }
            printf("Successful removal\n");
            sendConnection = 0;
            break;
        case 2:
            list();
            break;
        case 3:
            req_inf(msg, cdata->s);
            break;
        default:
            printf("Unknown command\n");
            break;
        }
    }
    pthread_exit(EXIT_SUCCESS);
}

int parseRecvCommand(char *cmd)
{
    char *command = strtok(cmd, "(");
    if (strcmp(command, "OK") == 0)
    {
        return 1;
    }
    else if (strcmp(command, "REQ_REM") == 0)
    {
        return 2;
    }
    else if (strcmp(command, "RES_ADD") == 0)
    {
        return 3;
    }
    else if (strcmp(command, "RES_LIST") == 0)
    {
        return 4;
    }
    else if (strcmp(command, "REQ_INF") == 0)
    {
        return 5;
    }
    else if (strcmp(command, "RES_INF") == 0)
    {
        return 6;
    }
    return -1;
}

void *recv_thread(void *data)
{
    struct client_data *cdata = (struct client_data *)data;
    while (recvConnection)
    {
        char res[BUFSZ];
        char msg[BUFSZ];
        char cmd[BUFSZ];
        memset(res, 0, BUFSZ);
        memset(msg, 0, BUFSZ);
        memset(cmd, 0, BUFSZ);
        // Mensagem recebida do servidor
        int size = recv(cdata->s, res, BUFSZ, 0);
        strcpy(cmd, res);
        int cmdType = parseRecvCommand(cmd);
        switch (cmdType)
        {
        case 1:
            recvConnection = 0;
            break;
        case 2:
            req_rem(res, size);
            break;
        case 3:
            res_add(res, size);
            break;
        case 4:
            res_list(res, size);
            break;
        case 5:
            requested_inf(res, size, cdata->s);
            break;
        case 6:
            res_inf(res, size, cdata->s);
            break;
        }
        if (strcmp(res, "ERROR(01)\n") == 0)
        {
            printf("Equipment not found\n");
        }
        else if (strcmp(res, "ERROR(02)\n") == 0)
        {
            printf("Source equipment not found\n");
        }
        else if (strcmp(res, "ERROR(03)\n") == 0)
        {
            printf("Target equipment not found\n");
        }
        else if (strcmp(res, "ERROR(04)\n") == 0)
        {
            printf("Equipment limit exceeded\n");
            recvConnection = 0;
        }
    }
    pthread_exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        usage(argc, argv);
    }

    struct sockaddr_storage storage;
    if (0 != addrparse(argv[1], argv[2], &storage))
    {
        usage(argc, argv);
    }

    // Inicializar Socket
    int s;
    s = socket(storage.ss_family, SOCK_STREAM, 0);
    if (s == -1)
    {
        logexit("socket");
    }

    // Inicializar Conexao
    struct sockaddr *addr = (struct sockaddr *)(&storage);
    if (0 != connect(s, addr, sizeof(storage)))
    {
        logexit("connect");
    }

    char addrstr[BUFSZ];
    addrtostr(addr, addrstr, BUFSZ);

    fflush(stdin);

    struct client_data *cdata = malloc(sizeof(*cdata));
    if (!cdata)
    {
        logexit("malloc");
    }

    cdata->s = s;

    pthread_create(&tid_send, NULL, send_thread, cdata);
    pthread_create(&tid_recv, NULL, recv_thread, cdata);

    while (sendConnection && recvConnection)
    {
        continue;
    }
    close(s);
    exit(EXIT_SUCCESS);
}
