function [] = print_table(m)
  
  % Afisarea tablei de joc. 
  
  disp("--------------------------------------")
  for i = 1 : 3
    printf("                ");
    for j = 1 : 3
      if m(i, j) == -1
         fprintf("%c ", 'O');
      elseif m(i, j) == 0
         fprintf("%c ", '-');
      else 
         fprintf("%c ", 'X');
      end
    end
    printf("\n");
  end
  disp("--------------------------------------")
end  