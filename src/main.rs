extern crate encoding_rs;
extern crate encoding_rs_io;

#[link(name = "foo")]
extern "C" {
    fn AutoDectUnicodeType(pBuffer: *const u8, cb: i32) -> i32;
}

fn main() -> std::io::Result<()> {
    use std::env;
    use std::fs::File;
    use std::io::Read;
    let args: Vec<String> = env::args().collect();
    if args.len() >= 2 {
        let mut file = File::open(&args[1].as_str())?;
        let metadata = std::fs::metadata(&args[1])?;
        let bytesread = metadata.len() as usize;
        let mut buf: Vec<u8> = Vec::with_capacity(bytesread);
        file.read_to_end(&mut buf)?;
        let type1 = unsafe { AutoDectUnicodeType(buf.as_ptr(), buf.len() as i32) };
        // println!("type:{}, bytesread:{}", type1, bytesread);

        // https://github.com/BurntSushi/ripgrep/blob/master/crates/searcher/src/searcher/mod.rs#L322
        use encoding_rs::{Encoding, GBK, UTF_16BE, UTF_16LE, UTF_8};
        use encoding_rs_io::DecodeReaderBytesBuilder;
        let mut decode_builder = DecodeReaderBytesBuilder::new();
        /*
           enum UnicodeType {
            AutoType = 0,
            Binary = 1,
            Ansi = 2,
            UnicodeLe = 3,
            UnicodeBe = 4,
            UTF8 = 5,
        }*/
        let encode: Option<&'static Encoding> = match type1 {
            0 => None,      // AutoType
            1 => None,      // Binary
            2 => Some(GBK), // ansi目前直接认为就是GBK
            3 => Some(UTF_16LE),
            4 => Some(UTF_16BE),
            5 => Some(UTF_8),
            _ => None,
        };
        let mut dest = Vec::new();
        let mut decoder = decode_builder
            .encoding(encode)
            .utf8_passthru(true)
            .strip_bom(true)
            .bom_override(true)
            .bom_sniffing(true)
            .build(buf.as_slice());
        decoder.read_to_end(&mut dest)?;
        use std::io::Write;
        std::io::stdout().write_all(dest.as_slice())?;
    } else {
        println!("usage: rgpre file");
    }
    Ok(())
}
