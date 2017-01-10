//
//  main.c
//  ADSA_Sem1_Slowest_Shortest_Path
//
//  Created by Anurag Gupta on 13/11/16.
//  Copyright © 2016 Anurag Gupta. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function prototype
int *slowest_shortest_path(const int rows, const int cols, const int *W);
void extend_shortest_path(const int rows, const int cols, int *L, const int *W);
void displayAdjMatrix(int rows, int cols, int *arr);

int main(int argc, const char * argv[]) {

    // Varialble declaration
    const int M = 5;
    const int N = 5;
    int *arrayWithShortestPath;
    int W[M*N];
    int i, j;
    
    /*
     Matrix Used
     { 0, 3, 8, 99, -4,
       99, 0, 99, 1, 7,
       99, 4, 0, 99, 99,
       2, 99, -5, 0, 99,
       99, 99, 99, 6, 0};
     */
    printf("==========================================");
    printf("\n---slowest all pair shortest path---\n");
    printf("==========================================");
    
    // Initialization of adjacency matix W
    printf("\nEnter the weight between vertices row-wise:\n");
    for(i = 0; i < M; i++){
        for(j = 0; j < N; j++){
            printf("weight between %d --> %d: ", i, j);
            scanf("%d", &W[i*M+j]);
        }
    }
    
    arrayWithShortestPath = (int *)malloc(sizeof(int));
    
    // Displaying initial adjacency matrix W
    printf("\nInitial Adjacency Matrix:\n");
    displayAdjMatrix(M, N, W);
    
    // Calling slowest_shortest_path procedure
    arrayWithShortestPath = slowest_shortest_path(M, N, W);
    
    // Displaying adjacency matrix containing the shortest path
    printf("\nAdjacency Matrix With Shortest Path:\n");
    displayAdjMatrix(M, N, arrayWithShortestPath);

    return 0;
}

// Function Definitions
int *slowest_shortest_path(const int rows, const int cols, const int *W) {
    int m, n, i, j;
    int *L;
    
    n = rows;
    
    // Allocating memory to array L
    L = (int *)malloc(sizeof(int) * (rows*cols));
    
    // Initializing L
    for(i = 0; i < rows; i++)
        for(j = 0; j < cols; j++)
            L[i*rows+j] = W[i*rows+j];

    for(m = 2; m <= n-1; m++) {
        extend_shortest_path(rows, cols, L, W);
        printf("\n---Matrix for m=%d---\n", m);
        displayAdjMatrix(rows, cols, L);
    }
    
    return L;
}

void extend_shortest_path(const int rows, const int cols, int *L, const int *W) {
    int n;
    int i, j, k;
    int *L_dash;
    
    n = rows;
    
    // Allocating memory to array L
    L_dash = (int *)malloc(sizeof(int) * (rows*cols));

    // Computing L_dash
    for(i = 0; i <= n-1; i++)
        for(j = 0; j <= n-1; j++) {
            L_dash[i*n+j] = 999;
            for(k = 0; k <= n-1; k++)
                L_dash[i*n+j] = fminf(L_dash[i*n+j], (L[i*n+k] + W[k*n+j]));
        }
    
    // Copying the computed data in returning buffer
    for(i = 0; i < rows; i++)
        for(j = 0; j < cols; j++)
            L[i*rows+j] = L_dash[i*rows+j];
}

void displayAdjMatrix(int rows, int cols, int *arr) {
    int i, j;
    
    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            printf("%3d\t", arr[i*rows+j]);
        }
        printf("\n");
    }
}