// author: Smeu Florin-Ion
// email: florin.ion.smeu@gmail.com

#include <stdio.h>
#include <stdlib.h>

#define EPERM 1
#define EINVAL 2
#define ENOMEM 3

typedef struct {
	int r, g, b;
} pixel;


void print_matrix(pixel **matrix, int height, int width) 
{
	int i, j;

	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			printf("%d %d %d ", 
			       matrix[i][j].r, matrix[i][j].g, matrix[i][j].b);
		}
		printf("\n");
	}
	fflush(stdout);
}

void deallocate_matrix(pixel **matrix, int height) 
{
 	int i;	
	for (i = 0; i < height; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

pixel **allocate_matrix(int height, int width) 
{
	int i;
	pixel **matrix;
	
	matrix = malloc(height * sizeof(pixel *));
	if (matrix == NULL) {
		fprintf(stderr, "%d\n", ENOMEM);
		exit(EXIT_FAILURE);
	}
	
	for (i = 0; i < height; i++) {
		matrix[i] = malloc(width * sizeof(pixel)); 
		if (matrix[i] == NULL) {
 			fprintf(stderr, "%d", ENOMEM);
			deallocate_matrix(matrix, height);
			exit(EXIT_FAILURE);
		}
	}

	return matrix;
}
	
pixel **get_matrix(int height, int width) 
{
	int i, j;	
	pixel **matrix;
	matrix = allocate_matrix(height, width);

	for (i = 0;  i < height; i++) {
		for (j= 0; j < width; j++) {
			scanf("%d", &matrix[i][j].r);
			if (matrix[i][j].r < 0 || matrix[i][j].r > 255) {
				fprintf(stderr, "%d", EINVAL);
				deallocate_matrix(matrix, height);
				exit(EXIT_FAILURE);
			}		
			scanf("%d", &matrix[i][j].g);
			if (matrix[i][j].r < 0 || matrix[i][j].r > 255) {
				fprintf(stderr, "%d", EINVAL);
				deallocate_matrix(matrix, height);
				exit(EXIT_FAILURE);
			}		
			scanf("%d", &matrix[i][j].b);
			if (matrix[i][j].r < 0 || matrix[i][j].r > 255) {
				fprintf(stderr, "%d", EINVAL);
				deallocate_matrix(matrix, height);
				exit(EXIT_FAILURE);
			}		
		}
	}
	
	return matrix;
}

pixel **crop(pixel **matrix, int height, int start_col, int start_line,
	     int end_col, int end_line)
{
	int i, j;
	int new_height = end_line - start_line + 1;
	int new_width  = end_col - start_col + 1;
	
	pixel **new_mat;
	new_mat = allocate_matrix(new_height, new_width);
	
	for(i = 0; i < new_height; i++) {
		for (j = 0; j < new_width; j++) {
			new_mat[i][j] = matrix[i + start_line][j + start_col];
		}
	}
	
	deallocate_matrix(matrix, height);
	
	return new_mat; 
}

pixel **resize(pixel **matrix, int height, int width, 
	       int new_height, int new_width) 
{
	int i, j;

	pixel **new_mat;
	new_mat = allocate_matrix(new_height, new_width);
	
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			if(i < new_height && j < new_width)  
				new_mat[i][j] = matrix[i][j];
		}
	}
	
	for (i = 0; i < new_height; i++) {
		for (j = width; j < new_width; j++) {
			new_mat[i][j].r = 255;
			new_mat[i][j].g = 255;
			new_mat[i][j].b = 255;	
		}
	}
	
	for (i = height; i < new_height; i++) {
		for (j = 0; j < new_width; j++) {
			new_mat[i][j].r = 255;
			new_mat[i][j].g = 255;
			new_mat[i][j].b = 255;	
		}
	}
	
	deallocate_matrix(matrix, height);

	return new_mat;	
}

void colour(pixel **matrix, int r, int g, int b,
	      int start_col, int start_line, int end_col, int end_line)
{
	int i, j;
	
	for (i = start_line; i <= end_line; i++) {
		for (j = start_col; j <= end_col; j++){
			matrix[i][j].r = r;
			matrix[i][j].g = g;
			matrix[i][j].b = b;	
		}
	}	
}	

pixel **blur(pixel **matrix, int height, int width, int n_iter) 
{	
	int i, j; 
	int sum_r = 0, sum_g  = 0, sum_b = 0;
	int ctr = 0;
	
	pixel **new_mat;
	
	while (n_iter != 0) {
		new_mat = allocate_matrix(height, width);
	
		for (i = 0; i < height; i++) {
			for (j = 0; j < width; j++) {
				sum_r = sum_g = sum_b = ctr = 0;
				if (i - 1 >= 0) {
					sum_r += matrix[i - 1][j].r;
					sum_g += matrix[i - 1][j].g;
					sum_b += matrix[i - 1][j].b;
					ctr++;
				}
				if (i + 1 < height) {
					sum_r += matrix[i + 1][j].r;
					sum_g += matrix[i + 1][j].g;
					sum_b += matrix[i + 1][j].b;
					ctr++;
				}
				if (j - 1 >= 0) {
					sum_r += matrix[i][j - 1].r;
					sum_g += matrix[i][j - 1].g;
					sum_b += matrix[i][j - 1].b;
					ctr++;
				}
				if (j + 1 < width) {
					sum_r += matrix[i][j + 1].r;
					sum_g += matrix[i][j + 1].g;
					sum_b += matrix[i][j + 1].b;
					ctr++;
				}
				
				new_mat[i][j].r = sum_r / ctr;
				new_mat[i][j].g = sum_g / ctr;
				new_mat[i][j].b = sum_b / ctr;
			}
		}
		deallocate_matrix(matrix, height);
		matrix = new_mat;
		n_iter--;
	}	
		
	return matrix;
}

