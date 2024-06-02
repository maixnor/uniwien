#!/home/maixnor/.nix-profile/bin/bash

# Watch for file changes in the current directory recursively (-r)
inotifywait -m -r -e modify . |
while read -r directory event filename; do
  make && ./main.out
done

