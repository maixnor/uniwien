#!/home/maixnor/.nix-profile/bin/bash

# Watch for file changes in the current directory recursively (-r)
inotifywait -m -r -e modify,create,delete . |
while read -r directory event filename; do
    # Check if the modified file is main.cpp
    if [[ "$filename" == "main.cpp" ]]; then
        # Replace the command below with your compile and execute command
        g++ main.cpp -o main.out && ./main.out
    fi
done

