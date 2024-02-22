#ifndef NETWORK_MAMAGER_H
#define NETWORK_MAMAGER_H

#include <enet/enet.h>
#include <iostream>
#include <map>
#include <glm/glm.hpp>

class ClientData
{
	private:
	int m_id;
	std::string m_username;
    glm::vec2 pos;

	public:
	ClientData(int id) : m_id(id) {}

	void SetUsername(std::string username){ m_username = username; }
    void SetPos(glm::vec2 pos){this->pos = pos;}

	int GetID(){ return m_id; }
	std::string GetUsername(){ return m_username; }
    glm::vec2 getPos(){return this->pos;}
};

class Client {
    public:
        ENetHost* client;
        ENetAddress address;
        ENetEvent event;
        ENetPeer* peer;
        std::map<int, ClientData*> client_map;
        int CLIENT_ID = 0;
        Client(){}
        Client(int port) {
            if(enet_initialize() != 0)
            {
                fprintf(stderr, "An error occurred while initializing ENet!\n");
            }
            atexit(enet_deinitialize);

            client = enet_host_create(NULL, 1, 1, 0, 0);

            if(client == NULL)
            {
                fprintf(stderr, "An error occurred while trying to create an ENet client host!\n");
            }

            enet_address_set_host(&address, "127.0.0.1");
            address.port = port;

            peer = enet_host_connect(client, &address, 1, 0);
            if(peer == NULL)
            {
                fprintf(stderr, "No available peers for initiating an ENet connection!\n");
            }


            if(enet_host_service(client, &event, 3000) > 0 &&
                event.type == ENET_EVENT_TYPE_CONNECT)
            {
                puts("Connection to 127.0.0.1:7777 succeeded.");

                SendPacket(peer, "2|TestName");
            }
            else
            {
                enet_peer_reset(peer);
                puts("Connection to 127.0.0.1:7777 failed.");
            }
            
        }

        void SendPos(glm::vec2 pos)
        {
            SendPacket(peer, ("1|" + std::to_string((int)round(pos.x)) + " " + std::to_string((int)round(pos.y))).c_str());
        }

        void Update() {
            while(enet_host_service(client, &event, 0) > 0)
            {
                switch(event.type)
                {
                    case ENET_EVENT_TYPE_RECEIVE:
                        ParseData((char *)event.packet->data); // Parse the receiving data.
                        
                        enet_packet_destroy(event.packet);
                        break;
                }
            }
            
        }

        // A simple way to send packets to a peer
        void SendPacket(ENetPeer* peer, const char* data)
        {
            // Create the packet using enet_packet_create and the data we want to send
            // We are using the flag ENET_PACKET_FLAG_RELIABLE that acts a bit like TCP.
            // That is to say, it'll make sure the packet makes it to the destination.
            ENetPacket* packet = enet_packet_create(data, strlen(data) + 1, ENET_PACKET_FLAG_RELIABLE);

            // Finally, send the packet to the peer on channel 0!
            enet_peer_send(peer, 0, packet);
        }

        void ParseData(char* data)
        {
            // Will store the data type (e.g. 1, 2, etc)
            int data_type;
            //1: new Position 1|xPos,yPos
            //2: username
            //3: our ID

            // Will store the id of the client that is sending the data
            int id;

            // Get first two numbers from the data (data_type and id) and but them in their respective variables
            sscanf(data, "%d|%d", &data_type, &id);
             
            // Switch between the different data_types
            switch(data_type)
            {
                case 1: // data is a new Position
                    if (id != CLIENT_ID) {
                        float xPos = 0;
                        float yPos = 0;
                        sscanf(data, "%*d|%*d|%f %f", &xPos, &yPos);

                        client_map[id]->SetPos(glm::vec2(xPos, yPos));
                    }
                    break;
                case 2: // data is a username (new User is being added)
                    if(id != CLIENT_ID)
                    {
                        // Create a new ClientData with username and add it to map at id.
                        char username[80];
                        sscanf(data, "%*d|%*d|%[^|]", &username);

                        client_map[id] = new ClientData(id);
                        client_map[id]->SetUsername(username);
                    }
                    break;
                case 3: // data is our ID.
                    CLIENT_ID = id; // Set our id to the received id.
                    break;
            }
            
        }

        void Disconnect() {
            enet_peer_disconnect(peer, 0);

            while(enet_host_service(client, &event, 3000) > 0)
            {
                switch(event.type)
                {
                    case ENET_EVENT_TYPE_RECEIVE:
                        enet_packet_destroy(event.packet);
                        break;
                    case ENET_EVENT_TYPE_DISCONNECT:
                        puts("Disconnection succeeded.");
                        break;
                }
            }
        }
};

