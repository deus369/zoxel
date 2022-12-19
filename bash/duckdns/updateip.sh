#!/bin/bash

# seperate token file in .ssh directory for security
# duck_token="token_from_duck_dns"
# get duck_token stored in this file
my_domain="zoxel"
my_ip=$(host myip.opendns.com resolver1.opendns.com | grep "myip.opendns.com has" | awk '{print $4}')
source ~/.ssh/zoxel_duck_token.sh
my_command="https://www.duckdns.org/update?domains=$my_domain&token=$duck_token&ip=$my_ip"

echo "Setting DuckDNS IP4 [$my_domain.duckdns.org]"
echo "  Token [$duck_token]"
echo "  Public IP4 is [$my_ip]"
echo "  Command is [$my_command]"
wget --delete-after $my_command
echo "Setting DuckDNS IP4 has completed."

sleep 30