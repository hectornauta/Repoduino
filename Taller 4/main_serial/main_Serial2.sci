function [elementos_json] = captura(puerto, baudios)
    config = string(baudios) + ",n,8,1";

    arduino = openserial(puerto, config);
    captura_serial = readserial(arduino);
    elementos_json = JSONParse(captura_serial);

endfunction

function graficar(elementos_json, atributos)
    //i = 1;
    n = length(elementos_json)
    n_atributos = size(atributos, 'c') //devuelve la cantidad de columnas que tiene el arreglo

    for i = 1:n_atributos
        for j = 1:n
            dato = elementos_json(j);
            dato = dato(atributos(i))
            plot(j, dato,'d*-');
            drawnow();
        end
    end
end