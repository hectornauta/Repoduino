getd("./macros")
function main()
    [port, configs, limit] = get_configs()
    arduino = get_source(port, configs)
    start = getdate("s")
    time = 0
    band = %t
    while time < limit
        // TODO: Aquí adentro tratar la captura de datos y graficación
        data = capture(arduino)
        plot(time, data, '.')
        time = getdate("s") - start
    end
    // closeserial(port)
endfunction

// Entrypoint
main()
break