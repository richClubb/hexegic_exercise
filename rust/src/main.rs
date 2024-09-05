use clap::Parser;
use std::path::{Path, PathBuf};

use crate::rotate::rotate_file;
mod rotate;

#[derive(Parser)]
struct Cli {
    #[arg(help="The direction of rotation, either 'left' or 'right'.")]
    direction: String,

    #[arg(help="The path to the input file to rotate.")]
    input_path: PathBuf,

    #[arg(help="The path to output the rotated file.")]
    output_path: PathBuf,
}

fn check_direction(direction: &String){

    if (direction != "left") && (direction != "right"){
        panic!("Direction is not 'left' or 'right'. Can not rotate file.")
    }
}

fn check_input_file_path(input_file: &PathBuf){
    if Path::new(input_file).exists() == false {
        panic!("Input file does not exist")
    }
}

fn check_output_file_path(output_file: &PathBuf){

    let output_path = Path::new(output_file);

    let parent_path = output_path.parent();

    if parent_path != Some(Path::new("")) && parent_path.unwrap().exists() == false {
        panic!("Output path is invalid")
    }

    if Path::new(output_file).exists() == true {
        panic!("Output file exists")
    }
}

fn main() {
    let args = Cli::parse();

    // passing these as references as they do not need ownership inside the function
    check_direction(&args.direction);
    check_input_file_path(&args.input_path);
    check_output_file_path(&args.output_path);

    rotate_file(args.direction, args.input_path, args.output_path)
}
