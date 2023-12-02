#!/bin/bash
source bash/android/gradle_pathing.sh
start_gradle_build
keystore_alias="zoxel"
# echo "need to sign apk: "
apk_filepath="build/android-build/app/build/outputs/apk/release/app-release-unsigned.apk"
apk_signed_filepath="build/android-build/app/build/outputs/apk/release/zoxel.apk"
keystore_filepath="$HOME/.keys/$keystore_alias.keystore"

echo "  > signing android release build with alias [$keystore_alias]"
echo "      > keystore_filepath [$keystore_filepath]"
echo "      > apk_signed_filepath [$apk_signed_filepath]"
# jarsigner -verbose -keystore $keystore_filepath $apk_filepath $keystore_alias
#apksigner sign --ks $keystore_filepath --ks-key-alias $keystore_alias --out $apk_signed_filepath $apk_filepath

# sh $ANDROID_SDK_ROOT/build-tools/30.0.3/apksigner
bash $apksigner sign --ks $keystore_filepath --ks-key-alias $keystore_alias --out $apk_signed_filepath $apk_filepath

if [ $? -ne 0 ]; then
    echo "  > gradlew signing command failed"
    clear_gradle_build
    exit 1
else
    echo "  > gradlew signing was successful"
fi

end_gradle_build
# apk_filepath="app/build/outputs/apk/release/zipped.apk"
# sign the apk, i should save the keyname/alias somewhere for later
# jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 -keystore ~/.keys/$keystore_alias.keystore $apk_filepath $keystore_alias
