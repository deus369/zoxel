cd ~/projects/open-zoxel
make -f MakeWeb -B -j24
emrun --browser firefox zoxel.html
echo Done
sleep 30