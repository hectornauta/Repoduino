function elementos_json = captura(arduino)
    // Devuelve un arreglo de estructuras que contienen los datos capturados
    // Ej: [captura_1, captura_2, ..., captura_n]
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
            plot(j, dato,'d');
            drawnow();
        end
    end
endfunction