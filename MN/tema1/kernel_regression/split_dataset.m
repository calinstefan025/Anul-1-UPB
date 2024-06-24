function [X_train, y_train, X_pred, y_pred] = split_dataset(X, y, percentage)
    n = size(X,1);
    a = round(n * percentage); 

    X_train = X(1 : a, :);
    y_train = y(1 : a, :);

    X_pred = X(a+1 : n, :);
    y_pred = y(a+1 : n, :);
endfunction
