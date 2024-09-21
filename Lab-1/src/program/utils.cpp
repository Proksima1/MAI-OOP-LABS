bool checkClear(int num){
    int prev = -1, now;
    while (num != 0){
        if (prev == -1){
            prev = num % 10;
        } else {
            now = num % 10;
            if (prev < now) {
                return false;
            }
            prev = now;
        }
        num /= 10;
    }
    return true;
}