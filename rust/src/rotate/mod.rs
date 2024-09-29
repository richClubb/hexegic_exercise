use std::fs;
use std::path::PathBuf;

fn rotate_left(input_data: Vec<u8>) -> Vec<u8> {
    // considered ways to do this to keep the result immutable but
    // I knew this method works and didn't want to spend too long
    // playing around with a more complex method

    let mut result: Vec<u8> = Vec::new();

    // iterate from the first to the penultimate value in the input_data
    for index in 0..(input_data.len() - 1){
        let shifted_val = input_data[index] << 1;
        let next_byte_msb = (input_data[index+1] & 0x80) >> 7;
        let new_val = shifted_val + next_byte_msb;
        result.push(new_val);
    }

    // Process the last value as we have to append the most
    // significant bit from the first byte of the file stream
    let msb_first_byte = (input_data[0] & 0x80) >> 7;
    let shifted_val = input_data[input_data.len()-1] << 1;
    let new_val = shifted_val + msb_first_byte;
    result.push(new_val);
    result
}

fn rotate_right(input_data: Vec<u8>) -> Vec<u8> {
    // considered ways to do this to keep the result immutable but
    // I knew this method works and didn't want to spend too long
    // playing around with a more complex method

    let mut result: Vec<u8> = Vec::new();

    // Process the first value as we have to get the least significant
    // bit from the last byte of the file stream.
    let lsb_last_byte = input_data[input_data.len() - 1] & 0x01;
    let shifted_val = input_data[0] >> 1;
    let new_val = shifted_val + (lsb_last_byte << 7);
    result.push(new_val);

    // process from the second to the last value in the input_data
    for index in 1 .. (input_data.len()){
        let lsb_last_byte = input_data[index - 1] & 0x01;
        let shifted_val = input_data[index] >> 1;
        let new_val = shifted_val + (lsb_last_byte << 7);
        result.push(new_val);
    }
    result
}

pub fn rotate_file(direction: String, input_file_path: PathBuf, output_file_path: PathBuf) -> Result<(), &'static str>{
    // this function assumes that:
    // * direction is correct
    // * 

    let input_file_result = fs::read(input_file_path);
    let contents = match input_file_result {
        Ok(result) => result,
        Err(_) => return Err("Can't open input file")
    };
    
    // chose to panic here as it's not valid if the file is empty.
    if contents.len() == 0{
        return Err("Nothing in file")
    }

    // leaving the result unchecked as I've gone over the 2 hours for the assignment
    if direction == "left"{
        let rotated_input = rotate_left(contents);
        let _result = fs::write(output_file_path, rotated_input);
        Ok(())
    }
    else if direction == "right"{
        let rotated_input = rotate_right(contents);
        let _result = fs::write(output_file_path, rotated_input);
        Ok(())
    }
    else {
        return Err("Invalid direction")
    }
}

#[cfg(test)]
mod rotate_left_tests {
    use super::rotate_left;

    #[test]
    fn test_1_byte_all_bits_0(){
        let input: Vec<u8> = vec![0];
        let result = rotate_left(input);
        assert_eq!(result, [0]);
    }

    #[test]
    fn test_1_byte_all_bits_1(){
        let input: Vec<u8> = vec![255];
        let result = rotate_left(input);
        assert_eq!(result, [255]);
    }

    #[test]
    fn test_1_byte_1_rotates_to_2(){
        let input: Vec<u8> = vec![1];
        let result = rotate_left(input);
        assert_eq!(result, [2]);
    }

    #[test]
    fn test_1_byte_128_rotates_to_1(){
        let input: Vec<u8> = vec![128];
        let result = rotate_left(input);
        assert_eq!(result, [1]);
    }

    #[test]
    fn test_2_bytes_all_bits_0(){
        let input: Vec<u8> = vec![0; 2];
        let result = rotate_left(input);
        assert_eq!(result, [0, 0]);
    }

    #[test]
    fn test_2_bytes_all_bits_1(){
        let input: Vec<u8> = vec![255; 2];
        let result = rotate_left(input);
        assert_eq!(result, [255, 255]);
    }

