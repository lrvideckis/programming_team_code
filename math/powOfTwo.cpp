bool powOfTwo(int n) {
    if(n <= 0) return false;
    while(n > 1) {
        if(n%2 == 1) return false;
        n /= 2;
    }
    return true;
}
