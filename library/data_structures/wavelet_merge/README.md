# Memory analysis

let n = size of input array, k = number of leaves

For merge sort tree: k = n, for wavelet tree: k = (maxv - minv)

depth | total memory for depth | big-O | explanation
--- | --- | --- | ---
0 | $\lceil n / 64 \rceil$ | 1 + n / 64 |
1 | 2 * $\lceil (n/2) / 64 \rceil$ | 2 + n / 64 |
2 | 4 * $\lceil (n/4) / 64 \rceil$ | 4 + n / 64 |
...
i | 2^i * $\lceil (n/2^i) / 64 \rceil$ | 2^i + n / 64 |
...
log(k) - 2 | k/4 * $\lceil (n/(k/4)) / 64 \rceil$ | k/4 + n / 64|
log(k) - 1 | k/2 * $\lceil (n/(k/2)) / 64 \rceil$ | k/2 + n / 64 |
log(k) | k * $\lceil (n/k) / 64 \rceil$ | k + n / 64 | memory = (n/k)>=64 ? n/64 : k

Sum of big-O:
- first part: 1 + 2 + 4 + ... + 2^i + ... + k <= 2*k
- second part: log(k) * n / 64
