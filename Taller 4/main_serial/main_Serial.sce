function captura_serial())
    //Se abre el puerto
    h = openserial(puerto,"baudios,n,8,1"); //hay que configurar el puerto y los baudios
    captura_serial = readserial(h) //Se obtiene la captura serial
    elementos_json = JSONParse(captura_serial); //Se parsean los elementos a jsons, que serán almacenados en el arreglo "elementos_json"

    //En este punto se puede acceder a cada elemento del arreglo, como si fuera un JSON

    


