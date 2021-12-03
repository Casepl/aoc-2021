use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;


fn part2() {
    let mut fwd = 0;
    let mut depth = 0;
    let mut aim = 0;
    if let Ok(lines) = read_lines("./input.txt") {
        for line in lines {
            if let Ok(command) = line {
                let v: Vec<&str> = command.split(' ').collect();
                let value = v[1].parse::<i32>().unwrap();

                if v[0] == "up" {
                    aim -= value;
                } else if v[0] == "down" {
                    aim += value;  
                } else if v[0] == "forward"{
                    fwd += value;
                    depth += value*aim;
                } else {
                    aim += value;     
                }
            }
        }
    
        let answer: i128 = (fwd*depth) as i128;

        println!("Part2: {}", answer);
    }
}

fn part1() {
    let mut fwd = 0;
    let mut depth = 0;
    if let Ok(lines) = read_lines("./input.txt") {
        for line in lines {
            if let Ok(command) = line {
                let v: Vec<&str> = command.split(' ').collect();
                let value = v[1].parse::<i32>().unwrap();
                if v[0] == "up" {
                    depth -= value;
                } else if v[0] == "down" {
                    depth += value;
                } else if v[0] == "forward"{
                    fwd += value
                } else {
                    fwd -= value     
                }
            }
        }
        println!("Part1: {}", fwd*depth);
    }
}

fn main() {
    part1();
    part2();
}

fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where P: AsRef<Path>, {
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}