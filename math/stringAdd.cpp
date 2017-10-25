/*this function takes in 2 strings of just digits, and returns the sum of those numbers*/
string addString(string num1, string num2) {
    if (num2.size() > num1.size()) swap(num1, num2);
    int size1 = num1.size(), size2 = num2.size();
    vector<int16_t> digit1, digit2;
    for (int i = size1 - 1; i >= 0; i--) digit1.pb((int)num1[i] - 48);
    for (int i = size2 - 1; i >= 0; i--) digit2.pb((int)num2[i] - 48);
    for (int i = size1 - size2 - 1; i >= 0; i--) digit2.pb(0);
    bool carry = false;
    vector<int16_t> finalNum;
    for (int i = 0; i < size1; i++) {
        if (!carry) {
            if (digit1[i] + digit2[i] >= 10) {
                carry = true;
                finalNum.pb(digit1[i] + digit2[i] - 10);
            } else {
                carry = false;
                finalNum.pb(digit1[i] + digit2[i]);
            }
        } else {
            if (digit1[i] + digit2[i] + 1 >= 10) {
                carry = true;
                finalNum.pb(digit1[i] + digit2[i] + 1 - 10);
            } else {
                carry = false;
                finalNum.pb(digit1[i] + digit2[i] + 1);
            }
        }
    }
    if (carry) {
        finalNum.pb(1);
    }
    string ans = "";
    for (int i = finalNum.size() - 1; i >= 0; i--)
        ans += (char)(finalNum[i] + '0');
    return ans;
}
