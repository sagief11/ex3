/******************
Name:
ID:
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define addOne  1
#define addAll  2
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7


int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};
typedef struct {
    int value;
    int idx;
} Max;
int currentDayIdx = 0;

void printMenu(){
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}

void init3DArray() {
    for (int dayIdx = 0; dayIdx < DAYS_IN_YEAR; dayIdx++) {
        for (int brandIdx = 0; brandIdx < NUM_OF_BRANDS; brandIdx++) {
            for (int typeIdx = 0; typeIdx < NUM_OF_TYPES; typeIdx++) {
              cube[dayIdx][brandIdx][typeIdx] = -1;
            }
        }
    }
}

void initializeArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        arr[i] = 0;
}

int isSelectedValidBrand() {
    int brandIdx;

    scanf(" %d", &brandIdx);
    if (!(0 <= brandIdx && brandIdx < NUM_OF_BRANDS)) {
        printf("This brand is not valid\n");
        return -1;
    }
    return brandIdx;
}

void printBrandsWithNoData(int userSelectedBrand[], int size) {
    printf("No data for brands");
    for (int brandIdx = 0; brandIdx < size; brandIdx++) {
        if (userSelectedBrand[brandIdx] == -1) {
            printf(" %s", brands[brandIdx]);
        }
    }
    printf("\nPlease complete the data\n");
}

void addDaySalesForAllBrands() {
    int userSelectedBrand[NUM_OF_BRANDS];
    int brandsCounter = NUM_OF_BRANDS, sum, userSelecedBrand;
    initializeArray(userSelectedBrand, NUM_OF_BRANDS);

    while (brandsCounter) {
        printBrandsWithNoData(userSelectedBrand, NUM_OF_BRANDS);
        userSelecedBrand = isSelectedValidBrand();
        if (userSelecedBrand == -1) {
            continue;
        }
        if (!userSelectedBrand[userSelecedBrand]) {
            --brandsCounter;
        }
        userSelectedBrand[userSelecedBrand] = 1;
        for (int typeIdx = 0; typeIdx < NUM_OF_TYPES; typeIdx++) {
            scanf("%d", &sum);
            cube[currentDayIdx][userSelecedBrand][typeIdx] = sum;
        }
    }
    currentDayIdx++;
}

int calculateTotalSales(int day, int brandSales[], int typesSales[]) {
    int totalSum = 0;
    for (int brandIdx = 0; brandIdx < NUM_OF_BRANDS; brandIdx++) {
        for (int typeIdx = 0; typeIdx < NUM_OF_TYPES; typeIdx++) {
            if (cube[day][brandIdx][typeIdx] > 0) {
                totalSum += cube[day][brandIdx][typeIdx];
                brandSales[brandIdx] += cube[day][brandIdx][typeIdx];
                typesSales[typeIdx] += cube[day][brandIdx][typeIdx];
            }
        }
    }
    return totalSum;
}

Max findMax(int arr[], int size) {
    Max max;
    max.idx = max.value = 0;

    for (int idx = 0; idx < size; idx++) {
        if (arr[idx] > max.value) {
            max.value = arr[idx];
            max.idx = idx;
        }
    }
    return max;
}

void printTotalSalesStatsForSelectedDay(int dayIdx) {
    int brandSales[NUM_OF_BRANDS], typesSales[NUM_OF_TYPES];
    Max maxSale;
    int totalSum = 0;
    initializeArray(brandSales, NUM_OF_BRANDS);
    initializeArray(typesSales, NUM_OF_TYPES);

    --dayIdx;
    for (int brandIdx = 0; brandIdx < NUM_OF_BRANDS; brandIdx++) {
        for (int typeIdx = 0; typeIdx < NUM_OF_TYPES; typeIdx++) {
            if (cube[dayIdx][brandIdx][typeIdx] > 0) {
                totalSum += cube[dayIdx][brandIdx][typeIdx];
                brandSales[brandIdx] += cube[dayIdx][brandIdx][typeIdx];
                typesSales[typeIdx] += cube[dayIdx][brandIdx][typeIdx];
            }
        }
    }
    printf("The sales total was %d\n", totalSum);
    maxSale = findMax(brandSales, NUM_OF_BRANDS);
    printf("The best sold brand with %d sales was %s\n", maxSale.value, brands[maxSale.idx]);
    maxSale = findMax(typesSales, NUM_OF_TYPES);
    printf("The best sold type with %d sales was %s\n", maxSale.value, types[maxSale.idx]);
}

void printDailyStats() {
    int day;

    printf("What day would you like to analyze?\n");
    scanf(" %d", &day);
    while (day > currentDayIdx) {
        printf("Please enter a valid day.\n"
               "What day would you like to analyze?\n");
        scanf(" %d", &day);
    }
    printf("In day number %d:\n", day);
    printTotalSalesStatsForSelectedDay(day);
}

void printAllData() {
    for (int brandIdx = 0; brandIdx < NUM_OF_BRANDS; brandIdx++) {
        printf("Sales for %s:\n", brands[brandIdx]);
        for (int dayIdx = 0; dayIdx < currentDayIdx; dayIdx++) {
            if (cube[dayIdx][brandIdx][0] == -1) {
                continue;
            }
            printf("Day %d-", dayIdx + 1);
            for (int typeIdx = 0; typeIdx < NUM_OF_TYPES; typeIdx++) {
                printf( " %s: %d", types[typeIdx], cube[dayIdx][brandIdx][typeIdx]);
            }
            printf("\n");
        }
    }
}

void printOverAll() {
    int daysSales[DAYS_IN_YEAR], brandSales[NUM_OF_BRANDS], typesSales[NUM_OF_TYPES];
    Max maxSale;

    initializeArray(daysSales, DAYS_IN_YEAR);
    initializeArray(brandSales, NUM_OF_BRANDS);
    initializeArray(typesSales, NUM_OF_TYPES);

    for (int dayIdx = 0; dayIdx < currentDayIdx; dayIdx ++) {
        for (int brandIdx = 0; brandIdx < NUM_OF_BRANDS; brandIdx++) {
            for (int typeIdx = 0; typeIdx < NUM_OF_TYPES; typeIdx++) {
                if (cube[dayIdx][brandIdx][typeIdx] > 0) {
                    daysSales[dayIdx] += cube[dayIdx][brandIdx][typeIdx];
                    brandSales[brandIdx] += cube[dayIdx][brandIdx][typeIdx];
                    typesSales[typeIdx] += cube[dayIdx][brandIdx][typeIdx];
                }
            }
        }
    }
    maxSale = findMax(brandSales, NUM_OF_BRANDS);
    printf("The best-selling brand overall is %s: %d$\n", brands[maxSale.idx], maxSale.value);
    maxSale = findMax(typesSales, NUM_OF_TYPES);
    printf("The best-selling type of car is %s: %d$\n", types[maxSale.idx], maxSale.value);
    maxSale = findMax(daysSales, DAYS_IN_YEAR);
    printf("The most profitable day was day number %d: %d$\n", maxSale.idx + 1, maxSale.value);
}

void printAverageDeltaMetrics() {
    float daysSales[NUM_OF_BRANDS][DAYS_IN_YEAR];
    float delta;
    float previousNum;

    for (int brandIdx = 0; brandIdx < NUM_OF_BRANDS; brandIdx++)
        for (int dayIdx = 0; dayIdx < currentDayIdx; dayIdx ++)
            daysSales[brandIdx][dayIdx] = 0;

    for (int dayIdx = 0; dayIdx < currentDayIdx; dayIdx ++) {
        for (int brandIdx = 0; brandIdx < NUM_OF_BRANDS; brandIdx++) {
            for (int typeIdx = 0; typeIdx < NUM_OF_TYPES; typeIdx++) {
                if (cube[dayIdx][brandIdx][typeIdx] > 0) {
                    daysSales[brandIdx][dayIdx] += cube[dayIdx][brandIdx][typeIdx];
                }
            }
        }
    }

    for (int brandIdx = 0; brandIdx < NUM_OF_BRANDS; brandIdx++) {
        previousNum = daysSales[brandIdx][0];
        delta = 0;
        for (int dayIdx = 1; dayIdx < currentDayIdx; dayIdx ++) {
            delta += (daysSales[brandIdx][dayIdx] - previousNum);
            previousNum = daysSales[brandIdx][dayIdx];
        }
        if (delta < 0)
            delta = 0;
        printf("Brand: %s, Average Delta: %f\n", brands[brandIdx], delta / (currentDayIdx - 1.0));
    }
}

int main() {
    int choice;
    init3DArray(cube);

    printMenu();
    scanf("%d", &choice);
    while(choice != done){
        switch(choice){
            case addOne:
                //...
                break;
            case addAll:
                addDaySalesForAllBrands();
                break;
            case stats:
                printDailyStats();
                break;
            case print:
                printAllData();
                break;
            case insights:
                printOverAll();
                break;
            case deltas:
                printAverageDeltaMetrics();
                break;

            default:
                printf("Invalid input\n");
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}
