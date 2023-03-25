#!/bin/bash

keystore_alias="zoxel"
# cd build/android-build
# echo "need to sign apk: "

apk_filepath="build/android-build/app/build/outputs/apk/release/app-release-unsigned.apk"
apk_signed_filepath="build/android-build/app/build/outputs/apk/release/zoxel.apk"
keystore_filepath="$HOME/.keys/$keystore_alias.keystore"

echo "  > signing android release build with alias [$keystore_alias]"
echo "      > keystore_filepath [$keystore_filepath]"
echo "      > apk_signed_filepath [$apk_signed_filepath]"
# jarsigner -verbose -keystore $keystore_filepath $apk_filepath $keystore_alias
apksigner sign --ks $keystore_filepath --ks-key-alias $keystore_alias --out $apk_signed_filepath $apk_filepath

# apk_filepath="app/build/outputs/apk/release/zipped.apk"
# sign the apk, i should save the keyname/alias somewhere for later
# jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 -keystore ~/.keys/$keystore_alias.keystore $apk_filepath $keystore_alias