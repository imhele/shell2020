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

  for dirent in $(find $1 -depth -type f -name "*.c"); do
    print_and_exec "gcc $dirent -o ./temp.o"
    ./temp.o
    if [ $? -ne 0 ]; then
      exit 1
    fi
    rm ./temp.o
    echo
  done
}

if test $# -le 0; then
  test_directory ./test
else
  test_directory $1
fi
