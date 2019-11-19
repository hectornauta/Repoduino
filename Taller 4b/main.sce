getd("./macros")
function main()
    [port, configs, limit] = get_configs()
    arduino = open_source(port, configs)
    tic()
    data = capture(arduino)
    field_names = fieldnames(data)
    [rows, columns, field_amount] = define_plot(field_names)
    while toc() < limit
        data = cat(1, data, capture(arduino))
        // TODO: Plot data using plot2d function.
        disp(data)
        sleep(100)
    end
    close_source(port)
endfunction

// Entrypoint
main()
break