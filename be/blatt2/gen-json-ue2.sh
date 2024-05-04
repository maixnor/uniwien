#!/bin/bash
(return 0 2>/dev/null) && echo 'This script should not be sourced' && return 1
source_dir=$(echo $(realpath $(dirname $0)) | tr '/' '\/')
cat << 'EOF' > "$source_dir/compile_commands.json"
[
	{
		"directory": "",
		"arguments": [
			"/usr/bin/gcc",
			"-std=gnu11",
			"-Os",
			"-pedantic",
			"-Wall",
			"-Wextra",
			"-Werror",
			"-D_GNU_SOURCE",
			"-o",
			"uname",
			"uname.c"
		],
		"file": "uname.c"
	},
	{
		"directory": "",
		"arguments": [
			"/usr/bin/gcc",
			"-std=gnu11",
			"-Os",
			"-pedantic",
			"-Wall",
			"-Wextra",
			"-Werror",
			"-D_GNU_SOURCE",
			"-o",
			"statx",
			"statx.c"
		],
		"file": "statx.c"
	},
	{
		"directory": "",
		"arguments": [
			"/usr/bin/gcc",
			"-std=gnu11",
			"-Os",
			"-pedantic",
			"-Wall",
			"-Wextra",
			"-Werror",
			"-D_GNU_SOURCE",
			"-o",
			"killall",
			"killall.c"
		],
		"file": "killall.c"
	},
	{
		"directory": "",
		"arguments": [
			"/usr/bin/g++",
			"-std=gnu++20",
			"-Os",
			"-pedantic",
			"-Wall",
			"-Wextra",
			"-Werror",
			"-o",
			"uname",
			"uname.cpp"
		],
		"file": "uname.cpp"
	},
	{
		"directory": "",
		"arguments": [
			"/usr/bin/g++",
			"-std=gnu++20",
			"-Os",
			"-pedantic",
			"-Wall",
			"-Wextra",
			"-Werror",
			"-o",
			"statx",
			"statx.cpp"
		],
		"file": "statx.cpp"
	},
	{
		"directory": "",
		"arguments": [
			"/usr/bin/g++",
			"-std=gnu++20",
			"-Os",
			"-pedantic",
			"-Wall",
			"-Wextra",
			"-Werror",
			"-o",
			"killall",
			"killall.cpp"
		],
		"file": "killall.cpp"
	}
]
EOF

if [[ $? -eq 0 ]]; then
    sed -i "s;\"directory\": \"[^\"]*\",;\"directory\": \"\/home\/${USER}\",;" $source_dir/compile_commands.json
else
    echo "Writing the file did not work (missing permissions?)"
fi
