const int Max = 1e6;
int seive[Max], mob[Max];

//returns 0 iff there exists a prime p s.t. n%(p^2)=0
//returns -1 iff n has an odd number of distinct prime factors
//returns 1 iff n has an even number of distinct prime factors
int mobius(int n) {
    int &temp = mob[n];
    if(temp != -2) return temp;
    int factors = 0, counter = 1, prev = 0;
    while(n > 1) {
        if(prev == seive[n]) counter++;
        else counter = 1;
        if(counter == 2) {
            return temp = 0;
        }
        prev = seive[n];
        n /= seive[n];
        factors++;
    }
    if(counter == 2) {
        return temp = 0;
    }
    return temp = (factors%2==0?1:-1);
}

void doSeive() {
    for (int i = 0; i < Max; ++i) {
        mob[i] = -2;
        seive[i] = i;
    }
    seive[0] = seive[1] = -1;
    for (int i = 2; i*i < Max; ++i) {
        if (seive[i] == i) {
            for (int j = i * i; j < Max; j += i) seive[j] = min(seive[j], i);
        }
    }
}
