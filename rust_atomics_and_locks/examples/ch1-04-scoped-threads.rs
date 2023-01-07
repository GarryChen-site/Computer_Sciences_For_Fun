use std::thread;

fn main() {
	// let numbers = vec![1,2,3];

	// thread::scope(|s| {
		// s.spawn(|| {
		// 	println!("length: {}", numbers.len());
		// });
		// s.spawn(|| {
		// 	for n in &numbers { 
		// 		println!("{n}");
		// 	}
		// });
		// s.spawn(|| {
		// 	numbers.push(1);
		//     });
		//     s.spawn(|| {
		// 	numbers.push(2); // Error!
		//     });
	// });

	// Shared Ownership
	// Statics
// 	static X: [i32; 3] = [1, 2, 3];

// thread::spawn(|| dbg!(&X));
// thread::spawn(|| dbg!(&X));

// Leaking
let x: &'static [i32; 3] = Box::leak(Box::new([1, 2, 3]));

thread::spawn(move || dbg!(x));
thread::spawn(move || dbg!(x));
}