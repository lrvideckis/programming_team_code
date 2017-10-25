//returns number of total digits in sequence 1, 2, 3, ... , upper; [inclusive] in O(1)
int numOfDigits(int upper) {
    if(upper < 1) return 0;
    int count = 0;
    int n = digits(upper)-1;
    if(n > 0) {
        count += 9*powl(10, n)*(n-1) + powl(2, n+3)*powl(5, n) + 1;
        count /= 9;
    }
    count += digits(upper) * (upper - powl(10, digits(upper)-1) + 1);
    return min(count, infll);
}
