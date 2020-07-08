#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/types.h>
#include <arpa/inet.h> 
#include <netinet/in.h>
#include<errno.h> 

// refs:
// https://stackoverflow.com/questions/16156326/so-sndbuf-and-so-rcvbuf-on-linux-sockets
// http://man7.org/linux/man-pages/man7/socket.7.html
// (SO_RCVBUF corresponds to buffer size in bytes)
// https://www.cyberciti.biz/faq/linux-tcp-tuning/
// https://www.geeksforgeeks.org/udp-server-client-implementation-c/
// https://www.geeksforgeeks.org/socket-programming-cc/
// https://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html

// NOTES:
// BUFF_SIZE from reference program

// unclear TODOs:
// increase receive buffer size to >= 8MB; check if this is done in the windows program
// receive only from REMOTE_ADDR

// TODO:
// flags: they 0, we use MSG_WAITALL (642048, or 10011100110000000000)
// time it as sanity check
// maybe use memory mapping to write directly to disk, or write to cache, and batch write to file

#define BUFF_SIZE 4096
// #define REMOTE_ADDR "192.168.1.100"
#define REMOTE_ADDR "192.168.1.126"
#define REMOTE_ADDR_PREFIX "192.168.1."
// const int PORT = 3008; // 10001;
const int PORT = 2003; // 10001;
#define N_SAMPLES_PER_PACKET 22
#define SR 500000.0
// #define READ_FRAME "23530000000007D0" // 2000帧数据
// #define READ_FRAME "2353000000000FA0" // 4000帧数据
#define READ_FRAME "#S\x00\x00\x00\x00\x0f\xa0" // 4000帧数据
#define SA struct sockaddr 
const double DURATION_PER_PACKET = N_SAMPLES_PER_PACKET / SR;
#define SAVE_PATH "./save_data/"



unsigned int get_rcv_buff(int fd) {
    unsigned int rcvBufferSize;
    int sockOptSize = sizeof(rcvBufferSize);
    getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &rcvBufferSize, &sockOptSize);
    return rcvBufferSize;
}

void set_rcv_buff(int fd, unsigned int size) {
    setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));
}

char* GetTime()
{
    time_t timep;
    struct tm *p;

    char* res;
    time (&timep);
    p=gmtime(&timep);
    printf("%d\n",p->tm_sec);
    printf("%d\n",p->tm_min);
    printf("%d\n",8+p->tm_hour);
    printf("%d\n",p->tm_mday);
    printf("%d\n",1+p->tm_mon);
    printf("%d\n",1900+p->tm_year);
    printf("%d\n",p->tm_yday);

    sprintf(res, "%d-%d-%d", 1900+p->tm_year, p->tm_mon, p->tm_mday);
    return res;
}


char * get_device_ip(char * dev)
{
   static char str[80];
   strcpy (str, REMOTE_ADDR_PREFIX);
   strcat (str, dev);
   return str;
}

char* get_file_save_folder(char device_id, char folder_name){

}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        perror("Usage: ./<program> <duration in second> <filename>\n");
        exit(EXIT_FAILURE); 
    }
    double duration = atof(argv[1]);
    unsigned int n_packets = ceil(duration / DURATION_PER_PACKET);
    printf("collecting %d packets\n", n_packets);
    printf("MSG_WAITALL is %d\n", MSG_WAITALL);
    char* output_path = argv[2];

    char device_id[10];
    char* device_ip;

    strcpy(device_id, argv[1]);
    device_ip = get_device_ip(device_id);
    char* folder_name = GetTime("Day");

    printf("folder_name=%s\n", folder_name);
    printf("device_ip=%s\n", device_ip);
    
    char buffer[BUFF_SIZE];
    // printf("%lu\n", sizeof(buffer));
    
    int sockfd, connfd; 
    struct sockaddr_in servaddr, cli; 
    // // socket create and varification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
  
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr(REMOTE_ADDR); 
    servaddr.sin_port = htons(PORT); 
  
    // connect the client socket to server socket 
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    else
        printf("connected to the server..\n");
  
    // // function for chat 
    // // func(sockfd); 
    long total_size = BUFF_SIZE * 4000;
    long read_size = 0;


    // int len, n;
    FILE* fout = fopen(output_path, "wb");
    clock_t start, end;
    start = clock();

    int hex_i;
    char hex_str[4];
    sscanf(READ_FRAME, "%x", &hex_i);
    sprintf(hex_str, "%d", hex_i);

    int i = send(sockfd, (char *)READ_FRAME, sizeof(READ_FRAME) - 1, 0);
    if (i < 1)
    {
        printf("send failed...\n"); 
        exit(0);
    }

    while(1){
        // bzero(buff, sizeof(buff)); 
        printf("read data\n");
        read(sockfd, (char *)buffer, BUFF_SIZE);
        printf("read finish\n");
        read_size += sizeof(buffer);

        fwrite(buffer, sizeof(buffer), 1, fout);

        if(read_size >= total_size){
            break;
        }

    }

    // int len, n;
    // FILE* fout = fopen(output_path, "wb");
    // clock_t start, end;
    // start = clock();


    // for (unsigned int i = 0; i < n_packets; i++) {
    //     //n = recvfrom(fd, (char *)buffer, BUFF_SIZE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
    //     printf("read n_packets: %d\n", i);
    //     n = recvfrom(fd, (char *)buffer, BUFF_SIZE, 0, ( struct sockaddr *) &servaddr, &len); 
    //     printf("read n: %d\n", n);

    //     if (n == PACKET_SIZE) {
    //         fwrite(buffer, PACKET_SIZE, 1, fout);
    //     } else {
    //         perror("wrong packet size\n");
    //         printf("%d\n", n);
    //         exit(EXIT_FAILURE); 
    //     }
    // }
    end = clock();
    double elapsed_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Elapsed time: %fs", elapsed_time);
    fclose(fout);
    // close the socket 

    close(sockfd); 

}
