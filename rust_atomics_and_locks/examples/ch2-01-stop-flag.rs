use std::{sync::atomic::AtomicBool, thread, time::Duration};
use std::sync::atomic::Ordering::Relaxed;

fn main() {
	static STOP: AtomicBool = AtomicBool::new(false);

	// Spawn a thread to do the work
	let background_thread = thread::spawn(|| {
		while !STOP.load(Relaxed) {
			some_work();
		}
	});

	// Use the main thread to listen for user input
	for line in std::io::stdin().lines() {
		match line.unwrap().as_str() {
			"help" => println!("commands: help, stop"),
			"stop" => break,
			cmd => println!("unknown command: {cmd:?}"),
		}
	}

	// Inform the background thread it needs to stop
	STOP.store(true, Relaxed);

	// Wait until the background thread finishes
	background_thread.join().unwrap();
}


fn some_work() {
	thread::sleep(Duration::from_millis(100));
    }