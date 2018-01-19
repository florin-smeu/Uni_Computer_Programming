function [new_score] = replay_game(score, m, var)
  
  % Aceasta functie este folosita pentru a permite utilizatorului 
  % sa joace noi partide, sa inchida programul si ofera informatii
  % despre castigatorul partidei (formatand interfata).
  
  new_score = score;  
    
  if winner(m) == var 
    disp(" ");
    disp("   -----   CONGRATULATIONS!   -----");
    disp("               You won!    ");
    disp(" ");
    new_score(1, 1)++;    
    
    fprintf("      %s     ", "YOU");
    fprintf("%d   ", new_score(1, 1));
    fprintf("%c", '-');
    fprintf("   %d", new_score(1, 2));
    fprintf("     %s", "CPU");  
    printf("\n");
    disp(" ");
    answer_end = input("Press 'r' to play again, or 'q' to exit.   ", "s");
    disp(" ");
    
    while (strcmp(answer_end, 'q') != 1 && strcmp(answer_end, 'Q') != 1 
           && strcmp(answer_end, 'R') != 1 && strcmp(answer_end, 'r') != 1)
      printf("\n");
      answer_end = input("Press 'r' to play again, or 'q' to exit.   ", "s");
    end  
    
    if (strcmp(answer_end, 'q') == 1 || strcmp(answer_end, 'Q') == 1)
      return;
    elseif (strcmp(answer_end, 'r') == 1 || strcmp(answer_end, 'R') == 1)
      [m var exit] = body(score);
      new_score = replay_game(new_score, m , var);
    end  
  elseif winner(m) == -var 
    disp(" ");
    disp(" -----   BAD LUCK THIS TIME!   -----");
    disp("              You lost!    ");
    disp(" ");
    new_score(1, 2)++;    
    
    fprintf("      %s     ", "YOU");
    fprintf("%d   ", new_score(1, 1));
    fprintf("%c", '-');
    fprintf("   %d", new_score(1, 2));
    fprintf("     %s", "CPU");  
    printf("\n");
    disp(" ");
    answer_end = input("Press 'r' to play again, or 'q' to exit.   ", "s");
    disp(" ");
    
    while (strcmp(answer_end, 'Q') != 1 && strcmp(answer_end, 'q') != 1 
           && strcmp(answer_end, 'R') != 1 && strcmp(answer_end, 'r') != 1)
      printf("\n");
      answer_end = input("Press 'r' to play again, or 'q' to exit.   ", "s");
    end  
    
    if (strcmp(answer_end, 'q') == 1 || strcmp(answer_end, 'Q') == 1)
      return;
    elseif (strcmp(answer_end, 'r') == 1 || strcmp(answer_end, 'R') == 1)
      [m var exit] = body(score);
      new_score = replay_game(new_score, m, var); 
    end  
  elseif winner(m) == 2
    disp(" ");
    disp("     -----   EQUAL MATCH!   -----");
    disp(" ");
    
    fprintf("      %s     ", "YOU");
    fprintf("%d   ", new_score(1, 1));
    fprintf("%c", '-');
    fprintf("   %d", new_score(1, 2));
    fprintf("     %s", "CPU");  
    printf("\n");
    disp(" ");
    answer_end = input("Press 'r' to play again, or 'q' to exit.   ", "s");
    disp(" ");
    
    while (strcmp(answer_end, 'Q') != 1 && strcmp(answer_end, 'q') != 1 
           && strcmp(answer_end, 'R') != 1 && strcmp(answer_end, 'r') != 1)
      printf("\n");
      answer_end = input("Press 'r' to play again, or 'q' to exit.   ", "s");
    end  
    
    if (strcmp(answer_end, 'q') == 1 || strcmp(answer_end, 'Q') == 1)
      return;
    elseif (strcmp(answer_end, 'r') == 1 || strcmp(answer_end, 'R') == 1)
      [m var exit] = body(score);
      new_score = replay_game(new_score, m, var);
    end
  end  
end  