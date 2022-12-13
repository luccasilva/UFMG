#include "common.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFSZ 1024
#define MAX_RACKS 4

struct Rack_s {
    int sw[4];
    int count;
} Rack_default = {{0,0,0,0},0};
typedef struct Rack_s Rack;

Rack server[MAX_RACKS];

void usage(int argc, char **argv) {
    printf("usage: %s <v4|v6> <server port>\n", argv[0]);
    printf("exemple: %s v4 5151\n", argv[0]);
    exit(EXIT_FAILURE);
}

void substring(char s[], char sub[], int p, int l) {
   int c = 0;
   while (c < l) {
      sub[c] = s[p+c-1];
      c++;
   }
   sub[c] = '\0';
}

void sendClientMessage(int csock, char *res){
    int msglen = send(csock, res, strlen(res) + 1, 0);
    if (msglen != strlen(res) + 1) {
        logexit("send");
    }
}

int validateInstallCmd(char cmd[BUFSZ], int size, int *rack, int *s1, int *s2, int *s3) {
    char sw[BUFSZ] = "";
    char hk[BUFSZ] = "";

    substring(cmd, sw, 8, size);
    substring(cmd, hk, size-4, size);
    char *switches = strtok(sw, "i");

    if(strlen(switches)%3 != 0){
        return 1;
    }

    int sws[3] = {0,0,0};
    int control = strlen(switches)/3;

    if(control > 3){
        return 3;
    }

    for (int i = 0; i < control; ++i){
        char c1 = switches[i*3];
        char c2 = switches[(i*3)+1];
        char c3 = switches[(i*3)+2];

        if( c1 != '0' || c3 != ' '){
            return 1;
        }
        if( c2 != '1' &&
            c2 != '2' &&
            c2 != '3' &&
            c2 != '4'){
            return 1;
        }
        else{
            if(c2 == '1'){
                sws[i] = 1;
            }
            if(c2 == '2'){
                sws[i] = 2;
            }
            if(c2 == '3'){
                sws[i] = 3;
            }
            if(c2 == '4'){
                sws[i] = 4;
            }
        }
    }

    *s1 = sws[0];
    *s2 = sws[1];
    *s3 = sws[2];

    if(
        hk[0] != 'i' ||
        hk[1] != 'n' ||
        hk[2] != ' ' ||
        hk[3] != '0' ||
        hk[5] != '\0'
        ){
        return 2;
    }
    
    char readRack = hk[4];
    if( readRack != '1' &&
        readRack != '2' &&
        readRack != '3' &&
        readRack != '4'
        ){
        return 2;
    }
    else{
        if(readRack == '1'){
            *rack = 1;
        }
        if(readRack == '2'){
            *rack = 2;
        }
        if(readRack == '3'){
            *rack = 3;
        }
        if(readRack == '4'){
            *rack = 4;
        }
    }

    return 0;
}

int checkSwInstalled(int rack, int sw){
    if(server[rack-1].sw[sw-1] == 1){
        return 1;
    }
    return 0;
}

int tryInstall(int rack, int s1, int s2, int s3, int csock, char *res) {
    int thisRack = rack;
    int thisSw;
    int count = 0;

    if(s1 != 0){
        count = count + 1;
    }

    if(s2 != 0){
        count = count + 1;
    }

    if(s3 != 0){
        count = count + 1;
    }

    if(count + server[thisRack-1].count > 3){
        return 1;
    }

    if(s1 != 0){
        thisSw = s1;
        if(checkSwInstalled(thisRack,thisSw)){
            snprintf(res, 1024, "error switch 0%d already installed in 0%d\n", thisSw, thisRack);
            sendClientMessage(csock, res);
            return -1;
        }
    }
    if(s2 != 0){
        thisSw = s2;
        if(checkSwInstalled(thisRack,thisSw)){
            snprintf(res, 1024, "error switch 0%d already installed in 0%d\n", thisSw, thisRack);
            sendClientMessage(csock, res);
            return -1;
        }
    }
    if(s3 != 0){
        thisSw = s3;
        if(checkSwInstalled(thisRack,thisSw)){
            snprintf(res, 1024, "error switch 0%d already installed in 0%d\n", thisSw, thisRack);
            sendClientMessage(csock, res);
            return -1;
        }
    }
    return 0;
}

