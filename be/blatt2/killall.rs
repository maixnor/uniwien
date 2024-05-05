
extern crate libc;
use std::fs;
use libc::kill;
use std::process;

fn main() {
    let args: Vec<String> = std::env::args().collect();
    if args.len() < 2 {
        process::exit(1);
    }

    let proc_name = &args[1];

    for entry in fs::read_dir("/proc").unwrap() {
        if let Ok(entry) = entry {
            if let Ok(pid_str) = entry.file_name().into_string() {
                let path = format!("/proc/{}/cmdline", pid_str);
                if let Ok(contents) = fs::read_to_string(&path) {
                    if contents.contains(proc_name) {
                        unsafe { kill (pid_str.parse::<i32>().unwrap(), libc::SIGKILL) };
                    }
                }
            }
        }
    }
}

