function output = clean_data(data)
    ind = strindex(data, "}")
    n = length(data)
    // Limpiar la cabeza de los datos
    pos = 0
    limit = ind(1)
    if limit == 1
        limit = ind(2)
    end
    for i = 1:limit
        if part(data, i) == "{"
            pos = i
        end
    end
    if pos > 1
        temp = strsplit(data, pos - 1)
        data = temp(2) // Toma la segunda mitad
    end
    // Limpiar la cola de los datos
    if part(data, n) <> '}'
        pos = ind($)
        temp = strsplit(data, pos)
        data = temp(1) // Toma la primer mitad
    end
    output = data
endfunction

