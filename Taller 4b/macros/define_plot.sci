function [rows, columns, field_amount] = define_plot(field_names)
// Description of initialize_plot(input)
    field_amount = size(field_names, "r")    
    rows = ceil(sqrt(field_amount))
    columns = rows
    disp("Cantidad de campos: " + string(field_amount))
    disp("Cantidad de filas del gráfico: " + string(rows))
    disp("Cantidad de columnas del gráfico: " + string(columns))
    for i = 1:field_amount
        subplot(rows, columns, i)
        plot2d()
        title(field_names(i))
    end
    drawnow()
endfunction