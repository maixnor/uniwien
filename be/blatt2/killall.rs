extern crate libc;

use std::fs;
use std::process;
use libc::{kill, pid_t};

fn main() {
    let args: Vec<String> = std::env::args().collect();
    if args.len() < 2 {
        process::exit(1);
    }

    let proc_name = &args[1];
    let mut pids_to_kill: Vec<pid_t> = Vec::new(); // Collect PIDs to kill

    for entry in fs::read_dir("/proc").unwrap() {
        if let Ok(entry) = entry {
            let pid_str = entry.file_name().into_string().unwrap_or_default();
            if let Ok(pid) = pid_str.parse::<pid_t>() {
                let path = format!("/proc/{}/cmdline", pid);
                if let Ok(contents) = fs::read_to_string(&path) {
                    if contents.contains(proc_name) {
                        pids_to_kill.push(pid); // Collect PIDs
                    }
                }
            }
        }
    }

    // Batch kill processes
    for &pid in &pids_to_kill {
        let result = unsafe { kill(pid, libc::SIGKILL) };
        if result == 0 {
            println!("Process {} killed successfully.", pid);
        } else {
            eprintln!("Error killing process {}", pid);
            process::exit(1);
        }
    }
}
