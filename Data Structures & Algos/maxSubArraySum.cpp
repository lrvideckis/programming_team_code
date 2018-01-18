int maxSubArraySum(vector<int> &arr) {
    int maximum = 0, temp = 0;
    for(int i = 0; i < arr.size(); i++) {
        temp += arr[i];
        if(temp < 0) temp = 0;
        if(temp > maximum) maximum = temp;
    }
    return maximum;
}
