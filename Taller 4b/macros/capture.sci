function elementos_json = capture(arduino)
    // Devuelve un arreglo de estructuras que contienen los datos capturados
    // Ej: [captura_1, captura_2, ..., captura_n]
    if arduino <> -1 then
        captura_serial = readserial(arduino);
        elementos_json = JSONParse(captura_serial);
    else
        elementos_json = sin(getdate("s"))
    end
endfunction