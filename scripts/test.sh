#!bin/sh
print_and_exec() {
  echo $1
  echo
  echo $1 | bash
}

test_directory() {
  if test $# -le 0; then
    return 0
  fi

  for dirent in "$1/*"; do
    if test -f $dirent; then
      print_and_exec "gcc $dirent -o ./temp.o"
      ./temp.o
      rm ./temp.o
      echo
    elif test ! $dirent = $1; then
      test_directory $dirent
    fi
  done
}

test_directory ./test
