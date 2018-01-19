function m = algorithm(m, var)

  % Algoritmul dupa care CPU va juca.
  % Sunt tratate cazurile in care acesta 
  % poate sa castige, in care evita infrangerea, etc.  
  
  if (m(1, 3) == m(3, 1) && m(1, 3) == 1)
    if m(2, 3) == 0
      m(2, 3) = -var;
      return;
    end  
  end  
  
  for i = 1 : 3
    if (m(i, 1) == m(i, 2) && m(i, 1) == -var) 
      if m(i, 3) == 0
        m(i, 3) = -var;
        return;
      end  
    end
    if (m(i, 2) == m(i, 3) && m(i, 2) == -var)
      if m(i, 1) == 0
        m(i, 1) = -var;
        return;
      end  
    end
    if (m(i, 1) == m(i, 3) && m(i, 1) == -var)
      if m(i, 2) == 0
        m(i, 2) = -var;
        return;
      end 
    end  
  end   

  for j = 1 : 3
    if (m(1, j) == m(2, j) && m(1, j) == -var) 
      if m(3, j) == 0 
        m(3, j) = -var;
        return;
      end  
    end
    if (m(2, j) == m(3, j) && m(2, j) == -var)
      if m(1, j) == 0
        m(1, j) = -var;
        return;
      end  
    end
    if (m(1, j) == m(3, j) && m(1, j) == -var)
      if m(2, j) == 0
        m(2, j) = -var;
        return;
      end  
    end  
  end 
 
 
  for i = 1 : 3
    if (m(i, 1) == m(i, 2) && m(i, 1) == var) 
      if m(i, 3) == 0
        m(i, 3) = -var;
        return;
      end  
    end
    if (m(i, 2) == m(i, 3) && m(i, 2) == var)
      if m(i, 1) == 0
        m(i, 1) = -var;
        return;
      end  
    end
    if (m(i, 1) == m(i, 3) && m(i, 1) == var)
      if m(i, 2) == 0
        m(i, 2) = -var;
        return;
      end 
    end  
  end   

  for j = 1 : 3
    if (m(1, j) == m(2, j) && m(1, j) == var) 
      if m(3, j) == 0 
        m(3, j) = -var;
        return;
      end  
    end
    if (m(2, j) == m(3, j) && m(2, j) == var)
      if m(1, j) == 0
        m(1, j) = -var;
        return;
      end  
    end
    if (m(1, j) == m(3, j) && m(1, j) == var)
      if m(2, j) == 0
        m(2, j) = -var;
        return;
      end  
    end  
  end  
  
  if m(1, 1) == var
    if m(3, 3) == 0
      m(3, 3) = -var;
      return;
    end  
  end  
  if m(1, 3) == var
    if m(3, 1) == 0  
      m(3, 1) = -var;
      return;
    end  
  end    
  if m(3, 1) == var
    if m(1, 3) == 0 
      m(1, 3) = -var;
      return;
    end
  end  
  if m(3, 3) == var
    if m(1, 1) == 0
      m(1, 1) = -var;
      return;
    end  
  end  

  if m(1, 1) == 0
    m(1, 1) = -var;
    return;
  end
  if m(1, 2) == 0
    m(1, 2) = -var;
    return;
  end
  if m(1, 3) == 0
    m(1, 3) = -var;
    return;
  end
  if m(2, 1) == 0 
    m(2, 1) = -var;
    return;
  end
  if m(2, 2) == 0
    m(2, 2) = -var;
    return;
  end
  if m(2, 3) == 0
    m(2, 3) = -var;
    return;
  end
  if m(3, 1) == 0
    m(3, 1) = -var;
    return;
  end
  if m(3, 2) == 0
    m(3, 2) = -var;
    return;
  end
  if m(3, 3) == 0
    m(3, 3) = -var;
    return;
  end

end  