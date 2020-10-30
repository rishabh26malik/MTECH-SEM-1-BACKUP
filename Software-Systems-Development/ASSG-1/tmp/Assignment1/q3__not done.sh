#!/bin/bash
HISTFILE=~/.bash_history
set -o history
history 10 | awk '{$1=""; print $0}' | sort | uniq -c
