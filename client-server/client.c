
/* credit @Daniel Scocco */

/****************** CLIENT CODE ****************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int main(){
    int clientSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    char hello[1024];
    scanf ("%[^\n]%*c", hello);


    /*---- Create the socket. The three arguments are: ----*/
    /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);

    /*---- Configure settings of the server address struct ----*/
    /* Address family = Internet */
    serverAddr.sin_family = AF_INET;
    /* Set port number, using htons function to use proper byte order */
    serverAddr.sin_port = htons(5432);
    /* Set IP address to localhost */
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    /* Set all bits of the padding field to 0 */
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    /*---- Connect the socket to the server using the address struct ----*/
    addr_size = sizeof serverAddr;
    connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

    send(clientSocket , hello , strlen(hello) , 0 );

    printf("Message sent\n");

    /*---- Read the message from the server into the buffer ----*/
    recv(clientSocket, buffer, 1024, 0);

    /*---- Print the received message ----*/

    char html_code[8] = "\n<html>";
    char slice[8];
    for (int i = 0; (buffer[i]) && (i < 7); i++)
        slice[i] = buffer[i];
    slice[7] = '\0';
    if (strcmp(html_code, slice) != 0)
        printf("Data received: '%s'\n", buffer);
    else
    {
        FILE *html = fopen("/tmp/client_temp.html", "wb");
        fputs(buffer, html);
        printf("HTML received\n");
        popen("xdg-open /tmp/client_temp.html", "r");
        popen("sleep 5 && rm /tmp/client_temp.html", "r");
    }

    return 0;
}
