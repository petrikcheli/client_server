#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main()
{
    int clientSock = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSock < 0){
        std::cerr << "Ошибка создания сокета" << std::endl;
        exit(1);
    }

    struct sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = 8080;

    if (inet_pton(AF_INET, "192.168.31.45",
                  &(serverAddress.sin_addr)) <= 0){
        std::cerr << "Неверный IP адрес" << std::endl;
        exit(1);
    }

    if(connect(clientSock, (struct sockaddr *)&serverAddress,
                sizeof(serverAddress)) < 0){
        std::cerr << "Ошибка соединения с сервером" << std::endl;
        exit(1);
    }

    struct Command{
        int commandType;
    };

    Command command;

    std::cout << "Выберите команду" << std::endl;
    int com = 0;
    std::cin >> com;
    command.commandType = com;

    if (send(clientSock, &command, sizeof(command), 0) < 0){
        std::cerr << "Ошибка при отправке сообщения серверу" << std::endl;
        exit(1);
    }

    // if (recv(clientSock, &command, sizeof(command), 0) < 0)
    // {
    //     std::cerr << "Ошибка при приеме команды от сервера" << std::endl;
    //     exit(1);
    // }

    shutdown(clientSock, 2);

    if (clientSock != -1)
    {
        close(clientSock);
        clientSock = -1;
    }

    return 0;
}