class Server {
    public:
        ENetEvent event;
	    ENetAddress address;
	    ENetHost* server;
        std::map<int, ClientData*> client_map;
        int newPlayerID = 0;
        Server(){}
        Server(int port) {
            if (enet_initialize() != 0)
            {
                std::cout << "Failed to initialize Enet" << std::endl;
            }
            atexit (enet_deinitialize);

            /* Bind the server to the default localhost.     */
            /* A specific host address can be specified by   */
            /* enet_address_set_host (& address, "x.x.x.x"); */
            address.host = ENET_HOST_ANY; // This allows
            /* Bind the server to port 7777. */
            address.port = port;

            server = enet_host_create (&address	/* the address to bind the server host to */,
					32	/* allow up to 32 clients and/or outgoing connections */,
					1	/* allow up to 1 channel to be used, 0. */,
					0	/* assume any amount of incoming bandwidth */,
					0	/* assume any amount of outgoing bandwidth */);

            if (server == NULL)
            {
                printf("An error occurred while trying to create an ENet server host.");
            }

            std::cout << "Server has been created" << std::endl;
        }

        void GetEvents()
        {
            ENetEvent event;
            /* Wait up to 1000 milliseconds for an event. */
            while (enet_host_service (server, & event, 0) > 0)
            {
                switch (event.type)
                {
                    case ENET_EVENT_TYPE_CONNECT:
                    {
                        printf ("A new client connected from %x:%u.\n",
                        event.peer -> address.host,
                        event.peer -> address.port);

                        for(auto const& x : client_map)
                        {
                            char send_data[1024] = {'\0'};
                            sprintf(send_data, "2|%d|%s", x.first, x.second->GetUsername().c_str());
                            BroadcastPacket(server, send_data);
                        }


                        newPlayerID++;
                        client_map[newPlayerID] = new ClientData(newPlayerID);
                        event.peer->data = client_map[newPlayerID];

                        char data_to_send[126] = {'\0'};
                        sprintf(data_to_send, "3|%d", newPlayerID);
                        SendPacket(event.peer, data_to_send);

                        SendPacket(event.peer, "2|0|Server");
                        break;
                    }
                    case ENET_EVENT_TYPE_RECEIVE: 
                    {
                        // printf ("A packet of length %u containing %s was received from %s on channel %u.\n",
                        //     event.packet -> dataLength,
                        //     event.packet -> data,
                        //     event.peer -> data,
                        //     event.channelID);
                            /* Clean up the packet now that we're done using it. */
                            ParseData(server, static_cast<ClientData*>(event.peer->data)->GetID(), (char*)event.packet->data);
					        enet_packet_destroy(event.packet);
                        break;
                    }
                    case ENET_EVENT_TYPE_DISCONNECT: {
                        printf ("%s disconnected.\n", event.peer -> data);
                        /* Reset the peer's client information. */
                        char disconnected_data[126] = {'\0'};
                        sprintf(disconnected_data, "4|%d", static_cast<ClientData*>(event.peer->data)->GetID());
                        BroadcastPacket(server, disconnected_data);

                        event.peer->data = NULL;
                        break;
                    }
                }
            }
        }

        //sends data to all connected peers
        void BroadcastPacket(ENetHost* server, const char* data)
        {
            ENetPacket* packet = enet_packet_create(data, strlen(data) + 1, ENET_PACKET_FLAG_RELIABLE);
            enet_host_broadcast(server, 0, packet);
        }

        //sends data to a specific peer
        void SendPacket(ENetPeer* peer, const char* data)
        {
            ENetPacket* packet = enet_packet_create(data, strlen(data) + 1, ENET_PACKET_FLAG_RELIABLE);
            enet_peer_send(peer, 0, packet);
        }

        void SendPos(glm::vec2 pos)
        {
            BroadcastPacket(server, ("1|0|" + std::to_string((int)round(pos.x)) + " " + std::to_string((int)round(pos.y))).c_str());
        }

        void ParseData(ENetHost* server, int id, char* data)
        {

            int data_type;
            sscanf(data, "%d|", &data_type);

            switch(data_type)
            {
                case 1:
                {
                    float xPos = 0;
                    float yPos = 0;
                    sscanf(data, "%*d|%f %f", &xPos, &yPos);

                    client_map[id]->SetPos(glm::vec2(xPos, yPos));

                    char msg[80];
                    sscanf(data, "%*d|%[^\n]", &msg);

                    char send_data[1024] = {'\0'};
                    sprintf(send_data, "1|%d|%s", id, msg);
                    BroadcastPacket(server, send_data);
                    break;
                }
                case 2:
                {
                    char username[80];
                    sscanf(data, "2|%[^\n]", &username);

                    char send_data[1024] = {'\0'};
                    sprintf(send_data, "2|%d|%s", id, username);

                    BroadcastPacket(server, send_data);
                    client_map[id]->SetUsername(username);

                    break;
                }
            }
        }
};

class NetworkManager {
    public:
        bool isServer = false;
        Server server;
        Client client;
        NetworkManager(bool isServer)
        {
            this->isServer = isServer;
            if (isServer)
            {
                this->server = Server(7777);
            } else {
                this->client = Client(7777);
            }
            
        }

        void Update() {
            if (isServer)
            {
                server.GetEvents();
            } else {
                client.Update();
            }
        }

        void Disconnect() {
            if (!isServer)
            {
                client.Disconnect();
            }
            
        }

        void SendPos(glm::vec2 pos)
        {
            if (isServer)
            {
                server.SendPos(pos);
            } else {
                client.SendPos(pos);
            }
            
        }

        std::map<int, ClientData*> GetPlayers() {
            if (isServer) {
                return server.client_map;
            } else {
                return client.client_map;
            }
        }
};



#endif