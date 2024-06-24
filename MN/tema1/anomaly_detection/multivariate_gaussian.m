% Computes the probability density function of the multivariate gaussian distribution.
function probabilities = multivariate_gaussian(X, mean_values, variances)
    [m n] = size(X)
    probabilities = zeros(m, n);
    probabilities = gaussian_distribution(X , mean_values , variances);
endfunction
