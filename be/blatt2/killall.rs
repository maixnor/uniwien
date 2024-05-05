use std::fs;
use std::io::{self, Read};
use libc::*;

fn main() -> io::Result<()> {
    let args: Vec<String> = std::env::args().collect();
    if args.len() < 2 {
        eprintln!("Usage: {} <process_name>", args[0]);
        std::process::exit(1);
    }
    let to_kill = &args[1];

    for entry in fs::read_dir("/proc")? {
        if let Ok(entry) = entry {
            let pid_file = entry.path().join("comm");
            if let Ok(mut file) = fs::File::open(&pid_file) {
                let mut cmdline = String::new();
                file.read_to_string(&mut cmdline)?;
                if cmdline.contains(to_kill) {
                    if let Some(pid_str) = entry.file_name().to_str() {
                        if let Ok(pid) = pid_str.parse::<i32>() {
                            unsafe { kill(pid, libc::SIGKILL) } ;
                        }
                    }
                }
            }
        }
    }

    Ok(())
}

