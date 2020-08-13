# NWP_myteams_2019 - Epitech Project (myteams)
![C/C++ CI](https://github.com/Emilien-Delevoye/NWP_myteams_2019/workflows/C/C++%20CI/badge.svg?branch=dev)

The goal of this project is to create a chat server and a CLI client.

## The server :

./myteams_server [port]

    port: is the port number on which the server socket listens.

## The client :

./myteams_cli [ip] [port]

    ip:     is the server ip address on which the server socket listen
    port:   is the port number on which the server socket listens

### Client commands :

/login "username": set the username used by client

/logout: disconnect the client from the server

/users: get the list of all usrs that exist on the domain

/user ["user_uuid"]: get informations about a user

/send [“user_uuid”] [“message_body”]: send a message to a user

/messages [“user_uuid”]: list all messages exchange with an user

/subscribe [“team_uuid”]: subscribe to the event of a team and its sub directories (enable reception of all events from a team)

/subscribed ?[“team_uuid”]: list all subscribed teams or list all users subscribed to a team

/unsubscribe [“team_uuid”]: unsubscribe from a team

/use ?[“team_uuid”] ?[“channel_uuid”] ?[“thread_uuid”]: use specify a context team/channel/thread

/create: based on what is being used create the sub resource

/list: based on what is being used list all the sub resources

/info: based on what is being used list the current

## Protocol

The clients must send the commands to the server with these rules :

    - The command must be send in a char [2048] describe by the BF_S macro in server.h and client.h
    
    - The name of the command must be splited by the '|' character (example : /create "Team 1" "Description" will be send as following /create|Team 1|Description)

    - It's necessary to write 2048 bytes on the socket because the server is waiting for exactly 2048 bytes


The server will send a structure to the client when an event or a command need to be display :

    - The structure is the following, this structure is located in server.h and client.h (struct packet_server_s) :
        
        struct packet_server_s {
        
            unsigned short command;
            
            char team_id[37];
            
            char channel_id[37];
            
            char thread_id[37];
            
            char user_id[37];
            
            char name[33];
            
            char description[256];
            
            char body[513];
            
            int user_status;
            
            time_t time_stamp;
            
            unsigned char broadcast;
            
        }
        
        command -> The number of the function which will be call by the client (the number is the order in the lib_myteams_client.h file).
        
        team_id -> The uuid of the team concerned by the command
        
        channel_id -> The uuid of the channel concerned by the command
        
        thread_id -> The uuid of the thread concerned by the command
        
        user_id -> The uuid of the user concerned by the command
        
        name -> The name of the user/team/channel/thread concerned by the command
        
        description -> The description of the team/channel/thread concerned by the command
        
        body -> The body of the message or the comment concerned by the command
        
        user_status -> 1 if the user is logged, 0 if the user is not logged
        
        time_stamp -> time_t value of the message or the comment concerned by the command
        
        broadcast -> 0 if the client doesn't need to apply change, 1 if the client needs to apply changes on its configuration
        
    - The structure needs to be packed and with exactly the same variables at the same place, if not the client will not accept it
    
    - The structure needs to be initialised with 0.

Project by Emilien Delevoye (emilien.delevoye@epitech.eu) and Cyprien Ricque (cyprien.ricque@epitech.eu)

