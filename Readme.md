# rgpre #

A tool for `rg --pre`.

Read file to console, automatically recognize file encoding, include ansi, utf16le, utf16be, utf8. Currently output ansi as gbk for chinese text search.

Usage
=====
`rg --pre rgpre 中文`


中文说明
=====
rg有个问题是只能自动根据bom识别utf-8,utf16等，除此之外如gbk编码的文件，只能用`rg -Egbk`来搜索，这多少有点不方便。本工具根据rg提供的--pre参数说明编写而成，自动识别文件编码并把内容输出到console供rg搜索，支持编码有ansi，utf16le/be，utf8，目前ansi直接认为是gbk编码以方便中文搜索。参考了grepwin和ripgrep的源码。

输出到console会对rg速度有些影响，建议只在搜索中文时使用--pre参数。

emacs helm可以这样设置:

```
(defun chinese-char-p (char)
    (if (string-match "\\cC\\{1\\}" (string char))
    t
    nil)
)
(require 'cl-lib)
(defun chinese-word-chinese-string-p (string)
    "Return t if STRING is a Chinese string."
    (cl-find-if 'chinese-char-p (string-to-list string))
)

;; helm
(defadvice helm-grep-ag-prepare-cmd-line (around my-helm-grep-ag-prepare-cmd-line activate)
(if (chinese-word-chinese-string-p (ad-get-arg 0))
    (let ((helm-grep-ag-command (concat helm-grep-ag-command " --pre rgpre")))
    ad-do-it)
    ad-do-it)
)

;; rg.el
(defadvice rg-build-command (around my-rg-build-command activate)
    (if (chinese-word-chinese-string-p (ad-get-arg 0))
    (let ((rg-command-line-flags (list "--pre rgpre")))
    ad-do-it
    )
    ad-do-it)
)
```

调试
----
console窗口`rgpre file`就可以看到输出。

## 感谢 ##
ripgrep, grepwin，rust，encoding_rs，they are all awesome!
