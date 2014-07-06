Helium Constant Rate Message Test
=================================

This sketch transmits sample messages at a constant rate using the Helium Alpha
modem, bridge and back-end. When a data stream is sent, the Helium Alpha system
eventually hangs. When hung, the Arduino is functioning normally. The modem is
blinking normally. The bridge is blinking normally. However, no data is
received by the Helium-RED application.

The server.py is a elementary TCP server that prints whatever is sent on to TCP
socket. Run the server and then configure a TCP endpoint in Helium-RED.

To check for lost packets, copy the output of the server to a text editor to
count the number of messages received (lines). Subtract the last sequence
number from the first to see how many messages were sent.

The sketch sends a message with a sequence number, the Arduino uptime (millis),
the time at which the message was scheduled to be sent, and a newline (for
convenience). The global `period` variable in the sketch determines the period
between messages.

With 10ms message period, the Alpha system hangs within a minute or two. I set
Helium-RED to forward messages to a TCP socket. Only 30% of messages are
received on the TCP socket. Many messages are out of order. Similar performance
message loss can be observed using a MQTT endpoint instead of a TCP endpoint.

With 100ms message period, the system can run for tens of minutes, but will
eventually crash. 99% of messages are received. The messages are generally
received in the correct order.

When the system is hung, the Arduino is still sending messages. The bridge
LEDs are flashing as if it were receiving the messages. If the Arduino is
restarted, it cannot reconnect to the bridge. The system can be restored to
operation by power-cycling both the bridge and modem.
