#!/bin/bash

if ! grep -q "echo 'source \"\$HOME/projects/emsdk/emsdk_env.sh\"' >> \$HOME/.bash_profile" $HOME/.bash_profile; then
    echo 'source "$HOME/projects/emsdk/emsdk_env.sh"' >> $HOME/.bash_profile
    echo "  > emscripten environment variables added to .bash_profile"
else
    echo "  > emscripten environment variables are already present in .bash_profile"
fi