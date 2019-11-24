function output = clean_data(data)
    // Verificar que los datos sean correctos
    n = length(data)
    if part(data, n) <> '}'
        // Arreglar
        ind = strindex(data, "}")
        pos = ind($)
        [output, _] = strsplit(data, pos)
        return
    end
    output = data
    return
endfunction

