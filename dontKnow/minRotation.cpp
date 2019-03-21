// Lexicographically minimum rotation of a sequence
//
// Given a sequence s of length N, min_rotation(s, N) returns the start index
// of the lexicographically minimum rotation.
//
// Note: array s must be of length of at least 2 * N.
//
// Time complexity: O(N)

int min_rotation(int *s, int N) {
  for(int i=0;i<N;i++) s[N+i] = s[i];

  int a = 0;
  for(int b=0;b<N;b++) for(int i=0;i<N;i++) {
    if (a+i == b || s[a+i] < s[b+i]) { b += max(0, i-1); break; }
    if (s[a+i] > s[b+i]) { a = b; break; }
  }
  return a;
}
