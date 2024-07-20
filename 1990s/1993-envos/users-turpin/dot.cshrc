# @(#)Cshrc 1.1 86/01/06 SMI; 
#################################################################
#
#         .cshrc file
#
#         initial setups for both interactive and noninteractive
#         C-Shells
#
#################################################################


#         set up search path

set lpath = (/users/maiko/bin /usr/demo /usr/games)  #  add directories for local commands
set path = (. ~ ~/bin ~/maiko/bin /usr/local/bin /usr/ucb /usr/bin /bin /usr/bin/X11 /usr/andrew/bin)
set path = ($path[1-3] $lpath $path[4-])
#set path = ($path /etc /usr/etc)

#         cd path

#set lcd = ( )  #  add parents of frequently used directories
#cdpath = (.. ~ ~/bin ~/src $lcd)

#         set this for all shells

set noclobber

#         aliases for all shells

#alias cd            'cd \!*;echo $cwd'
#alias cp            'cp -i'
#alias mv            'mv -i'
#alias rm            'rm -i'
alias pwd           'echo $cwd'
#alias del          'rm -i'
#umask 002

#         skip remaining setup if not an interactive shell

if ($?USER == 0 || $?prompt == 0) exit

#		If this is a chat from LDE, set up as a dm2500.

if ($?LDESHELL == 1) then
	setenv TERM dm2500
	tset -e^H
   endif

#          settings  for interactive shells

set history=40
#set ignoreeof
#set notify
set savehist=40
#set prompt="% "
set prompt="`hostname` \!: "
#set time=100
setenv LDEINIT ~/INIT.LISP

#          commands for interactive shells

#date
#pwd

#         other aliases

#alias a            alias
#alias h            'history \!* | head -39 | more'
#alias u            unalias

#alias ^L            clear
#alias list         cat
alias lock          lockscreen
alias m             more
alias mroe          more
alias type         more

alias .             'echo $cwd'
alias ..            'set dot=$cwd;cd ..'
alias ,             'cd $dot '

alias dir          ls
alias pdw           'echo $cwd'
#alias ff           'find . -name \!* -print'
alias la            'ls -a'
alias ll            'ls -la'
alias ls           'ls -F'

#alias pd           dirs
#alias po           popd
#alias pp           pushd

alias open          'chmod go+r'
alias shut          'chmod go-r'
alias x             'chmod +x'

alias j             'jobs -l'
alias f             'fg %\!*'
alias lo            logout

alias bye           logout
alias ciao          logout
alias die           logout

#alias k            kill
alias psg           'ps -ax | grep \!* | grep -v grep'
alias punt          kill

#alias r            rlogin
#alias run          source
#alias slay 'set j=`ps -ax|grep \!*|head -1`; kill -9 `echo $j[1]`'

#alias nms 'tbl \!* | nroff -ms | more'                  # nroff -ms
#alias tms 'tbl \!* | troff -t -ms >! troff.output &'    # troff -ms
#alias tpr 'tbl \!* | troff -t -ms | lpr -t &'           # troff & print
#alias ppr 'lpr -t \!* &'                                # print troffed

#alias lp1           'lpr -P1'
#alias lp2           'lpr -P2'

#alias lq1           'lpq -P1'
#alias lq2           'lpq -P2'

#alias lr1           'lprm -P1'
#alias lr2           'lprm -P2'

#alias sd           'screendump | rastrepl | lpr -v &'

#alias c            'cc \!1.c \!:2* -o \!1 >>& c.errors'
#alias ccc          'cc \!*.c -o \!*'
#alias edit         textedit

#alias fem           man
#alias help          man
#alias key           'man -k'

alias mkae          make
alias te            'textedit \!* &'

# for printing 2-column, landscape on maui:
alias maui2	'enscript -2rh -Pmaui -fCourier-Bold6'


switch ("`hostname`")
	case 'rattler' : 
		setenv LDEKBDTYPE type4 ; breaksw
	default: breaksw
endsw
