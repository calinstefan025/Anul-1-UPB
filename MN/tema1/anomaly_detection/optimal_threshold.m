% Finds the best threshold to use for selecting outliers.
function [best_epsilon best_F1 associated_precision associated_recall] = optimal_threshold(truths, probabilities)
    % initializari
    best_epsilon = 0;
    best_F1 = 0;
    associated_precision = 0;
    associated_recall = 0;
    
    % calculam probabilitatile minime si maxime
    min_prob = min(probabilities);
    max_prob = max(probabilities);
    
    eps = min_prob; % epsilon
    for i = 1 : 1000
      pred_size = size(probabilities)
      pred = zeros(pred_size);
      
      % updatam vectorul de predictii
      for j = 1 : pred_size;
        if probabilities(j) < eps
          pred(j) = 1;
        endif
      endfor
      
      [fp, fn, tp] = check_predictions(pred, truths);
      [precision, recall, F1] = metrics(tp, fp, fn);
      
      % modificarea celor mai bune valori in cazul gasirii altora
      if best_F1 < F1
        best_F1 = F1;
        best_epsilon = eps;
        associated_precision = precision;
        associated_recall = recall;
      endif
      
      eps = eps + ((max_prob - min_prob) / 1000);
    endfor
endfunction
