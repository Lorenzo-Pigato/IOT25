
Authors: 
**Kevin Abate:       10812892**
**Lorenzo Pigato: 10766953** **[Team Leader]** 

---
# Project topic
The project consist on the **analysis** and **sniffing** of the packets captured on the "challenge2.pcap", the analysis have been done through Wireshark and TShark.

# Questions
## CQ1
"How many different Confirmable PUT requests obtained an unsuccessful response from the local CoAP server?"
**Answer**: 22
	The answer is given by filtering before all the **CONfirmbale PUT requests**, and after that checked the **error response** sent from the server. Due the fact that's not possible to do combination of filter in Wireshark, to deal with this problem we used TShark.    Below it's possible to see the filters in TShark  and the consequent result.             
	![[Screenshot from 2025-03-31 10-25-17.png]] ![[CQ1.2.png]] Above it's possible to see the the matching between the MID of the several packets.
## CQ2
"How many CoAP resources in the coap.me public server received the
same number of unique Confirmable and Non Confirmable GET requests?"
	*Assuming a resource receives X different CONFIRMABLE requests and Y different
	NONCONFIRMABLE GET requests, how many resources have X=Y, with X>0?*
**Answer**: 3 [large, secret, validate]
	In order to solve the problem, before all on Wireshark has been done an analysis to find out the **address** of the "coap.me" server![[Screenshot from 2025-03-31 10-32-17.png]] which is possible to see that the coap.me ip address is: 134.102.218.18 .                            After that on TShark has been done  the filters and comparison to find out the result.![[Screenshot from 2025-03-31 10-36-06.png]]
	In the first filter will be returned the **GET NON-confirmable packets**, with an IP destination equals to the coap.me server. The second does the same but with the **CONfirmable packets**. At the end matches the outputs of the two previously obtained files and returns the common rows.
## CQ3
"How many different MQTT clients subscribe to the public broker
HiveMQ using multi-level wildcards?"
**Answer**:  4 [38619- 38641-54449-57863]
      Before all it has been made a filter on Wireshark to find out the **address** of the HiveMQ broker, as is possible to see below.![[Screenshot from 2025-03-31 11-09-05.png]]There are **three IP addresses** used to connect to the broker. After that, MQTT subscribe messages sent to these IPs were analyzed to identify topics that contain the **multi-level wildcard**.![[Screenshot from 2025-03-31 11-14-52.png]]The clients **differ** from each other by the **TCP port**, making it easy to compute the solution at this point.
      It's easy to check the solution on TShark too
      ![[Screenshot from 2025-03-31 11-43-25.png]]
      obtaining as a result the several clients, distinguished by their TCP port   
      ![[Screenshot from 2025-03-31 11-50-29.png]]
## CQ4 
"How many different MQTT clients specify a last Will Message to be
directed to a topic having as first level "university" ?"
**Answer**: 1 [127.0.0.1 - university/department12/room1/temperature]
	To solve this question is possible to use either Wireshark and TShark, will be showed 
	the TShark solution.
	These conditions filters all the MQTT connect file, with the **willflag** on the **CONNACK** flags activated and a **Last Will Topic** that contains the string "university".
	![[Screenshot from 2025-03-31 11-57-04.png]]
	**Note**:  In the first command, the Will Topic is shown for better clarity.
## CQ5
"How many MQTT subscribers receive a last will message derived from a subscription without a wildcard?"
**Answer**: 3 [39551-53557-41789]
	The answer for this question is divided in five parts.
	At the beginning are searched all the **distinct topics** that have a flag set for last will message and clients which set them.![[Screenshot from 2025-03-31 12-17-51.png]]
	output of the filter:
	```38083	university/department12/room1/temperature
	56285	metaverse/room2/floor4
	53485	hospital/facility3/area3
	42665	metaverse/room2/room2
	```
	After that it's used this command that filters the connection reset packets by the TCP source port to determine if any **connection reset** has been sent by a client that has configured a **Last Will Topic** message.![[Screenshot from 2025-03-31 12-25-48 1.png]]
	output of the filter:
	```38083	1883
	```
	Thus are matched the **Last Will Topic** with **failing clients**.
	![[Screenshot from 2025-03-31 12-34-28.png]]
	output of the filter:
	```university/department12/room1/temperature
	```
	Now that we have the topic we can search the **messages** sent by the broker on the single topic found.![[Screenshot from 2025-03-31 12-36-55.png]]
	output of the filter:
	```39551
	53557
	51743
	41789
	```
	With clients IPs in hand we can finally check which of these received the message, subscribed to the topic without wildcards:![[Screenshot from 2025-03-31 12-43-40.png]]
	obtaining as final answer to the question, the clients:
	```39551
	53557
	41789```
## CQ6
"How many MQTT publish messages directed to the public broker Mosquitto are sent with the retain option and use QoS “At most once”? "
**Answer**: 208
	To solve this question is possible to use either Wireshark and TShark, in this case will be showed the Wireshark solution, instead the TShark solution as proof.
	 Before all a filter was applied to find the address of the Mosquitto broker, as shown below![[Screenshot from 2025-03-31 12-50-31.png]]
	 it's possible to notice that the desired IP is: 5.196.78.28.
	Thus is possible to analyze the traffic with QoS equals to zero (at most once), sent by the broker with the retain option activated.![[Screenshot from 2025-03-31 12-56-12.png]]
	Below it's possible to see the proof of the result with TShark.
	![[Screenshot from 2025-03-31 12-47-02.png]]
## QC7
"How many MQTT-SN messages on port 1885 are sent by the clients to a broker in the local machine?"
**Answer**: 0
	Before all we changed on the setting the port of the MQTT-SN on 1885. 
	After the filtering there weren't results, as is shown below.
	![[Screenshot from 2025-03-31 13-02-34.png]]



