function arduino = get_source(port, configs)
// Description of get_source(input)
    try
        disp("Abriendo el puerto " + string(port) + " a " + string(bauds) + " baudios")
        arduino = openserial(port, configs)
    catch
        arduino = -1
    end
endfunction