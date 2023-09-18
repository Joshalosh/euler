
enum Power_Type
{
    Power_None,

    Power_Ones,
    Power_Tens,
    Power_Hundreds,
    Power_Thousands,

    Power_Unknown,
};

char *ones_buffer = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
char *teens_buffer = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
char *tens_buffer = {"error", "twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninety"};

static void StringifyNumber() {
    for (int num = 1; num <= 100; num++) {
        int mod;
        if (num < 10) {
            mod = 1;
        } else if ( num >= 10 && num < 100) {
            mod = 10;
        } else if (num >= 100 && num < 1000) {
            mod == 100;
        }
    }
}
