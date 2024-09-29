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

fn check_direction(direction: &String) -> Result<(), &'static str>{

    if (direction != "left") && (direction != "right"){
        return Err("Invalid direction")
    }
    return Ok(())
}

fn check_input_file_path(input_file: &PathBuf) -> Result<(), &'static str>{
    if Path::new(input_file).exists() == false {
        return Err("Invalid input file path")
    }
    return Ok(())
}

fn check_output_file_path(output_file: &PathBuf) -> Result<(), &'static str>{

    let output_path = Path::new(output_file);

    let parent_path = output_path.parent();

    if parent_path != Some(Path::new("")) && parent_path.unwrap().exists() == false {
        return Err("Output path is invalid");
    }

    if Path::new(output_file).exists() == true {
        return Err("Output file exists")
    }

    return Ok(())
}

fn main() -> Result<(), &'static str> {
    let args = Cli::parse();

    // passing these as references as they do not need ownership inside the function
    match check_direction(&args.direction) {
        Ok(()) => (),
        Err(error) => return Err(error)
    }

    match check_input_file_path(&args.input_path){
        Ok(()) => (),
        Err(error) => return Err(error)
    }

    match check_output_file_path(&args.output_path){
        Ok(()) => (),
        Err(error) => return Err(error)
    }

    match rotate_file(args.direction, args.input_path, args.output_path){
        Ok(()) => (),
        Err(error) => return Err(error)
    }

    return Ok(())
}