pixel **rotate(pixel **matrix, int height, int width, int n_rot)
{
	int i, j;	
	pixel **new_mat;
	
	switch (n_rot) {
	
	case 3: 
		new_mat = allocate_matrix(width, height);
		
		for(i = 0; i < height; i++) {
			for (j = 0; j < width; j++) {
				new_mat[width - j - 1][i] = matrix[i][j];
			}
		}
		
		break;
	
	case 2: 
		new_mat = allocate_matrix(height, width);
		
		for(i = 0; i < height; i++) {
			for (j = 0; j < width; j++) {
				new_mat[height - i - 1][width - j - 1] = matrix[i][j];
			}
		}

		break;
		
	case 1:	
		new_mat = allocate_matrix(width, height);	
		
		for(i = 0; i < height; i++) {
			for (j = 0; j < width; j++) {
				new_mat[j][height - i - 1] = matrix[i][j];
			}
		}

		break;
	}
	
	deallocate_matrix(matrix, height);

	return new_mat;
}

void fill(pixel **matrix, int height, int width, int start_col, int start_line,
	  int or, int og, int ob,  int r, int g, int b)
		   
{
	matrix[start_line][start_col].r = r;
	matrix[start_line][start_col].g = g;
	matrix[start_line][start_col].b = b;
	
	if (start_line - 1 >= 0 && 
	    matrix[start_line - 1][start_col].r == or &&
	    matrix[start_line - 1][start_col].g == og &&
	    matrix[start_line - 1][start_col].b == ob) { 
		
		fill(matrix, height, width, start_col, start_line - 1,
		     or, og, ob, r, g, b);
	}
	if (start_line + 1 < height && 
	    matrix[start_line + 1][start_col].r == or &&
	    matrix[start_line + 1][start_col].g == og &&
	    matrix[start_line + 1][start_col].b == ob) { 
		
		fill(matrix, height, width, start_col, start_line + 1,
		     or, og, ob, r, g, b);
	}
	if (start_col - 1 >= 0 &&
	    matrix[start_line][start_col - 1].r == or &&
	    matrix[start_line][start_col - 1].g == og &&
	    matrix[start_line][start_col - 1].b == ob) { 
		
		fill(matrix, height, width, start_col -1, start_line , 
		     or, og, ob, r, g, b);
	}
	if (start_col + 1 < width && 
	    matrix[start_line][start_col + 1].r == or &&
	    matrix[start_line][start_col + 1].g == og &&
	    matrix[start_line][start_col + 1].b == ob) { 
		
		fill(matrix, height, width, start_col + 1, start_line,
		     or, og, ob, r, g, b);
	}
}


