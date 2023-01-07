use std::{rc::Rc, thread, sync::Arc};


fn main() {
	// let a = Rc::new([1,2,3]);
	// let b = a.clone();

	// assert_eq!(a.as_ptr(), b.as_ptr()); // Same allocation

	// thread::spawn(move || dbg!(b));


let a = Arc::new([1, 2, 3]); 
let b = a.clone(); 

thread::spawn(move || dbg!(a)); 
thread::spawn(move || dbg!(b)); 
}
