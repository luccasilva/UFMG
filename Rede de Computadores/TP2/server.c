#include "common.h"

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFSZ 1024
#define MAX_EQUIP 10

struct Equip_s
{
    int ids[MAX_EQUIP];
    int csocks[MAX_EQUIP];
    int count;
} Equip_default = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 0};
typedef struct Equip_s Equip;

Equip server;

char msg[BUFSZ] = "";
char res[BUFSZ] = "";
char cmd[BUFSZ] = "";
char full[BUFSZ] = "";

struct client_data
{
    int csock;
    struct sockaddr_storage storage;
};

void usage(int argc, char **argv)
{
    printf("usage: %s <v4|v6> <server port>\n", argv[0]);
    printf("exemple: %s v4 5151\n", argv[0]);
    exit(EXIT_FAILURE);
}

void closeConnection(int csock)
{
    // Remover csock
    for (int i = 0; i < MAX_EQUIP; ++i)
    {
        if (server.csocks[i] == csock)
        {
            server.csocks[i] = 0;
            break;
        }
    }
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

void sendClientMessage(int csock, char *res)
{
    int msglen = send(csock, res, strlen(res) + 1, 0);
    if (msglen != strlen(res) + 1)
    {
        logexit("send");
    }
}

void broadcast(char *res)
{
    for (int i = 0; i < MAX_EQUIP; ++i)
    {
        if (server.csocks[i] != 0)
        {
            int msglen = send(server.csocks[i], res, strlen(res) + 1, 0);
            if (msglen != strlen(res) + 1)
            {
                logexit("send");
            }
        }
    }
}

void getIdList(char *str)
{
    char source[4] = "";
    for (int i = 0; i < MAX_EQUIP; ++i)
    {
        if (server.ids[i] != 0)
        {
            sprintf(source, "1 ");
            strcat(str, source);
        }
        else
        {
            sprintf(source, "0 ");
            strcat(str, source);
        }
    }
}

int try_req_add(int csock, char *res)
{
    if (server.count >= MAX_EQUIP)
    {
        return -1;
    }
    int newEquipamentId = 0;
    server.count++;
    for (int i = 0; i < MAX_EQUIP; ++i)
    {
        if (server.ids[i] == 0)
        {
            newEquipamentId = i + 1;
            server.ids[i] = 1;
            break;
        }
    }
    return newEquipamentId;
}

int req_add(int csock, char *res)
{
    int newEquipamentId = 0;
    newEquipamentId = try_req_add(csock, res);
    if (newEquipamentId == -1)
    {
        return 0;
    }
    for (int i = 0; i < MAX_EQUIP; ++i)
    {
        if (server.csocks[i] == 0)
        {
            server.csocks[i] = csock;
            break;
        }
    }
    printf("Equipment 0%d added\n", newEquipamentId);

    snprintf(res, 1024, "RES_ADD(0%d)\n", newEquipamentId);
    broadcast(res);

    fflush(stdout);
    usleep(100000);

    char currentEquips[600] = "";
    getIdList(currentEquips);

    snprintf(res, 1024, "RES_LIST(%s)\n", currentEquips);
    sendClientMessage(csock, res);

    return 1;
}

int try_req_rem(int id)
{
    if (server.ids[id] == 0)
    {
        return 0;
    }
    return 1;
}

int req_rem(int csock, int *connection, char *msg, int size)
{
    char arrayId[BUFSZ] = "";
    substring(msg, arrayId, 9, size);
    strtok(arrayId, ")");
    int intId = atoi(arrayId);

    if (!try_req_rem(intId - 1))
    {
        return 0;
    }

    sprintf(res, "OK(01)\n");
    sendClientMessage(csock, res);

    server.ids[intId - 1] = 0;
    server.csocks[intId - 1] = 0;
    server.count--;

    *connection = 0;

    printf("Equipment 0%d removed\n", intId);
    snprintf(res, 1024, "REQ_REM(0%d)\n", intId);
    broadcast(res);
    return 1;
}

int try_req_inf(int csock, int i, int j)
{
    if (server.ids[i - 1] == 0)
    {
        printf("Equipment 0%d not found\n", i);
        sprintf(res, "ERROR(02)\n");
        sendClientMessage(csock, res);
        return 0;
    }
    if (server.ids[j - 1] == 0)
    {
        printf("Equipment 0%d not found\n", j);
        sprintf(res, "ERROR(03)\n");
        sendClientMessage(csock, res);
        return 0;
    }
    return 1;
}

int req_inf(int csock, char *msg, int size)
{
    char id1[BUFSZ] = "";
    substring(msg, id1, 9, size);
    strtok(id1, ",");
    int intId1 = atoi(id1);

    char id2[BUFSZ] = "";
    substring(msg, id2, 12, size);
    strtok(id2, "\n");
    int intId2 = atoi(id2);

    if (intId1 == 0)
    {
        intId1 = 10;
    }

    if (intId2 == 0)
    {
        intId2 = 10;
    }

    if (try_req_inf(csock, intId1, intId2))
    {
        int finalId1 = intId1;
        int finalId2 = intId2;

        if (intId1 == 10)
            finalId1 = 0;

        if (intId2 == 10)
            finalId2 = 0;

        snprintf(msg, 1024, "REQ_INF(0%d, 0%d)\n", finalId1, finalId2);
        sendClientMessage(server.csocks[intId2 - 1], msg);
        return 1;
    }
    return 1;
}

int res_inf(int csock, char *msg, int size)
{
    char id1[BUFSZ] = "";
    substring(msg, id1, 9, size);
    strtok(id1, ",");
    int intId1 = atoi(id1);

    char id2[BUFSZ] = "";
    substring(msg, id2, 12, size);
    strtok(id2, ",");
    int intId2 = atoi(id2);

    char payload[20] = "";
    substring(msg, payload, 17, size);
    strtok(payload, ")");

    int finalId1 = intId1;
    int finalId2 = intId2;

    if (intId1 == 0)
        finalId1 = 10;

    if (intId2 == 0)
        finalId2 = 10;

    if (try_req_inf(csock, finalId2, finalId1))
    {
        snprintf(msg, 1024, "RES_INF(0%d, 0%d, %s)\n", intId1, intId2, payload);
        sendClientMessage(server.csocks[finalId2 - 1], msg);
        return 1;
    }

    return 1;
}

int parseCommand(char *cmd)
{
    char *command = strtok(cmd, "(");
    if (strcmp(command, "REQ_ADD") == 0)
    {
        return 1;
    }
    else if (strcmp(command, "REQ_REM") == 0)
    {
        return 2;
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

// Thread que roda em paralelo
void *client_thread(void *data)
{
    struct client_data *cdata = (struct client_data *)data;
    char msg[BUFSZ];
    char res[BUFSZ];
    memset(res, 0, BUFSZ);

    int connection = 1;

    // Tentativa de conexao
    if (!req_add(cdata->csock, res))
    {
        sprintf(res, "ERROR(04)\n");
        sendClientMessage(cdata->csock, res);
        connection = 0;
    }

    while (connection)
    {
        memset(msg, 0, BUFSZ);
        memset(full, 0, BUFSZ);
        memset(cmd, 0, BUFSZ);

        // Mensagem recebida pelo servidor ( msg )
        int size = recv(cdata->csock, msg, BUFSZ - 1, 0);

        strcpy(cmd, msg);
        strcpy(full, msg);
        int cmdType = parseCommand(cmd);
        // Acao das mensagens recebidas
        switch (cmdType)
        {
        case 2:
            if (!req_rem(cdata->csock, &connection, msg, size))
            {
                sprintf(res, "ERROR(01)\n");
                sendClientMessage(cdata->csock, res);
            }
            break;
        case 5:
            req_inf(cdata->csock, msg, size);
            break;
        case 6:
            res_inf(cdata->csock, msg, size);
            break;
        }
    }
    closeConnection(cdata->csock);
    close(cdata->csock);
    pthread_exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        usage(argc, argv);
    }

    struct sockaddr_storage storage;
    if (0 != server_sockaddr_init(argv[1], argv[2], &storage))
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

    int enable = 1;
    if (0 != setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)))
    {
        logexit("setsockopt");
    }

    // Bind
    struct sockaddr *addr = (struct sockaddr *)(&storage);
    if (0 != bind(s, addr, sizeof(storage)))
    {
        logexit("bind");
    }

    // Listen ( 10 conex pendentes )
    if (0 != listen(s, 10))
    {
        logexit("listen");
    }

    char addrstr[BUFSZ];
    addrtostr(addr, addrstr, BUFSZ);
    printf("bound to %s, waiting connections\n", addrstr);

    while (1)
    {
        memset(msg, 0, BUFSZ);
        memset(res, 0, BUFSZ);
        struct sockaddr_storage cstorage;
        struct sockaddr *caddr = (struct sockaddr *)(&cstorage);
        socklen_t caddrlen = sizeof(cstorage);
        char caddrstr[BUFSZ];
        memset(caddrstr, 0, BUFSZ);

        int csock = accept(s, caddr, &caddrlen);
        if (csock == -1)
        {
            logexit("accept");
        }

        struct client_data *cdata = malloc(sizeof(*cdata));
        if (!cdata)
        {
            logexit("malloc");
        }

        cdata->csock = csock;
        memcpy(&(cdata->storage), &storage, sizeof(storage));

        pthread_t tid;
        pthread_create(&tid, NULL, client_thread, cdata);
    }
    exit(EXIT_SUCCESS);
}