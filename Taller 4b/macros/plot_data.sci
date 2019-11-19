function plot_data(data, rows, columns, field_amount, field_names)
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