function [m var exit]= body(score)
  
  exit = 1;
  m = zeros(3);
  
  % Se solicita alegerea unui simbol 'X' sau 'O'.
  % Tratam si erorile.
  answer = input("Make your choice: X or O?   ", "s");
  disp(" ");
  
  if  (strcmp(answer, 'O') != 1 && strcmp(answer, 'o') != 1 
         && strcmp(answer, 'X') != 1 && strcmp(answer, 'x') != 1)
        
        disp("Whoops! :/ You have chosen an invalid option."); 
  end
  
  while (strcmp(answer, 'O') != 1 && strcmp(answer, 'o') != 1 
         && strcmp(answer, 'X') != 1 && strcmp(answer, 'x') != 1) 
    
    answer = input("Try again, please! Press 'x' or 'o'.   ", "s");
  end
  
  % Codificam 'X' cu 1 si 'O' cu -1.
  if (strcmp(answer, 'O') == 1 || strcmp(answer, 'o') == 1) 
    var = -1;
  elseif (strcmp(answer, 'X') == 1 || strcmp(answer, 'x') == 1)  
    var = 1;
  end  
  
  % Parte a algoritmului de joc.
  if var == -1 
    if m(2, 2) == 0
       m(2, 2) = -var;
    else  
       m = random_move(m, var);
    end
  end  
  
  % Functie care afiseaza tabla.
  print_table(m);
  
  % Vrem sa stim unde vrea persoana sa joace.
  pos_user = input("It's your turn.        ", "s");
  pos_user = toascii(pos_user);
  [i j] = wrong_input(m, pos_user);
  
  % Persoana poate alege o pozitie in care deja exista 'X' sau 'O'.
  % De asemenea, poate introduce o pozitie invalida.
  % 'wrong_input' se asigura ca cifra introdusa este valida.
  while m(i, j) != 0
      disp(" ");
      pos_user = input("Choose another position that is empty.     ", "s");
      pos_user = toascii(pos_user);
      [i j] = wrong_input(m, pos_user);
  end    
  
  % O prima mutare a jucatorului si o parte a algoritmului de joc.
  m(i, j) = var;
  if m(2, 2) == 0
    m(2, 2) = -var;  
  else 
    m = random_move(m, var);
  end  
  print_table(m);
  
  % Atat timp cat meciul nu este incheiat, solicit jucatorului sa aleaga
  % unde joaca.  
  while finished_game(m) != 0 
  
    pos_user = input("It's your turn.        ", "s");
    pos_user = toascii(pos_user);
      
    [i j] = wrong_input(m, pos_user);
    
    while m(i, j) != 0
      disp(" ");
      pos_user = input("Choose another position that is empty.     ", "s");
      pos_user = toascii(pos_user);
      [i j] = wrong_input(m, pos_user);
    end    
    
    m(i, j) = var;
    
    % Testez daca utilizatorul a castigat. El va putea sa inchida programul,
    % sau sa rejoace.
    if winner(m) == var 
      print_table(m);
      
      disp(" ");
      disp("   -----   CONGRATULATIONS!   -----");
      disp("               You won!    ");
      disp(" ");
      score(1, 1)++;    
    
      fprintf("      %s     ", "YOU");
      fprintf("%d   ", score(1, 1));
      fprintf("%c", '-');
      fprintf("   %d", score(1, 2));
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
        exit = 0;
        return;
      elseif (strcmp(answer_end, 'r') == 1 || strcmp(answer_end, 'R') == 1)
        [m var exit] = body(score);
        score = replay_game(score, m , var);
      end  
    end
    
    % Functia 'algorithm' descrie algoritmul de joc.
    m = algorithm(m, var);
     
    print_table(m);  
  end  