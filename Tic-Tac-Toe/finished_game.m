function x = finished_game(m)
  
  % Functie care calculeaza daca partida s-a incheiat sau nu.
  
  if (m(1, 1) == m(2, 2) && m(2, 2) == m(3, 3)
      && m(1, 1) != 0) 
    x = 0;
    return;
  end
  
  if (m(3, 1) == m(2, 2) && m(2, 2) == m(1, 3)
      && m(1, 3) != 0) 
    x = 0; 
    return;
  end
  
  for i = 1 : 3
    if (m(i, 1) == m(i, 2) && m(i, 2) == m(i, 3) 
        && m(i, 1) != 0)
      x = 0;
      return; 
    end
  end
  
  for j = 1 : 3
    if (m(1, j) == m(2, j) && m(2, j) == m(3, j) 
        && m(1, j) != 0)
      x = 0;
      return; 
    end
  end  
      
  for i = 1 : 3 
    for j = 1 : 3
      if m(i, j) == 0
        x = 1;
        return;
      else 
        x = 0;
      end
    end
  end 
  
end
    