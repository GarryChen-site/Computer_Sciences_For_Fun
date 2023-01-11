use std::{thread, sync::atomic::AtomicU64, time::Duration};
use std::sync::atomic::Ordering::Relaxed;


fn get_x() -> u64 {
	static X: AtomicU64 = AtomicU64::new(0);
	let mut x = X.load(Relaxed);
	if x == 0 {
		x = calculate_x();
		X.store(x, Relaxed);
	}
	x
}

fn calculate_x() -> u64 {
	thread::sleep(Duration::from_secs(1));
	123
}

fn main() {
	dbg!(get_x());
	dbg!(get_x());
}