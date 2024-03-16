#!/bin/sh

if [ $# -eq 2 ]
then
  filesdir=$1
  searchstr=$2
  if [ -d $filedir ];
  then
    echo "Directory is valid"
  else
    echo "Directory is not valid"
    exit 1
  fi
else
  echo $#
  echo "Incorrect number of arguments"
  exit 1
fi
numfiles=$(grep -r -c $searchstr $filesdir | grep -v :0 | grep -c :)
numocc=$(grep -r $searchstr $filesdir| grep -c $searchstr)
echo "The number of files are $numfiles and the number of matching lines are $numocc"