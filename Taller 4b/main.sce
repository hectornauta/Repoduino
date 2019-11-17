getd("./macros")
function main()
    [port, configs, limit] = get_configs()
    arduino = get_source(port, configs)
    start = getdate("s")
    tic()
    while toc() < limit
        // TODO: Aquí adentro tratar la captura de datos y graficación
        data = capture(arduino)
        plot(time, data, '.')
    end
    // closeserial(port)
endfunction

// Entrypoint
main()
break