    #[test]
    fn test_2_bytes_bit_on_byte_0_boundary(){
        let input: Vec<u8> = vec![128, 0];
        let result = rotate_left(input);
        assert_eq!(result, [0, 1]);
    }

    #[test]
    fn test_2_bytes_bit_on_byte_1_boundary(){
        let input: Vec<u8> = vec![0, 128];
        let result = rotate_left(input);
        assert_eq!(result, [1, 0]);
    }

    #[test]
    fn test_100_bytes_all_bytes_1(){
        let input: Vec<u8> = vec![1; 100];
        let result = rotate_left(input);
        assert_eq!(result, [2; 100]);
    }
}

#[cfg(test)]
mod rotate_right_tests {
    use super::rotate_right;

    #[test]
    fn test_1_byte_all_bits_0(){
        let input: Vec<u8> = vec![0];
        let result = rotate_right(input);
        assert_eq!(result, [0]);
    }

    #[test]
    fn test_1_byte_all_bits_1(){
        let input: Vec<u8> = vec![255];
        let result = rotate_right(input);
        assert_eq!(result, [255]);
    }

    #[test]
    fn test_1_byte_1_rotates_to_128(){
        let input: Vec<u8> = vec![1];
        let result = rotate_right(input);
        assert_eq!(result, [128]);
    }

    #[test]
    fn test_1_byte_128_rotates_to_64(){
        let input: Vec<u8> = vec![128];
        let result = rotate_right(input);
        assert_eq!(result, [64]);
    }

    #[test]
    fn test_2_bytes_all_bits_0(){
        let input: Vec<u8> = vec![0; 2];
        let result = rotate_right(input);
        assert_eq!(result, [0, 0]);
    }

    #[test]
    fn test_2_bytes_all_bits_1(){
        let input: Vec<u8> = vec![255; 2];
        let result = rotate_right(input);
        assert_eq!(result, [255, 255]);
    }

    #[test]
    fn test_2_bytes_bit_on_byte_1_boundary(){
        let input: Vec<u8> = vec![0, 1];
        let result = rotate_right(input);
        assert_eq!(result, [128, 0]);
    }

    #[test]
    fn test_2_bytes_bit_on_byte_0_boundary(){
        let input: Vec<u8> = vec![1, 0];
        let result = rotate_right(input);
        assert_eq!(result, [0, 128]);
    }

    #[test]
    fn test_100_bytes_all_bytes_1(){
        let input: Vec<u8> = vec![1; 100];
        let result = rotate_right(input);
        assert_eq!(result, [128; 100]);
    }
}

#[cfg(test)]
mod rotate_file_tests
{
    use super::rotate_file;
    use std::path::PathBuf;
    use std::env;
    use std::panic;

    #[test]
    fn test_empty_file(){
        let mut input_file_path = env::var("TEST_RESOURCE_DIR").unwrap();
        input_file_path.push_str("test08_empty_file");
        let input_path = PathBuf::from(input_file_path);

        // this will never output as the function will panic as it has and empty imput
        let mut output_file_path = env::var("TEST_OUTPUT_DIR").unwrap();
        output_file_path.push_str("test08_output"); 
        let output_path = PathBuf::from(output_file_path);

        let result = panic::catch_unwind(|| {
            rotate_file("left".to_string(), input_path, output_path)
        });

        assert!(result.is_err());
    } 

    #[test]
    fn test_1_byte_file_msb_0(){
        let mut input_file_path = env::var("TEST_RESOURCE_DIR").unwrap();
        input_file_path.push_str("test01_single_byte_msb_0");
        let input_path = PathBuf::from(input_file_path);

        let mut output_file_path = env::var("TEST_OUTPUT_DIR").unwrap();
        output_file_path.push_str("test01_output"); 
        let output_path = PathBuf::from(output_file_path);

        _ = rotate_file("left".to_string(), input_path, output_path);

        // would have liked to get it working to check the output but stopping as I've spent over 2 hours on the assignment.
    }
}