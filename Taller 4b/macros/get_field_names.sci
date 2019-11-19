function field_names = get_field_names(data)
// Description of get_field_names(input)
    field_names = fieldnames(data)
    disp("Información detectada en los datos capturados: ")
    disp(field_names)
endfunction