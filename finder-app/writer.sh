#!/bin/sh

if [ $# -eq 2 ]
then
  writefile=$1
  writestr=$2

else
  echo $#
  echo "Incorrect number of arguments"
  exit 1
fi
dirname=$(dirname $writefile)
if [ ! -d $dirname ]
then
    mkdir -p $dirname
fi
echo $writestr > $writefile