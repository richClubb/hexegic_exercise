package main

import (
  "fmt"
  "io/ioutil"
)

func main() {
  data, err := ioutil.ReadFile("../test_files/test01_single_byte_msb_0")
  if err != nil {
    fmt.Println("File reading error", err)
    return
  }

  fmt.Println("Contents of file:", data)
}