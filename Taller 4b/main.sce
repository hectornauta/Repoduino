getd("./macros")
function main()
    [port, configs, limit] = get_configs()
    arduino = open_source(port, configs)
    tic()
    while toc() < limit
        data = cat(data, capture(arduino))
        // TODO: Plot data using plot2d function.
        disp(data)
    end
    close_source(port)
endfunction

// Entrypoint
main()
break