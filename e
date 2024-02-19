#include "webserv.hpp"

/*void executeCGIScript(int client_socket, const std::string& scriptPath) {
    // Create a pipe for communication with the CGI script
    int pipe_fd[2];
    if (pipe(pipe_fd) < 0)
        throw PipeFailedException();

    // Fork a new process for the CGI script
    pid_t pid = fork();
    if (pid < 0)
        throw ForkFailedException();

    if (pid == 0) { // Child process (CGI script)
        // Close the write end of the pipe
        close(pipe_fd[1]);

        // Redirect standard input to read from the pipe
        dup2(pipe_fd[0], STDIN_FILENO);

        // Redirect standard output to write to the client socket
        dup2(client_socket, STDOUT_FILENO);

        // Close unnecessary file descriptors
        close(pipe_fd[0]);
        close(client_socket);

        // Execute the CGI script
        execve("./script.cgi", NULL, NULL);

        // If execl fails, print an error
        perror("execl");
        exit(EXIT_FAILURE);
    } else { // Parent process
        // Close the read end of the pipe
        close(pipe_fd[0]);

        // Write the client request to the CGI script
        write(pipe_fd[1], "Client request data", 19);
        close(pipe_fd[1]); // Close the write end to signal the end of input

        // Wait for the CGI script to complete
        waitpid(pid, nullptr, 0);
    }
}/**/


int main()
{
    try
    {
        int server_fd = socket(AF_INET, SOCK_STREAM, 0);
        int client_fd;
        int client_fd2;
        int valread;
        std::string buffer(1024, '\0');
        fd_set ready_sockets;
        fd_set current_sockets;
        if (server_fd < 0)
            throw SocketFailedException();
        struct sockaddr_in address;
        const int PORT = 8080;
        memset((char *)&address, 0, sizeof(address)); 
        address.sin_family = AF_INET; 
        address.sin_addr.s_addr = htonl(INADDR_ANY); 
        address.sin_port = htons(PORT); 
        long len = sizeof(address);
        if (bind(server_fd,(struct sockaddr *)&address,sizeof(address)) < 0)//&addrlen
            throw BindFailedException();
        if (listen(server_fd, 3) < 0) 
            throw ListenFailedException();
        FD_ZERO(&current_sockets);
        FD_SET(server_fd, &current_sockets);
        while (1) 
        {
            ready_sockets = current_sockets;
            if (select(FD_SETSIZE, &ready_sockets, NULL, NULL, NULL) < 0)
                throw SelectFailedException();
            for (int i = 0; i < FD_SETSIZE; i++) 
            {
                if (FD_ISSET(i, &ready_sockets)) 
                {
                    if (i == server_fd) 
                    {
                        if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&len)) < 0) 
                            throw AcceptFailedException();
                        FD_SET(client_fd, &current_sockets);
                    } 
                    else 
                    {
                        valread = read(i, &buffer[0], 1024); // Utilisation de i au lieu de client_fd
                        if (valread < 0)
                            throw ReadFailedException();
                        buffer[0] = 'b';
                        write(0, &buffer[0], 100); // Utilisation de i au lieu de client_fd
                        FD_CLR(i, &current_sockets); // Utilisation de i au lieu de client_fd
                        close(i); // Fermeture du descripteur de fichier après traitement
                    }
                }
            }
        }
    }


        /*while(1)
        {
            ready_sockets = current_sockets;
            if(select(FD_SETSIZE, &ready_sockets, NULL, NULL, NULL) < 0)
                throw SelectFailedException();
            for (int i=0; i < FD_SETSIZE; i++)
            {
                if (FD_ISSET(i, &ready_sockets))
                {
                    if (i == server_fd)
                    {
                        if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&len))<0)
                            throw AcceptFailedException();
                        FD_SET(client_fd, &current_sockets);
                    }
                    else
                    {
                        valread = read(i , &buffer[0], 1024); 
                        if(valread < 0)
                            throw ReadFailedException();
                        write(i, &buffer[0], 100);
                        FD_CLR(i, &current_sockets);
                        close(i);
                    }
                }
            }
            /*valread = read( client_fd , &buffer[0], 1024); 
            if(valread < 0)
                throw ReadFailedException();
            /*if ((client_fd2 = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&len))<0)
                throw AcceptFailedException();
            write(client_fd2, &buffer[0], 6);*/
    catch (std::exception &e) 
    {
        std::cerr << e.what() << std::endl;
    }

}
/*int main()
{
    try
    {
        int server_fd = socket(AF_INET, SOCK_STREAM, 0);
        int client_socket;
        if (server_fd < 0)
            throw SocketFailedException();
        struct sockaddr_in address;
        const int PORT = 8080;
        memset((char *)&address, 0, sizeof(address)); 
        address.sin_family = AF_INET; 
        address.sin_addr.s_addr = htonl(INADDR_ANY); 
        address.sin_port = htons(PORT); 
        long len = sizeof(address);
        if (bind(server_fd,(struct sockaddr *)&address,sizeof(address)) < 0)//&addrlen
            throw BindFailedException();
        if (listen(server_fd, 3) < 0) 
            throw ListenFailedException();
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&len))<0)
            throw AcceptFailedException();
        
        
    }
    catch (std::exception &e) {
    			std::cerr << e.what() << std::endl;
    }
}*/