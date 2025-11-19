#include <stdio.h>
#include <stdlib.h>

int main() {
    float currentWeight, targetWeight, height, age;
    char sex, goal;
    int durationMonths;
    float calorieIntake, proteinIntake;
    float caloriesPerMeal;
    int meals;
    float diff;
    float BMR, TDEE;
    float activityMultiplier;

    FILE *file;

    printf("Fitness & Bodybuilding Assistant (Realistic)\n\n");

    file = fopen("fitness_data.txt", "r");
    if (file != NULL) {
        printf("Previous progress found:\n");
        char line[200];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);
        printf("\n-----------------------------------------\n\n");
    }

    printf("Enter your current weight (kg): ");
    scanf("%f", &currentWeight);

    printf("Enter your target weight (kg): ");
    scanf("%f", &targetWeight);

    printf("Enter your height (cm): ");
    scanf("%f", &height);

    printf("Enter your age: ");
    scanf("%f", &age);

    printf("Enter your sex (M/F): ");
    scanf(" %c", &sex);

    printf("How many meals do you eat per day (3-5): ");
    scanf("%d", &meals);
    if (meals < 3) meals = 3;
    if (meals > 5) meals = 5;

    printf("Do you want to gain muscle (G) or lose weight (L)? Enter G/L: ");
    scanf(" %c", &goal);

    diff = targetWeight - currentWeight;

    file = fopen("fitness_data.txt", "w");
    if (file == NULL) {
        printf("Error saving file!\n");
        return 1;
    }

    fprintf(file, "Fitness Progress Record\n\n");
    fprintf(file, "Current Weight: %.1f kg\n", currentWeight);
    fprintf(file, "Target Weight: %.1f kg\n", targetWeight);

    if (sex == 'M' || sex == 'm')
        BMR = 10 * currentWeight + 6.25 * height - 5 * age + 5;
    else
        BMR = 10 * currentWeight + 6.25 * height - 5 * age - 161;

    activityMultiplier = 1.3;
    TDEE = BMR * activityMultiplier;

    if (goal == 'G' || goal == 'g') {
        if (diff <= 0) {
            printf("\nYou already reached or exceeded your target.\n");
            fprintf(file, "Goal: Muscle Gain - Already achieved.\n");
            fclose(file);
            return 0;
        }

        durationMonths = (int)(diff / 1.5);

        if (sex == 'M' || sex == 'm')
            calorieIntake = TDEE + 400;
        else
            calorieIntake = TDEE + 300;

        if (calorieIntake > 3500) calorieIntake = 3500;

        if (sex == 'M' || sex == 'm')
            proteinIntake = targetWeight * 2.0;
        else
            proteinIntake = targetWeight * 1.8;

        caloriesPerMeal = calorieIntake / meals;

        printf("\nGoal: Muscle Gain\n");
        printf("Weight Gain Needed: %.1f kg\n", diff);
        printf("Estimated Time: %d months\n", durationMonths);
        printf("Daily Calories: %.0f kcal\n", calorieIntake);
        printf("Protein: %.1f g/day\n", proteinIntake);
        printf("Calories per meal (%d meals): %.0f kcal\n\n", meals, caloriesPerMeal);

        fprintf(file, "Goal: Muscle Gain\nWeight Gain Needed: %.1f kg\nEstimated Time: %d months\nDaily Calories: %.0f kcal\nProtein: %.1f g/day\nCalories per Meal: %.0f kcal\n",
		 diff, durationMonths, calorieIntake, proteinIntake, caloriesPerMeal);
    }

    else if (goal == 'L' || goal == 'l') {
        if (diff >= 0) {
            printf("\nYou are already below or at your target.\n");
            fprintf(file, "Goal: Weight Loss - Already reached.\n");
            fclose(file);
            return 0;
        }

        diff = -diff;
        durationMonths = (int)(diff / 3.0);

        TDEE = BMR * 1.3;

        if (sex == 'M' || sex == 'm')
            calorieIntake = TDEE - 700;
        else
            calorieIntake = TDEE - 500;

        if (calorieIntake < 1200) calorieIntake = 1200;

        if (sex == 'M' || sex == 'm')
            proteinIntake = currentWeight * 1.8;
        else
            proteinIntake = currentWeight * 1.6;

        caloriesPerMeal = calorieIntake / meals;

        printf("\nGoal: Weight Loss\n");
        printf("Weight Loss Needed: %.1f kg\n", diff);
        printf("Estimated Time: %d months\n", durationMonths);
        printf("Daily Calories: %.0f kcal\n", calorieIntake);
        printf("Protein: %.1f g/day\n", proteinIntake);
        printf("Calories per meal (%d meals): %.0f kcal\n\n", meals, caloriesPerMeal);

        fprintf(file, "Goal: Weight Loss\nWeight Loss Needed: %.1f kg\nEstimated Time: %d months\nDaily Calories: %.0f kcal\nProtein: %.1f g/day\nCalories per Meal: %.0f kcal\n",
		 diff, durationMonths, calorieIntake, proteinIntake, caloriesPerMeal);
    }

    else {
        printf("\nInvalid choice. Enter G or L.\n");
        fclose(file);
        return 0;
    }

    fprintf(file, "\nStay consistent and disciplined.\n");
    fclose(file);

    printf("\nProgress saved in 'fitness_data.txt'.\n");
    return 0;
    
}

