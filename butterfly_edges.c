/******************************************************************************
  Title          : butterfly_edges.c
  Author         : Stewart Weiss
  Created on     : September 24, 2019
  Description    : Computes the forward cross-edges in a butterfly network
  Purpose        : To show that we can compute the edges without using
                   bitwise operations, but grossly inefficiently.
  Usage          : butterfly_edges  <order>
                     where <order> is the number of ranks minus 1
  Build with     : gcc -o butterfly_edges butterfly_edges.c -lm
  Modifications  :

  License        : Copyright 2019 Stewart Weiss

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

/* Comment out the line below to build a faster program. */
#define NOBITWISE

int main ( int argc, char* argv[])
{

    int i,j,k,m,n;

    char  endptr[255];
    					/* check args 	*/
    if ( argc != 2 ){
        fprintf( stderr, "usage: %s <order>\n", argv[0]);
        exit(1);
    }

    errno = 0;
    /* get order */
    k = strtol(argv[1], (char**) &endptr, 0);

    /* Check for error in buffersize */
    if (errno != 0 ) {
        perror("strtol");
        exit(1);
    }

    /* No negatives and nothing too large for the order */
    if ( ( k < 0 ) || ( k > 32 ) ) {
       printf( "The order is not in range.\n");
       exit(1);
    }

    long int columns = (long)pow(2,k);
    for ( i = 0; i < k; i++ ) {
        printf("\nEdges for rank  %d:\n", i);

#ifdef NOBITWISE
        /*  This is how to do it without using bitwise operators */
        n = (int)pow(2,k-i-1);
        m = 2*n;
        for ( j = 0; j < columns ; j++ ) {
            int temp = m*(j/m) + ( n * ((j/n + 1)%2)) + j%n;
            printf ("(%d,%d) => (%d,%d)\n", i,j,i+1, temp);
        }
#else
        /* and this uses bitwise operators */
        for ( j = 0; j < columns ; j++ ) {
            int temp = j ^ (1 << k-i-1);
            printf ("(%d,%d) => (%d,%d)\n", i,j,i+1, temp);
        }
#endif


    }
return 0;
}
