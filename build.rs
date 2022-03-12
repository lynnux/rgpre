extern crate cc;

fn main() {
    cc::Build::new()
        .cpp(true)
        .file("src/main.cpp")
        .compile("foo");

    println!("cargo:rustc-link-arg=foo.lib"); // vs2013可能需要这个，试了很多办法都失败
    println!("cargo:rerun-if-changed=build.rs");
    println!("cargo:rerun-if-changed=src/main");
}
