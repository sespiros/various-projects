#!/bin/bash

# Simple script that does the following:
# -- establishes a connection through the vpn channel of upatras
# -- creates a gateway at address 192.168.0.1 on interface eth0
# -- enables ip_forwarding
# -- forwards traffic of local network 192.168.0.0 through the vpn
#

# Command to set the color to SUCCESS (Green)
SETCOLOR_SUCCESS="echo -en \\033[1;32m"
# Command to set the color back to normal
SETCOLOR_NORMAL="echo -en \\033[0;39m"
 
# Function to print the SUCCESS status
echo_success() {
  echo -n "["
  $SETCOLOR_SUCCESS
  echo -n $"DONE"
  $SETCOLOR_NORMAL
  echo -n "]"
  echo -ne "\r"
  echo
  return 0
}

ip link set up dev enp5s0 
ip addr add 192.168.0.1/24 dev enp5s0 
echo -n "::Local gateway up..."
echo_success

sysctl net.ipv4.ip_forward=1
echo -n "::IP forwarding..."
echo_success

iptables -t nat -A POSTROUTING -o tun0 -j MASQUERADE
#iptables --append FORWARD --in-interface enp5s0 -j ACCEPT
iptables-save > /etc/iptables/iptables.rules
systemctl start iptables
echo -n "::IPtables configuration..."
echo_success

