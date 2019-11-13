function captura_serial())
    //Se abre el puerto
    h = openserial(puerto,"baudios,n,8,1"); //hay que configurar el puerto y los baudios
    captura_serial = readserial(h) + ' '; //Se obtiene la captura serial
    //Se agrega el elemento en blanco para que la función que parte el string, no se rompa
    index = strindex(captura_serial,'}'); //Se busca dónde se encuentra el corchete final de cada json
    captura_elementos = strsplit(captura_serial,index); //Se cortan los jsons
    elementos_json = JSONParse(captura_elementos); //Se parsean los elementos a jsons, que serán almacenados en el arreglo "elementos_json"

    //En este punto se puede acceder a cada elemento del arreglo, como si fuera un JSON
    //Se debe tener cuidado con el JSON que se envía desde el Arduino ya que el elemento de corte es "}"

    


