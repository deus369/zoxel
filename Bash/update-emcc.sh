
cd ~

echo "Rebuilding EM SDK for web builds."
sudo rm -r emsdk
sudo rm -r /user/share/emscripten


git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
git pull
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh

# add emcc to envvironment
source "/home/deus/emsdk/emsdk_env.sh"
echo 'source "/home/deus/emsdk/emsdk_env.sh"' >> $HOME/.bash_profile

echo finished~ 
sleep 30