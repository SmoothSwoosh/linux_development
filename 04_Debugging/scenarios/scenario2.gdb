set pagination off

file ./range
break range.c:45

set var $idx = 1
command 1
    if 28 <= $idx && $idx <= 35
        printf "@@@ %d %d %d %d\n", N, M, S, num
    end
    set $idx = $idx + 1
    continue
end

run -100 100 3 > /dev/null

quit
