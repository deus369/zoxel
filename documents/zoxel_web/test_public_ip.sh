echo "Testing public ip"

# Get the public IP address using the curl command
public_ip=$(curl -s icanhazip.com)

# Set the port to be tested
port=80

echo "Testing public ip [$public_ip:$port]"

# Test the port forwarding by attempting to connect to the public IP and port
nc -vz $public_ip $port

# Check the exit status of the nc command
if [ $? -eq 0 ]
then
    # Port is open and forwarding is working
    echo "  Port forwarding is working"
    sleep 3
else
    # Port is closed or forwarding is not working
    echo "  Port forwarding is not working"
    sleep 16
fi

sleep 6