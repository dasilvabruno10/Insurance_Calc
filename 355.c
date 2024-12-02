//*********************************************************************************************************************************************************************
// Author: Bruno da Silva  
// Major: Computer Engineering  
//
// Verison: 05/8/2023 
// Module Name: Insurance Calculation Module 
// Component: Task Layer 
// Description of Module: Grabs patient’s insurance information based on the name, and calculates prices before and after insurance deductions. 
//
//**********************************************************************************************************************************************************************
// Input: Reads in insurance type and deductible from text file "insurance.txt" as well as patient information from text file "data.txt"  
// Output: Prints out patient's information (patient's name, patient's age, patient's gender, patients date of birth, and patient insurance) as well as an itemized bill after insuarance dedcutible is applied.
//***********************************************************************************************************************************************************************
//  
// CMSC 355-03
// Spring 2023
// Virginia Commonwealth University 
//
//************************************************************************************************************************************************************************
// Format of .txt files: 
// 
// Insurance.txt: 
// Plan A,100
// Plan B,150
// Plan C,200
// Plan D,250
//
// patient.txt: 
// John Doe,35,M,05/08/1988,750.
//*************************************************************************************************************************************************************************
//
//Command line input: ./a.out insurance.txt data.txt
//
//
//
//Included the required libraries

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INSURANCE_TYPES 4

// Struct to store patient info 
typedef struct {
    char name[50];
    int age;
    char gender;
    char dob[11];
    float total_amount_due;
} Patient;

// Struct to stor insurance info 
typedef struct {
    char name[50];
    float deductible;
} Insurance;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <insurance_file> <patient_file>\n", argv[0]);
        return 1;
    }

    // Read in insurance data from file
    FILE *insurance_file = fopen(argv[1], "r");
    if (insurance_file == NULL) {
        printf("Could not open insurance file.\n");
        return 1;
    }
    Insurance insurances[MAX_INSURANCE_TYPES];
    int num_insurances = 0;
    char line[100];
    while (fgets(line, sizeof(line), insurance_file) != NULL && num_insurances < MAX_INSURANCE_TYPES) {
        char *name = strtok(line, ",");
        float deductible = strtof(strtok(NULL, ","), NULL);
        if (name != NULL && deductible >= 0) {
            strcpy(insurances[num_insurances].name, name);
            insurances[num_insurances].deductible = deductible;
            num_insurances++;
        }
    }
    fclose(insurance_file);

    // Read in patient data from file and calculate itemized bill
    FILE *patient_file = fopen(argv[2], "r");
    if (patient_file == NULL) {
        printf("Could not open patient file.\n");
        return 1;
    }
    Patient patient;
    while (fscanf(patient_file, "%[^,],%d,%c,%[^,],%f\n", patient.name, &patient.age, &patient.gender, patient.dob, &patient.total_amount_due) != EOF) {
        float total_deductible = 0;
        printf("Patient name: %s\n", patient.name);
        printf("Age: %d\n", patient.age);
        printf("Gender: %c\n", patient.gender);
        printf("Date of Birth: %s\n", patient.dob);
        printf("Total Amount Due: $%.2f\n", patient.total_amount_due);
        printf("Itemized Bill:\n");
        for (int i = 0; i < num_insurances; i++) {
            float deductible = insurances[i].deductible;
            if (total_deductible + deductible <= patient.total_amount_due) {
                printf("\t%s deductible: $%.2f\n", insurances[i].name, deductible);
                total_deductible += deductible;
            }
        }
        float amount_paid = patient.total_amount_due - total_deductible;
        printf("Amount Paid by Insurance: $%.2f\n", total_deductible);
        printf("Amount Due from Patient: $%.2f\n\n", amount_paid);
    }
    fclose(patient_file);

    return 0;
}


