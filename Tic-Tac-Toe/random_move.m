function m = random_move(m, var)   
  
  % Folosind aceasta functie, CPU va juca random 
  % in cele 4 colturi sau in centrul tablei, 
  % in anumite circumstante. 
  
  sum = 1; 
  while rem(sum, 2) != 0 
    a = floor(1 + 3 * rand(1));
    b = floor(1 + 3 * rand(1));
    sum = a + b;
  end
  if m(a, b) == 0   
     m(a, b) = -var;
     return;
  else 
     m = random_move(m, var);   
  end  
end