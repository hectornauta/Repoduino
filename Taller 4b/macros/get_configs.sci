function [port, configs, limit, sleep_time] = get_configs()
// Description of get_configs()
    port = input("Seleccione el puerto: ")
    bauds = input("Indique los baudios: ")
    limit = input("Indique la duración de la sesión de medida (en minutos): ") * 60
    sleep_time = input("Indique el intervalo de trazado: ")
    configs = string(bauds) + ",n,8,1"
endfunction