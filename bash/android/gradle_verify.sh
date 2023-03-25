#!/bin/bash

apk_unsigned_filepath="build/android-build/app/build/outputs/apk/release/app-release-unsigned.apk"
apk_signed_filepath="build/android-build/app/build/outputs/apk/release/zoxel.apk"

echo "  > verifying unsigned [$apk_unsigned_filepath]"
apksigner verify $apk_unsigned_filepath

echo "  > verifying signed [$apk_signed_filepath]"
apksigner verify $apk_signed_filepath