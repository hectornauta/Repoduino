getd("./functions")
function main()
    puerto = input("Seleccione el puerto: ")
    baudios = input("Indique los baudios: ")
    configs = string(baudios) + ",n,8,1"
    disp("Abriendo el puerto " + string(puerto) + " a " + string(baudios) + " baudios")
    arduino = openserial(puerto, configs)
	closeserial(arduino)
endfunction

// Entrypoint
main()
break