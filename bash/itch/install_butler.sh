#! /bin/bash

butler_zip="build/butler.zip"
butler_dir="build/butler"
butler_file="$butler_dir/butler"
platform="linux-amd64"
latest_version_url="https://broth.itch.ovh/butler/$platform/LATEST"
# latest_html
version=$(curl -s $latest_version_url)
echo " > latest html [$version]"
# version=$(echo "$latest_html" | grep -oP '<title>\K[^<]+')
# version=$(echo "$html_string" | awk -F'<title>|</title>' '{print $2}')
# echo " > latest version [$version]"
# 15.21.0"
latest_butler="http://broth.itch.ovh/butler/$platform/$version/archive/default"
echo " > latest butler url [$latest_butler]"
if [ -f $butler_zip ]; then
    echo " > removing previous [$butler_zip]"
    rm $butler_zip
fi
if [ -d $butler_dir ]; then
    echo " > removing previous [$butler_dir]"
    rm -r $butler_dir
fi
echo " > installing butler to [$butler_zip] from [$latest_butler]"
curl -L $latest_butler -o $butler_zip
unzip $butler_zip -d $butler_dir
rm $butler_zip

chmod +x $butler_file
./$butler_file -V
./$butler_file help