void installSwitches(int rack, int s1, int s2, int s3, int csock, char *res) {
    int thisRack = rack-1;
    int thisSw;
    char destination[20] = "";
    char source[4] = "";

    if(s1 != 0){
        thisSw = s1-1;
        server[thisRack].sw[thisSw] = 1;
        server[thisRack].count += 1;
        if(s1 == 1){
            strncpy(source, "01 ", 4);
        }
        if(s1 == 2){
            strncpy(source, "02 ", 4);
        }
        if(s1 == 3){
            strncpy(source, "03 ", 4);
        }
        if(s1 == 4){
            strncpy(source, "04 ", 4);
        }
        strcat(destination,source);
    }
    if(s2 != 0){
        thisSw = s2-1;
        server[thisRack].sw[thisSw] = 1;
        server[thisRack].count += 1;
        if(s2 == 1){
            strncpy(source, "01 ", 4);
        }
        if(s2 == 2){
            strncpy(source, "02 ", 4);
        }
        if(s2 == 3){
            strncpy(source, "03 ", 4);
        }
        if(s2 == 4){
            strncpy(source, "04 ", 4);
        }
        strcat(destination,source);
    }
    if(s3 != 0){
        thisSw = s3-1;
        server[thisRack].sw[thisSw] = 1;
        server[thisRack].count += 1;
        if(s3 == 1){
            strncpy(source, "01 ", 4);
        }
        if(s3 == 2){
            strncpy(source, "02 ", 4);
        }
        if(s3 == 3){
            strncpy(source, "03 ", 4);
        }
        if(s3 == 4){
            strncpy(source, "04 ", 4);
        }
        strcat(destination,source);
    }
    snprintf(res, 1024, "switch %sinstalled\n", destination);
    sendClientMessage(csock, res);
}

void install(char cmd[BUFSZ], int size, int csock, char *res) {
    int rack = 0;
    int s1 = 0, s2 = 0, s3 = 0;
    int error = validateInstallCmd(cmd,size,&rack,&s1,&s2,&s3);

    if(error == 1){
        sprintf(res, "error switch type unknown\n");
        sendClientMessage(csock, res);
    }
    else if(error == 2){
        sprintf(res, "error rack doesn't exist\n");
        sendClientMessage(csock, res);
    }
    else if(error == 3){
        sprintf(res, "error rack limit exceeded\n");
        sendClientMessage(csock, res);
    }
    else{
        error = tryInstall(rack,s1,s2,s3,csock,res);
        if(error == 1){
            sprintf(res, "error rack limit exceeded\n");
            sendClientMessage(csock, res);
        }
        if(error == 0){
            installSwitches(rack,s1,s2,s3,csock,res);
        }
    }
}

int validateUninstallCmd(char cmd[BUFSZ], int size, int *rack, int *s1) {
    char sw[BUFSZ] = "";
    char hk[BUFSZ] = "";

    substring(cmd, sw, 7, size);
    substring(cmd, hk, size-4, size);
    char *switches = strtok(sw, "i");
    if(strlen(switches) != 3){
        return 1;
    }

    char c1 = switches[0];
    char c2 = switches[1];
    char c3 = switches[2];

    if( c1 != '0' || c3 != ' '){
        return 1;
    }

    if( c2 != '1' &&
        c2 != '2' &&
        c2 != '3' &&
        c2 != '4'){
        return 1;
    }

    else{
        if(c2 == '1'){
            *s1 = 1;
        }
        if(c2 == '2'){
            *s1 = 2;
        }
        if(c2 == '3'){
            *s1 = 3;
        }
        if(c2 == '4'){
            *s1 = 4;
        }
    }

     if(
        hk[0] != 'i' ||
        hk[1] != 'n' ||
        hk[2] != ' ' ||
        hk[3] != '0' ||
        hk[5] != '\0'
        ){
        return 2;
    }
    
    char readRack = hk[4];
    if( readRack != '1' &&
        readRack != '2' &&
        readRack != '3' &&
        readRack != '4'
        ){
        return 2;
    }
    else{
        if(readRack == '1'){
            *rack = 1;
        }
        if(readRack == '2'){
            *rack = 2;
        }
        if(readRack == '3'){
            *rack = 3;
        }
        if(readRack == '4'){
            *rack = 4;
        }
    }

    return 0;
}

