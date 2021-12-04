#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define BITS_COUNT 12
#define XS_CAP 1024

long long xs[XS_CAP];
long long xs_cnt = 0;
bool xs_removed[XS_CAP];
size_t xs_sz = 0;


void part1() {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    long long bits[BITS_COUNT][2];
    long long gamma = 0, epsilon = 0;
    fp = fopen("./input.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    for(int i=0; i < BITS_COUNT; ++i){
         for(int j=0; j < 2; ++j){
             bits[i][j] = 0;
         }   
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        char *ptr;
        int64_t x = strtoll(line, &ptr, 2);
        for(int i = 0; i < BITS_COUNT; ++i) {
            bits[i][(x>>i)&1]++;
        }
    }
    for(int i = 0; i < BITS_COUNT; ++i) {
        if(bits[i][0] < bits[i][1]) {
            gamma |= 1<<i;
            epsilon &= ~(1<<i);
        } else if(bits[i][0] > bits[i][1]) {
            gamma &= ~(1<<i);
            epsilon |= 1<<i;
        } else {
           printf("unreachable\n");
        }
    }

    printf("Part 1: %lld\n", gamma*epsilon);

    fclose(fp);
    if (line)
        free(line);
}

void readXs() {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen("./input.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    xs_sz = 0;

    while ((read = getline(&line, &len, fp)) != -1) {
        char *ptr;
        int64_t x = strtoll(line, &ptr, 2);
        xs[xs_sz] = x;
        xs_removed[xs_sz] = false;
        xs_sz++;
    }

    xs_cnt = xs_sz;

    fclose(fp);
    if (line)
        free(line);
}

void BitOfXs(long long bit_number, long long *bits) {
    for(int j=0; j < 2; ++j){
        bits[j] = 0;
    }

    for(size_t i = 0; i < xs_sz; ++i) {
        if(!xs_removed[i]) {
            bits[(xs[i] >> bit_number)&1]++;
        }
    }
}

long long SearchValue(bool common) {  
    long long bit_number = BITS_COUNT - 1;
    long long bits[2];
    long long bit;

    for(int j = 0; j < XS_CAP; ++j) {
        xs_removed[j] = 0;
    }

    xs_cnt = xs_sz;
    while(xs_cnt > 1) {
        BitOfXs(bit_number, bits);
        for(size_t i = 0; i < xs_sz; ++i) {
            if(!xs_removed[i]){
                bit = (xs[i] >> bit_number)&1;
                if(common) {
                    if((bits[1] >= bits[0]) != (bit == 1)) {
                        xs_removed[i] = true;
                        xs_cnt--;
                    }
                } else {
                    if((bits[1] >= bits[0]) == (bit == 1)) {
                        xs_removed[i] = true;
                        xs_cnt--;
                    }
                }      
            }
        }
        bit_number--;
    }
    
    for(size_t i = 0; i < xs_sz; i++) {
        if(!xs_removed[i]) {
            return xs[i];
        }
    }

    return 0;
}

void part2() {
    readXs();
    long long  oxygen = SearchValue(true);
    long long  co2 = SearchValue(false);

    printf("Part2: %lld\n", co2*oxygen);
}

int main() {
    part1();
    part2();
    return 0;
}
