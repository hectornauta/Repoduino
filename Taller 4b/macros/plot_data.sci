function plot_data(data, rows, columns, field_amount, field_names, t)
    time_window = 50
    left_limit = t - time_window
    right_limit = t + time_window
    upper_limit = 1.2
    lower_limit = - 1.2
    //i = 1;
    struct1 = data(1)
    struct2 = data(2)
    for i = 1:field_amount
        y1 = struct1(field_names(i))
        y2 = struct2(field_names(i))
        subplot(rows, columns, i)
        axes = gca()
        axes.data_bounds = [left_limit, lower_limit; right_limit, upper_limit]
        plot2d([t, t+1], [y1, y2])
    end
endfunction