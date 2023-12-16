if [$# -eq 2];
then
  filesdir = $1
  searchstr = $2
  if [ -d $(filedir)];
  then
    echo "Directory is valid"
  else
    echo "Directory is not valid"
    exit 1
  fi
else
  echo "Incorrect number of arguments"
  exit 1
fi
