function arduino = open_source(port, configs)
// Description of open_source(input)
    try
        disp("Abriendo el puerto " + string(port) + " a " + string(bauds) + " baudios")
        arduino = openserial(port, configs)
    catch
        disp(lasterror())
        disp("Error al abrir la comunicación serial, utilizando la siguiente configuración: ")
        disp("Puerto: " + string(port))
        disp("Configuraciones: " + string(configs))
        arduino = -1
    end
endfunction