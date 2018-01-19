function [i j] = wrong_input(m, pos_user)

  % Pot aparea situatii in care utilizatorul sa introduca
  % optiuni invalide. Aceasta functie se asigura ca inputul
  % este valid.
    
  while (pos_user < 49 || pos_user > 57 || length(pos_user) > 1
         || length(pos_user) == 0)  
      disp(" ");
      pos_user = input("Pick a digit from 1 to 9.       ", "s");
      pos_user = toascii(pos_user);
  end
    
    digit = pos_user - '0';
    i = floor(rdivide((digit - 1), 3)) + 1;
    j = rem((digit - 1), 3) + 1;
end