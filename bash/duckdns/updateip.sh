#!/bin/bash

# if no file
duck_token_path="$HOME/.ssh/zoxel_duck_token.sh"
if [ ! -f $duck_token_path ]; then
    echo "Duck token path file does not exist [$duck_token_path]"
    echo "  Create a shell file there with duck_token=<token_id_from_duck_dns_dot_org>"
    sleep 10
    exit
else
    echo "Duck token path file exists [$duck_token_path]"
fi

# seperate token file in .ssh directory for security
# duck_token="token_from_duck_dns"
# get duck_token stored in this file
my_domain="zoxel"
my_ip=$(host myip.opendns.com resolver1.opendns.com | grep "myip.opendns.com has" | awk '{print $4}')
source $duck_token_path
my_command="https://www.duckdns.org/update?domains=$my_domain&token=$duck_token&ip=$my_ip"

if [[ $duck_token == "" ]]; then
    echo DuckToken was empty.
    sleep 10
    exit
fi

echo "Setting DuckDNS IP4 [$my_domain.duckdns.org]"
echo "  Token [$duck_token]"
echo "  Public IP4 is [$my_ip]"
echo "  Command is [$my_command]"
wget --delete-after $my_command
echo "Setting DuckDNS IP4 has completed."

sleep 30