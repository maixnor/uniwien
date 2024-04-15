#!/bin/bash

cat << 'EOF' > "$HOME/.vimrc"
"turn on syntax highlightning of dark backgrounds
syntax on	
set background=dark
" highlight search 
set hlsearch        "nohlsearch
"set number 	    "set nonu
" enter paste mode per default 
set paste           

" TAB config 
set tabstop=2       "number of spaces for tab
set shiftwidth=2    "number of spaces for intend
set softtabstop=2   "backspace treat four spaces lika a tab 
set expandtab       "replace '\t' with 0x20 (space) "set noexpandtab" to edit makefiles
autocmd FileType make setlocal noexpandtab "exclude makefiles

"" activate markdown syntax highlighting per default 
au BufNewFile,BufFilePre,BufRead *.md set filetype=markdown

EOF

echo "PS1='"'${debian_chroot:+($debian_chroot)}\u@\h:\D{%s}:$(echo $?):\w\n\$ '"'" >> $HOME/.bashrc


read -p "Enter current LAB = " LAB
read -p "Enter current TASK = " TASK
export LAB
export TASK
# start script
# to replay it:
# $ scriptreplay -t "./$(hostname).${LAB}.${TASK}.tm" "./$(hostname).${LAB}.${TASK}.log"
# or
# $ cat "./$(hostname).${LAB}.${TASK}.log" | more
script --timing="./$(hostname).${LAB}.${TASK}.tm" -fa "./$(hostname).${LAB}.${TASK}.log"
/bin/bash

