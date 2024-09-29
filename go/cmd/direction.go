/*
Copyright © 2024 NAME HERE <EMAIL ADDRESS>

*/
package cmd

import (
	"fmt"

	"github.com/spf13/cobra"
)

// directionCmd represents the direction command
var directionCmd = &cobra.Command{
	Use:   "direction",
	Short: "Direction of rotation, either left or right",
	Long: ``,
	Run: func(cmd *cobra.Command, args []string) {
		fmt.Println("direction called")
	},
}

func init() {
	rootCmd.AddCommand(directionCmd)

	// Here you will define your flags and configuration settings.

	// Cobra supports Persistent Flags which will work for this command
	// and all subcommands, e.g.:
	// directionCmd.PersistentFlags().String("foo", "", "A help for foo")

	// Cobra supports local flags which will only run when this command
	// is called directly, e.g.:
	// directionCmd.Flags().BoolP("toggle", "t", false, "Help message for toggle")
}
