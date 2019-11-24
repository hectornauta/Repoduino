getd("./macros")
function main()
    [port, configs, limit, sleep_time] = get_configs()
    arduino = open_source(port, configs)
    tic()
    sleep(6000)
    [data, field_names] = capture(arduino)
    disp("Información detectada en los datos capturados: ")
    disp(field_names)
    [rows, columns, field_amount] = define_plot(field_names)
    t = 0
    if sleep_time > 0
        sleep(sleep_time)
    end
    while toc() < limit
        [newdata, _] = capture(arduino)
        data = cat(1, data, newdata) 
        while size(data, "r") > 1
            if sleep_time > 0
                sleep(sleep_time)
            end
            plot_data(data, rows, columns, field_amount, field_names, t)
            data = data(2:$) // Descartamos el primer elemento de la lista
            t = t + 1
        end
    end
    close_source(port)
endfunction

// Entrypoint
try
    main()
catch
    close_source(port)
end
break