int tryUninstall(int rack, int s1, int csock, char *res) {
    if(s1 != 0){
        if(!checkSwInstalled(rack,s1)){
            sprintf(res, "error switch doesn’t exist\n");
            sendClientMessage(csock, res);
            return -1;
        }
    }
    return 0;
}

void uninstallSwitches(int rack, int s1, int csock, char *res) {
    int thisRack = rack-1;
    int thisSw = s1-1;
    char destinationSw[20] = "";
    char sourceSw[4] = "";
    char destinationHk[20] = "";
    char sourceHk[4] = "";

    if(s1 != 0){
        server[thisRack].sw[thisSw] = 0;
        server[thisRack].count -= 1;
        if(s1 == 1){
            strncpy(sourceSw, "01", 4);
        }
        if(s1 == 2){
            strncpy(sourceSw, "02", 4);
        }
        if(s1 == 3){
            strncpy(sourceSw, "03", 4);
        }
        if(s1 == 4){
            strncpy(sourceSw, "04", 4);
        }
        strcat(destinationSw,sourceSw);
    }

    if(rack != 0){
        if(rack == 1){
            strncpy(sourceHk, "01", 4);
        }
        if(rack == 2){
            strncpy(sourceHk, "02", 4);
        }
        if(rack == 3){
            strncpy(sourceHk, "03", 4);
        }
        if(rack == 4){
            strncpy(sourceHk, "04", 4);
        }
        strcat(destinationHk,sourceHk);
    }
    snprintf(res, 1024, "switch %s removed from %s\n", destinationSw,destinationHk);
    sendClientMessage(csock, res);
}

void uninstall(char cmd[BUFSZ], int size, int csock, char *res) {
    int rack = 0;
    int s1 = 0;
    int error = validateUninstallCmd(cmd,size,&rack,&s1);

    if(error == 1){
        sprintf(res, "error switch type unknown\n");
        sendClientMessage(csock, res);
    }
    else if(error == 2){
        sprintf(res, "error rack doesn't exist\n");
        sendClientMessage(csock, res);
    }
    else{
        error = tryUninstall(rack,s1,csock,res);
        if(error == 0){
            uninstallSwitches(rack,s1,csock,res);
        }
    }
}

int validateReadSwitchCmd(char cmd[BUFSZ], int size, int *rack, int *s1, int *s2) {
    char sw[BUFSZ] = "";
    char hk[BUFSZ] = "";

    substring(cmd, sw, 5, size);
    substring(cmd, hk, size-4, size);
    char *switches = strtok(sw, "i");
    if(strlen(switches) > 6){
        return 1;
    }

    int sws[2] = {0,0};
    int control = strlen(switches)/3;

    if(control > 2){
        return 3;
    }

    for (int i = 0; i < control; ++i){
        char c1 = switches[i*3];
        char c2 = switches[(i*3)+1];
        char c3 = switches[(i*3)+2];

        if( c1 != '0' || c3 != ' '){
            return 1;
        }
        if( c2 != '1' &&
            c2 != '2' &&
            c2 != '3' &&
            c2 != '4'){
            return 1;
        }
        else{
            if(c2 == '1'){
                sws[i] = 1;
            }
            if(c2 == '2'){
                sws[i] = 2;
            }
            if(c2 == '3'){
                sws[i] = 3;
            }
            if(c2 == '4'){
                sws[i] = 4;
            }
        }
    }
    *s1 = sws[0];
    *s2 = sws[1];

    if(
        hk[0] != 'i' ||
        hk[1] != 'n' ||
        hk[2] != ' ' ||
        hk[3] != '0' ||
        hk[5] != '\0'
        ){
        return 2;
    }
    
    char readRack = hk[4];
    if( readRack != '1' &&
        readRack != '2' &&
        readRack != '3' &&
        readRack != '4'
        ){
        return 2;
    }
    else{
        if(readRack == '1'){
            *rack = 1;
        }
        if(readRack == '2'){
            *rack = 2;
        }
        if(readRack == '3'){
            *rack = 3;
        }
        if(readRack == '4'){
            *rack = 4;
        }
    }
    return 0;
}

