#!/bin/bash
red='\033[0;31m'
green='\033[0;32m'
reset='\033[0m'
cyan='\033[0;36m'

cases=0;
while [ $cases -le 1000 ]; do
  ./gen > 1.in && ./gen_input < 1.in > input.S    
  echo -e ${cyan}"Testing std"${reset}
  time ./main < 1.in > std.out
  echo -e ${cyan}"Testing me"${reset}
  time java -jar venus-jvm-latest.jar heap.S > me.out
  ((cases=cases+1));
  if diff -Bb me.out std.out; then
      echo -e ${green}'test '$cases' Accepted!'${reset}
  else
      echo -e ${red}'WrongAnswer on test '$cases${reset}
      exit 0
  fi
done
