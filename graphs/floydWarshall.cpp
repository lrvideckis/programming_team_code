for (int k = 0; k < n; k++){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (w[i][j] > w[i][k] + w[k][j]){
                w[i][j] = w[i][k] + w[k][j];
                prev[i][j] = k;
            }
        }
    }
}
