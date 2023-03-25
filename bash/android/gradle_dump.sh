#!/bin/bash

apk_filepath="build/android-build/app/build/outputs/apk/release/app-release-unsigned.apk"
aapt2 dump badging $apk_filepath