set pagination off

file ./range
break range.c:45 if (num % 5 == 0)

command 1
    printf "@@@ %d %d %d %d\n", N, M, S, num
    continue
end

run 1 12 > /dev/null

quit
