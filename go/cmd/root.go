package cmd

import (
	"fmt"
	"os"

	"github.com/spf13/cobra"

	"hexegic_example/rotate"
)

var rootCmd = &cobra.Command{
	Use:   "rotate",
	Short: "Rotates a bitstream from a file into another file",
	Long:  `An exercise for Hexegic`,
	Args:  cobra.MatchAll(cobra.MinimumNArgs(3), cobra.MaximumNArgs(3)),
	Run: func(cmd *cobra.Command, args []string) {
		fmt.Println(args)
		rotate.Rotate_file("left")
	},
}

func Execute() {
	if err := rootCmd.Execute(); err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
}
