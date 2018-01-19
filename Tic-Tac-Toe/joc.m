function [] = joc()
  
  % 'A' este folosita doar pentru a codifica pozitiile tablei, 
  % cu rol doar in interfata in command line.
  % Nu reprezinta matricea tablei!! 
  
  A = size(3);
  value = 1;
  for i = 1 : 3
    for j = 1 : 3
      A(i, j) = value;
      value++;
    end
  end 
  
  %Formatare interfata.
  disp("                X vs O                ");  
  disp("--------------------------------------");
  disp(" ");
  disp("The configuration of the table is:");
  for i = 1 : 3
    printf("                ");  
    for j = 1 : 3
      fprintf("%d ", A(i, j));
    end
    printf("\n");
  end
   
  disp("Pick a digit to play in that position.");
  disp(" ");
  
  % Variabila score va retine scorul partidelor.
  % 'm' este matricea pe baza careia se construieste tabla de joc.
  % 'var' retine daca jucatorul alege 'X' sau 'O'.
  % 'exit' este un flag care permite iesirea din functia 'joc', in 
  % anumite circumstante.
  % 'body' este functia "principala".
  % 'replay_game' este necesara in cazul in care utilizatorul
  % doreste sa rejoace partide.
  score = zeros(1, 2);
  [m var exit] = body(score); 
  if exit == 0
    return;
  end  
  score = replay_game(score, m, var);  
  
end
  
  
  