/*
	Main for handling:
		- Send packets to server
		- Receive packets from server
		- Send packets to node
		- Receive packets from node

	Structure based on: https://github.com/Lora-net/lora_gateway/tree/master/libloragw
	------------------------------------------------------------
	<configure the radios and IF+modems>
	<start the LoRa concentrator>
	loop {
		<fetch packets that were received by the concentrator>
		<process, store and/or forward received packets>
		<send packets through the concentrator>
		}
	<stop the concentrator> 
	------------------------------------------------------------

*/

#include <stdio.h>
#include <stdlib.h>

#include "send_to_srv.h"
#include "recv_from_srv.h"
#include "send_to_node.h"
#include "recv_from_node.h"

// #include "global_variable.h"


int main(){

	// Radio Configuration
	config_radio(int paramenter_1, int parameter_2, int parameter_3);

	// Start Concentrator
	concentrator_start(int paramenter_1, int parameter_2, int parameter_3);

	while(true){
		// Fetch Received Packets
		packet_fetch();

		// Forward Packets To Server
		packet_forward_to_server();

		// Send Packets to Node
		packet_send_to_node();
	
	}
	
	return(0);
}