int tryReadSwitch(int rack, int s1, int s2, int csock, char *res) {
    if(s1 != 0){
        if(!checkSwInstalled(rack,s1)){
            sprintf(res, "error switch doesn’t exist\n");
            sendClientMessage(csock, res);
            return -1;
        }
    }
    if(s2 != 0){
        if(!checkSwInstalled(rack,s2)){
            sprintf(res, "error switch doesn’t exist\n");
            sendClientMessage(csock, res);
            return -1;
        }
    }
    return 0;
}

void readSwitches(int rack, int s1, int s2, int csock, char *res) {
    int random_number = rand() % 100 + 1;
    int random_number2 = rand() % 100 + 1;

    if(s1 != 0 && s2 != 0){
        snprintf(res, 1024, "%d Kbs %d Kbs\n", random_number, random_number2);
        sendClientMessage(csock, res);
    }
    else if(s1 != 0 && s2 == 0){
        snprintf(res, 1024, "%d Kbs\n", random_number);
        sendClientMessage(csock, res);
    }
}

void readSwitch(char cmd[BUFSZ], int size, int csock, char *res) {
    int rack = 0;
    int s1 = 0;
    int s2 = 0;
    int error = validateReadSwitchCmd(cmd,size,&rack,&s1,&s2);

    if(error == 1){
        sprintf(res, "error switch type unknown\n");
        sendClientMessage(csock, res);
    }
    else if(error == 2){
        sprintf(res, "error rack doesn't exist\n");
        sendClientMessage(csock, res);
    }
    else{
        error = tryReadSwitch(rack,s1,s2,csock,res);
        if(error == 0){
            readSwitches(rack,s1,s2,csock,res);
        }
    }
}

int validateListCmd(char cmd[BUFSZ], int size, int *rack) {
    char hk[BUFSZ] = "";

    substring(cmd, hk, 4, size);

    if(
        hk[0] != '0' ||
        hk[2] != '\0'
        ){
        return 1;
    }
    
    char readRack = hk[1];
    if( readRack != '1' &&
        readRack != '2' &&
        readRack != '3' &&
        readRack != '4'
        ){
        return 1;
    }
    else{
        if(readRack == '1'){
            *rack = 1;
        }
        if(readRack == '2'){
            *rack = 2;
        }
        if(readRack == '3'){
            *rack = 3;
        }
        if(readRack == '4'){
            *rack = 4;
        }
    }
    return 0;
}

int tryListRack(int rack, int csock, char *res) {
    if(rack != 0){
        int thisRack = rack-1;
        if(server[thisRack].count == 0){
            sprintf(res, "empty rack\n");
            sendClientMessage(csock, res);
            return -1;
        }
    }
    return 0;
}

void listRack(int rack, int csock, char *res) {
    int thisRack = rack-1;
    char destination[20] = "";
    char source[4] = "";
    if(server[thisRack].sw[0] == 1){
        strncpy(source, "01 ", 4);
        strcat(destination,source);
    }
    if(server[thisRack].sw[1] == 1){
        strncpy(source, "02 ", 4);
        strcat(destination,source);
    }
    if(server[thisRack].sw[2] == 1){
        strncpy(source, "03 ", 4);
        strcat(destination,source);
    }
    if(server[thisRack].sw[3] == 1){
        strncpy(source, "04 ", 4);
        strcat(destination,source);
    }

    snprintf(res, 1024, "%s\n", destination);
    sendClientMessage(csock, res);
}

void list(char cmd[BUFSZ], int size, int csock, char *res) {
    int rack = 0;
    int error = validateListCmd(cmd,size,&rack);

    if(error == 1){
        sprintf(res, "error rack doesn't exist\n");
        sendClientMessage(csock, res);
    }
    else{
        error = tryListRack(rack,csock,res);
        if(error == 0){
            listRack(rack,csock,res);
        }
    }
}

