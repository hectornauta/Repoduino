function data = capture(arduino)
    // Devuelve una lista de estructuras que contienen los datos capturados
    // Ej: [captura_1, captura_2, ..., captura_n]
    if arduino <> -1 then
        serial_entry = readserial(arduino);
    else
        sine = "''sine'':" + string(sin(toc()))
        cosine = "''cosine'':" + string(cos(toc()))
        serial_entry = "{" + sine + "," + cosine + "}"
    end
    data = JSONParse(serial_entry);
endfunction