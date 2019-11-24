function output = clean_data(data)
    // Limpiar la cabeza de los datos
    if part(data, 1) <> "{"
        ind = strindex(data, "{")
        pos = ind(1)
        temp = (strsplit(data, pos - 1))
        data = temp(2) // Toma la segunda mitad
    end
    // Limpiar la cola de los datos
    n = length(data)
    if part(data, n) <> "}"
        ind = strindex(data, "}")
        pos = ind($)
        temp = strsplit(data, pos)
        data = temp(1) // Toma la primer mitad
    end
    output = data
endfunction

