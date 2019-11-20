tic()
time = 0
value = sin(time)
while %t
    next = toc()
    next_value = sin(next)
    plot2d([time, next], [value, next_value])
    time = next
    value = next_value
    sleep(10)
end