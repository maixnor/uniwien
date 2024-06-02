#!/home/maixnor/.nix-profile/bin/bash

# Watch for file changes in the current directory recursively (-r)
inotifywait -m -r -e modify,create,delete . |
while read -r directory event filename; do
  g++ main.cpp -o main.out && ./main.out
done

