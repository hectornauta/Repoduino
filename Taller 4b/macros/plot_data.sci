function plot_data(data, rows, columns, field_amount, field_names, t)
    //i = 1;
    struct1 = data(1)
    struct2 = data(2)
    for i = 1:field_amount
        y1 = struct1(field_names(i))
        y2 = struct2(field_names(i))
        subplot(rows, columns, i)
        plot2d([t, t+1], [y1, y2])
    end