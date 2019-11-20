getd("./macros")
function main()
    [port, configs, limit, sleep_time] = get_configs()
    arduino = open_source(port, configs)
    tic()
    data = capture(arduino)
    field_names = get_field_names(data)
    [rows, columns, field_amount] = define_plot(field_names)
    t = 0
    while toc() < limit
        data = cat(1, data, capture(arduino))
        // TODO: Plot data using plot2d function.
        while size(data, "r") > 1
            plot_data(data, rows, columns, field_amount, field_names, t)
            data = data(2:$) // Descartamos el primer elemento de la lista
            t = t + 1
        end
        sleep(sleep_time)
    end
    close_source(port)
endfunction

// Entrypoint
main()
break