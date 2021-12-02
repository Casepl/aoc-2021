package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
)

func part1() {
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

func part2() {
	var answer int = 0

	file, err := os.Open("./input.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	scanner.Scan()
	a, err := strconv.Atoi(scanner.Text())
	if err != nil {
		fmt.Println(err)
		os.Exit(2)
	}
	scanner.Scan()
	b, err := strconv.Atoi(scanner.Text())
	if err != nil {
		fmt.Println(err)
		os.Exit(2)
	}
	scanner.Scan()
	c, err := strconv.Atoi(scanner.Text())
	if err != nil {
		fmt.Println(err)
		os.Exit(2)
	}
	for scanner.Scan() {
		d, err := strconv.Atoi(scanner.Text())

		if err != nil {
			fmt.Println(err)
			os.Exit(2)
		}
		if b+c+d > a+b+c {
			answer++
		}
		a = b
		b = c
		c = d
	}
	fmt.Println(answer)
}

func main() {
	part1()
	part2()
}
