function [rows, columns, field_amount] = define_plot(field_names)
// Description of initialize_plot(input)
    field_amount = length(field_names)    
    rows = ceil(field_amount)
    columns = rows
endfunction