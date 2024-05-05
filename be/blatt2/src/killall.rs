use std::process;
use std::io::{self, Write};
use std::fs::{self, read_dir};
use nix::unistd::Pid;
use nix::pty::SessionId;
use nix::sys::signal::kill;
use nix::sys::signal::Signal::*;

fn main() {
    let args: Vec<String> = std::env::args().collect();
    if args.len() < 2 {
        writeln!(io::stderr(), "Usage: {} <process_name>", args[0]).unwrap();
        process::exit(1);
    }

    let proc_name = &args[1];
    for entry in read_dir("/proc").unwrap() {
        let entry = entry.unwrap();
        let path = format!("/proc/{}/cmdline", entry.file_name().to_str().unwrap());
        if let Ok(contents) = fs::read_to_string(&path) {
            if contents.contains(proc_name) {
                let proc_int = SessionId::from(entry.file_name().to_str().unwrap().parse::<i32>().unwrap());
                match kill(proc_int, SIGKILL) {
                    Ok(_) => println!("Signal sent"),
                    Err(e) => writeln!(io::stderr(), "Error sending signal: {}", e).unwrap(),
                };
                break;
            }
        }
    }
}