void exitClient(int csock, char *res) {
    sprintf(res, "exit");
    int msglen = send(csock, res, strlen(res) + 1, 0);
    if (msglen != strlen(res) + 1) {
        logexit("send");
    }
    close(csock);
}

int parseCommand(char *cmd){
    char *command = strtok(cmd, " ");
    if (strcmp(command, "add") == 0){
        return 1;
    }
    else if (strcmp(command, "rm") == 0){
        return 2;
    }
    else if (strcmp(command, "get") == 0){
        return 3;
    }
    else if (strcmp(command, "ls") == 0){
        return 4;
    }
    else if (strcmp(command, "exit") == 0){
        return 5;
    }
    return -1;
}

int main(int argc, char **argv) {
    if (argc < 3){
        usage(argc, argv);
    }

    struct sockaddr_storage storage;
    if( 0 != server_sockaddr_init(argv[1], argv[2], &storage) ){
        usage(argc, argv);
    }

    // Inicializar Socket
    int s;
    s = socket(storage.ss_family, SOCK_STREAM, 0);
    if( s == -1 ){
        logexit("socket");
    }

    int enable = 1;
    if( 0 != setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int))){
        logexit("setsockopt");
    }

    //Bind
    struct sockaddr *addr = (struct sockaddr *)(&storage);
    if( 0 != bind(s, addr, sizeof(storage)) ){
        logexit("bind");
    }

    //Listen ( 10 conex pendentes )
    if( 0 != listen(s, 10) ){
        logexit("listen");
    }

    char addrstr[BUFSZ];
    addrtostr(addr, addrstr, BUFSZ);
    printf("bound to %s, waiting connections\n", addrstr);

    struct sockaddr_storage cstorage;
    struct sockaddr *caddr = (struct sockaddr *)(&cstorage);
    socklen_t caddrlen = sizeof(cstorage);
    char caddrstr[BUFSZ];
    char msg[BUFSZ] = "";
    char res[BUFSZ] = "";
    char cmd[BUFSZ] = "";
    char full[BUFSZ] = "";
    
    while (1) {
        memset(caddrstr, 0, BUFSZ);

        //s -> socket do servidor
        //csock -> socket que comunica com o cliente
        int csock = accept(s, caddr, &caddrlen);
        if (csock == -1) {
            logexit("accept");
        }

        int connection = 1;

        //Mensagem de conexao estabelecida
        addrtostr(caddr, caddrstr, BUFSZ);
        printf("[log] connection from %s\n", caddrstr);

        while (connection) {
            memset(msg, 0, BUFSZ);
            memset(res, 0, BUFSZ);
            memset(full, 0, BUFSZ);
            memset(cmd, 0, BUFSZ);

            //Mensagem recebida pelo servidor ( msg )
            int size = recv(csock, msg, BUFSZ-1, 0);

            strcpy(cmd, msg);
            strcpy(full, msg);
            int cmdType = parseCommand(cmd);
            char *command = strtok(full, "0");
            switch (cmdType){
                case 1:;
                    if (strcmp(command, "add sw ") == 0){
                        install(msg, size, csock, res);
                    }
                    else{
                        exitClient(csock, res);
                        connection = 0;
                    }
                    break;
                case 2:;
                    if (strcmp(command, "rm sw ") == 0){
                        uninstall(msg, size, csock, res);
                    }
                    else{
                        exitClient(csock, res);
                        connection = 0;
                    }
                    break;
                case 3:;
                    if (strcmp(command, "get ") == 0){
                        readSwitch(msg, size, csock, res);
                    }
                    else{
                        exitClient(csock, res);
                        connection = 0;
                    }
                    break;
                case 4:;
                    if (strcmp(command, "ls ") == 0){
                        list(msg, size, csock, res);
                    }
                    else{
                        exitClient(csock, res);
                        connection = 0;
                    }
                    break;
                case 5:
                    exitClient(csock, res);
                    connection = 0;
                    break;
                default:
                    exitClient(csock, res);
                    connection = 0;
                    break;
            }
        }
    }
    exit(EXIT_SUCCESS);
}