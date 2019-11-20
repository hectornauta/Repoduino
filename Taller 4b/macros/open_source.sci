function arduino = open_source(port, configs)
// Description of open_source(input)
    try
        disp("Abriendo el puerto " + string(port) + " a " + string(bauds) + " baudios")
        arduino = openserial(port, configs)
    catch
        disp("Error al abrir la comunicación serial, utilizando datos de prueba")
        arduino = -1
    end
endfunction