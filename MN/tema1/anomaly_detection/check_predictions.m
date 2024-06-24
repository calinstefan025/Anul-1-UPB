function [false_positives, false_negatives, true_positives] = check_predictions(predictions, truths)
  false_positives = 0;
  false_negatives = 0;
  true_positives = 0;
  n = length(predictions);
  % crestem contoarele corespunzator
  for i = 1 : n
    % verificam legaturile dintre adevaruri si predictii
    if predictions(i) == 1 && truths(i) == 0
      false_positives = false_positives + 1;
    endif
    if predictions(i) == 0 && truths(i) == 1
      false_negatives = false_negatives + 1;
    endif 
    if predictions(i) == 1 && truths(i) == 1
      true_positives = true_positives + 1;
    endif
  endfor
endfunction