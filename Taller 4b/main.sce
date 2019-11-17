getd("./macros")
function main()
    [port, configs, limit] = get_configs()
    arduino = open_source(port, configs)
    tic()
    while toc() < limit
        // TODO: Aquí adentro tratar la captura de datos y graficación
        data = capture(arduino)
        plot(time, data, '.')
    end
    close_source(port)
endfunction

// Entrypoint
main()
break