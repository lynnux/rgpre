# rgpre #

A tool for `rg --pre`.

Read file to console, automatically recognize file encoding, include ansi, utf16le, utf16be, utf8. Currently output ansi as gbk for chinese text search.

Usage
=====
`rg --pre rgpre 中文`


中文说明
=====
rg有个问题是只能自动根据bom识别utf-8,utf16等，除此之外如gbk编码的文件，只能用`rg -Egbk`来搜索，这多少有点不方便。本工具根据rg提供的--pre参数说明编写而成，自动识别文件编码并把内容输出到console供rg搜索，支持编码有ansi，utf16le/be，utf8，目前ansi直接认为是gbk编码以方便中文搜索。参考了grepwin和ripgrep的源码。
输出到console会对rg速度有些影响，建议只在搜索中文时使用--pre参数。emacs里

调试
----
console窗口`rgpre file`就可以看到输出。

## 感谢 ##
ripgrep, grepwin，rust，encoding_rs，they are all awesome!
