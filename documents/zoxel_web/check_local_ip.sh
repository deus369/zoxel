
# physical_interface="eth0"
# physical_interface="wlan1"
physical_interface="wlP2p33s0"

# Set the expected IP address in a variable
expected_ip=192.168.0.105

# Get the current local IP address using the ip command
current_ip=$(ip addr show $physical_interface | grep "inet " | awk '{print $2}' | cut -d/ -f1)

echo "Local IP is [$current_ip]"
echo "  Expected Local IP is [$expected_ip]"

# Compare the expected and current IP addresses
if [[ "$current_ip" == "$expected_ip" ]]
then
    # IP addresses match
    echo "  Local IP matches expected value"
else
    # IP addresses do not match
    echo "  Local IP does not match expected value"
    echo "  Make sure to update router port forwarding at [http://192.168.0.1/]."
    sleep 100
fi