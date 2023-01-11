#!/bin/bash

# Set the expected IP address in a variable
expected_ip=192.168.0.200

# physical_interface="eth0"
# physical_interface="wlan1"
physical_interface="wlP2p33s0"

# IP addresses do not match
while [ true ]
do
    current_ip=$(ip addr show $physical_interface | grep "inet " | awk '{print $2}' | cut -d/ -f1)
    echo "Required Local IP is [$expected_ip] - Found Local IP is [$current_ip]"
    if [[ "$current_ip" == "$expected_ip" ]]
    then
        # IP addresses match
        echo "      Local IP matches expected value"
        break
    else
        echo "      Local IP does not match expected value"
        echo "          # Update Router Port Forwarding at [http://192.168.0.1/] #"
        sleep 3
    fi
done

echo IP is forwarded for website.
sleep 3