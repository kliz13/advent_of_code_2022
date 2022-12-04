package main

import (
    "bufio"
    "fmt"
    "os"
    "strings"
    "strconv"
)

func checkForError(e error) {
    if e != nil {
        panic(e)
    }
}

func convertStringToInt(s string) int {
    ret_int, err := strconv.Atoi(s)
    checkForError(err)

    return ret_int
}

func main() {
    var num_enclosed_pairs int = 0

    f, err := os.OpenFile("input_files/camp_assignments.txt", os.O_RDONLY, 0444)
    checkForError(err)

    fScanner := bufio.NewScanner(f)
    fScanner.Split(bufio.ScanLines)


    for fScanner.Scan() {

        // Read in a single line
        line := fScanner.Text()

        // Split the line into the two elves
        pair_assignments := strings.Split(line, ",")

        // Split each elf group into beginning and end sections
        pair1 := strings.Split(pair_assignments[0], "-")
        pair2 := strings.Split(pair_assignments[1], "-")

        // We currently have the pairs in strings; convert to ints
        elf1_1 := convertStringToInt(pair1[0])
        elf1_2 := convertStringToInt(pair1[1])
        elf2_1 := convertStringToInt(pair2[0])
        elf2_2 := convertStringToInt(pair2[1])

        if elf1_1 > elf2_1 { // pair2 start is less than pair1 start
            if elf1_2 <= elf2_2 {
                num_enclosed_pairs++
            }
        } else if elf1_1 < elf2_1 { // pair1 start is less than pair2 start
            if elf1_2 >= elf2_2 {
                num_enclosed_pairs++
            }
        } else { // pair1 start is the same as pair2 start; they must be enclosed
            num_enclosed_pairs++
        }
    }

    fmt.Println("Number of enclosed pairs: ", num_enclosed_pairs)

    f.Close()
}
