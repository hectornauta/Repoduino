function output = close_source(port)
// Description of close_source(source)
    try
        closeserial(port)
    catch
    end
endfunction