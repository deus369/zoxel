#/bin/bash


# Prompt the user for the keystore password
read -p "Enter keystore password: " keystore_password

# Prompt the user for the alias
read -p "Enter alias: " alias

# keytool -genkey -v -keystore my-keystore.keystore -alias my-alias -keyalg RSA -keysize 2048 -validity 10000

# check if include/flecs directory exists
if [ ! -d "~/.keys" ]; then
  # create include/flecs directory if it does not exist
  mkdir -p ~/.keys
fi

keystore_filename="~/.keys/$alias.keystore"
if [ ! -f $keystore_filename ]; then
    echo "  > generating keystore [$keystore_filename]"
    # Generate the keystore file
    keytool -genkey -v \
            -keystore ~/.keys/$alias.keystore \
            -alias "$alias" \
            -keyalg RSA \
            -keysize 2048 \
            -validity 10000 \
            -storepass "$keystore_password" \
            -keypass "$keystore_password"
else
    echo "  > keystore exists [$keystore_filename]"
fi