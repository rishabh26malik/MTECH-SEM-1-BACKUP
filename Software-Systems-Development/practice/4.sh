#!/bin/bash
i=0
dir="/home/rishabh/learn/"
ext=".try"
for f in /home/rishabh/learn/*; do
  mv "${f}" "${f}${ext}"
done