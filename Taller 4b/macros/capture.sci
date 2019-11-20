function [data, field_names] = capture(arduino)
    // Devuelve una lista de estructuras que contienen los datos capturados
    // Ej: [captura_1, captura_2, ..., captura_n]
    if arduino <> -1 then
        try
            serial_entry = readserial(arduino);
        catch
            disp("Arduino desconectado, finalizando el programa")
            quit
        end
    else
        sine = "''sine'':" + string(sin(toc()))
        cosine = "''cosine'':" + string(cos(toc()))
        tangent = "''tangent'':" + string(tan(toc()))
        serial_entry = "{" + sine + "," + cosine + "," + tangent + "}"
    end
    data = JSONParse(serial_entry);
    field_names = fieldnames(data);
    disp("Información detectada en los datos capturados: ");
    disp(field_names);
endfunction