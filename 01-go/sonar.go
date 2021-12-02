package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
)

func main() {
	var max, prev int = 0, -1
	file, err := os.Open("./input.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()
	scanner := bufio.NewScanner(file)

	for scanner.Scan() {
		i, err := strconv.Atoi(scanner.Text())
		if prev >= 0 && i > prev {
			max++
		}
		if err != nil {
			fmt.Println(err)
			os.Exit(2)
		}
		prev = i
	}
	fmt.Println(max)
}
