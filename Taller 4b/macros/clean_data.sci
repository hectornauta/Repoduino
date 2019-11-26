function output = clean_data(data)
    // Primer control. Limpiar la cabeza de los datos
    ind_1 = strindex(data, "{") //Índices de llaves que se abren
    if part(data, 1) <> "{"
        pos = ind_1(1)
        temp = (strsplit(data, pos - 1))
        data = temp(2) // Toma la segunda mitad
    end
    // Limpiar la cola de los datos
    n = length(data)
    
    //  Primer control. Limpiar la cola de los datos
    ind_2 = strindex(data, "}") //Índices de llaves que se cierran
    if part(data, n) <> "}"
        pos = ind_2($)
        temp = strsplit(data, pos)
        data = temp(1) // Toma la primer mitad
    end

    // Último control
    n1 = length(ind_1)
    n1 = n1 - 1 //Se recorrerá hasta la anteúltima posición
    n2 = length(ind_2)

    for i = 1:n1

        aux = ind_1(i)
        aux_2 = ind_2(i)
        aux_3 = ind_1(i+1)

        if ~((aux < aux_2) & (aux_2 < aux_3))
            pos = aux_3
            temp = (strsplit(data, pos - 1))
            data = temp(2)
        end 
    end

    output = data
endfunction

