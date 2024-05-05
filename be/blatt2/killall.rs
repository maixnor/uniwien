use std::fs;
use std::process;
use std::collections::HashSet;
use std::os::unix::process::CommandExt;
use std::io::Error;

fn main() {
    let args: Vec<String> = std::env::args().collect();
    if args.len() < 2 {
        process::exit(1);
    }

    let proc_name = &args[1];
    let mut pids_to_kill: HashSet<u32> = HashSet::new();

    // Iterate over processes in /proc directory
    if let Ok(entries) = fs::read_dir("/proc") {
        for entry in entries {
            if let Ok(entry) = entry {
                if let Ok(pid_str) = entry.file_name().into_string() {
                    if let Ok(pid) = pid_str.trim().parse::<u32>() {
                        let cmdline_path = format!("/proc/{}/cmdline", pid);
                        if let Ok(contents) = fs::read_to_string(&cmdline_path) {
                            if contents.contains(proc_name) {
                                pids_to_kill.insert(pid);
                            }
                        }
                    }
                }
            }
        }
    }

    // Kill processes in batch
    for &pid in &pids_to_kill {
        if let Err(err) = kill_process(pid) {
            eprintln!("Error killing process {}: {}", pid, err);
            process::exit(1);
        } else {
            println!("Process {} killed successfully.", pid);
        }
    }
}

fn kill_process(pid: u32) -> Result<(), Error> {
    // Use the `kill` syscall to terminate the process
    let result = unsafe { libc::kill(pid as libc::pid_t, libc::SIGKILL) };
    if result == 0 {
        Ok(())
    } else {
        Err(Error::last_os_error())
    }
}