int main(void) 
{
	int op, is_read = 0;
	int width, height;
	int start_col, start_line, end_col, end_line;
	int new_width, new_height;  
	int start_line_fill, start_col_fill, r_fill, g_fill, b_fill; 
	int start_line_colour, start_col_colour, end_line_colour, end_col_colour;
	int r_colour, g_colour, b_colour; 
	int n_iter,n_rot;
	int aux;
	pixel **matrix;

	while(1) {	
	
	scanf("%d", &op);
	
	switch (op) {
	
	case 1:  //initialize matrix
		if (is_read == 0) {
			scanf("%d %d", &width, &height);
		
			if (width < 1 || width > 1024 || height < 1 || height > 1024){ 
				fprintf(stderr, "%d", EINVAL);
				exit(EXIT_FAILURE);	
			}
		
			matrix = get_matrix(height, width);
			is_read = 1;
	
		} else {
			deallocate_matrix(matrix, height);
			scanf("%d" "%d", &width, &height);

			if (width < 1 || width > 1024 || height < 1 || height > 1024){
				fprintf(stderr, "%d", EINVAL);
				exit(EXIT_FAILURE);
			}

			matrix = get_matrix(height, width);
		}

		break;
		
	case 2: //crop
		if (is_read) {
			scanf("%d %d", &start_col, &start_line);
			scanf("%d %d", &end_col, &end_line);
			
			if ((start_line >= 0 && end_line >= start_line && 
			     height > end_line) &&
			    (start_col >= 0 && end_col >= start_col && 
			     width > end_col)) {		
		
						
				matrix = crop(matrix, height, start_col, start_line,
					      end_col, end_line);
				
				height = end_line - start_line + 1;
				width =  end_col - start_col + 1;
			} else {
				fprintf(stderr, "%d", EINVAL);
   				deallocate_matrix(matrix, height);
				exit(EXIT_FAILURE);
			}
		} else {
			fprintf(stderr, "%d", EPERM);
			exit(EXIT_FAILURE);
		}

		break;
	
	case 3: //resize
		if (is_read) {
			scanf("%d %d", &new_width, &new_height);

			if (new_width < 1 || new_width > 1024) {  
				fprintf(stderr, "%d", EINVAL);
				deallocate_matrix(matrix, height);
				exit(EXIT_FAILURE);
			}
			if (new_height < 1 || new_height > 1024) {
				fprintf(stderr, "%d", EINVAL);
   				deallocate_matrix(matrix, height);
				exit(EXIT_FAILURE);
			}
		
			matrix = resize(matrix, height, width, new_height, new_width);
			height = new_height;
			width = new_width;
		} else {
			fprintf(stderr, "%d", EPERM);
			exit(EXIT_FAILURE);
		}
 		
		break;
	
	case 4: //colour
		if (is_read) {
			scanf("%d %d %d %d %d %d %d",  
			      &start_col_colour, &start_line_colour,
			      &end_col_colour, &end_line_colour,
			      &r_colour, &g_colour, &b_colour);
			
			if (r_colour < 0 || r_colour > 255 || 
			    g_colour < 0 || g_colour > 255 ||
		       	    b_colour < 0 || b_colour > 255) {
	 
				fprintf(stderr, "%d", EINVAL);
				deallocate_matrix(matrix, height);
				exit(EXIT_FAILURE);
			}				
		
			if ((start_line_colour >= 0 && 
			     end_line_colour >= start_line_colour && 
			     height > end_line_colour) &&
			    (start_col_colour >= 0 && 
			     end_col_colour >= start_col_colour && 
			     width > end_col_colour)) {
			
				colour(matrix, r_colour, g_colour, b_colour,
				       start_col_colour, start_line_colour,
				       end_col_colour, end_line_colour);
	 		} else {
				fprintf(stderr, "%d", EINVAL);
				deallocate_matrix(matrix, height);
				exit(EXIT_FAILURE);
			}
		} else {
			fprintf(stderr, "%d", EPERM);
			exit(EXIT_FAILURE);
		}

		break;
	
	case 5: //blur
 		if (is_read) {
			scanf("%d", &n_iter);
	
			if (n_iter < 0 || n_iter > 2000) {
				fprintf(stderr, "%d", EINVAL);
				deallocate_matrix(matrix, height);
				exit(EXIT_FAILURE);
			}	
			
		 	matrix = blur(matrix, height, width, n_iter);
		} else {
			fprintf(stderr, "%d", EPERM);
			exit(EXIT_FAILURE);
		}
	
		break;
		
	case 6: //rotate
		if (is_read) {
			scanf("%d", &n_rot);			
			
			if (n_rot < 1 || n_rot > 3) {
				fprintf(stderr, "%d", EINVAL);
				deallocate_matrix(matrix, height);
				exit(EXIT_FAILURE);
			}	
			
		 	matrix = rotate(matrix, height, width, n_rot); 		
			if (n_rot != 2) {
				aux = height;
				height = width;
				width = aux;
			}
		} else {
			fprintf(stderr, "%d", EPERM);
			exit(EXIT_FAILURE);
		}
	
		break;
		
	case 7: //fill
		if (is_read) {
			scanf("%d %d %d %d %d", 
			      &start_col_fill, &start_line_fill,
			      &r_fill, &g_fill, &b_fill);
			
			if (start_line_fill < 0 || start_line_fill >= height ||
			    start_col_fill < 0 || start_col_fill  >= width) {
				fprintf(stderr, "%d", EINVAL);
				deallocate_matrix(matrix, height);
				exit(EXIT_FAILURE);
			}		
		
			if (r_fill < 0 || r_fill > 255 || 
			    g_fill < 0 || g_fill > 255 || 
			    b_fill < 0 || b_fill > 255) { 
				fprintf(stderr, "%d", EINVAL);
	 			deallocate_matrix(matrix, height);
				exit(EXIT_FAILURE);
			}	

			fill(matrix, height, width, 
			     start_col_fill, start_line_fill,
			     matrix[start_line_fill][start_col_fill].r,
			     matrix[start_line_fill][start_col_fill].g, 
			     matrix[start_line_fill][start_col_fill].b,
			     r_fill, g_fill, b_fill);	
		} else {
			fprintf(stderr, "%d", EPERM);
			exit(EXIT_FAILURE);
		}

		break;
	
	case 8: //print
		if (is_read) {
			printf("%d %d\n", width, height);
			print_matrix(matrix, height, width);
		}
		else {
			fprintf(stderr, "%d", EPERM);
			exit(EXIT_FAILURE);
		}

		break;
	
	case 0: //exit
		if (is_read) {
			deallocate_matrix(matrix, height);		
			return 0;
		}
		else {	
			return 0;
		}
	
		break;
	
	default:
	 	fprintf(stderr, "%d", EPERM);
		
		if(is_read) {			
		deallocate_matrix(matrix, height);		
		}
		
		exit(EXIT_FAILURE);
	}
	}
	return 0;
}
