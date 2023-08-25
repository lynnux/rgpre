# rgpre #

A tool for `rg --pre`.

Read file to console, automatically recognize file encoding, include ansi, utf16le, utf16be, utf8. Currently output ansi as gbk for chinese text search.

Usage
=====
`rg --pre rgpre 中文`


中文说明
=====
rg能自动识别编码很少，要搜索gbk编码的文件，只能指定编码如`rg -Egbk`，这很不方便。本工具根据rg提供的--pre参数说明编写而成，自动识别文件编码并把内容输出到console供rg搜索，支持编码有ansi，utf16le/be，utf8，目前ansi直接指定为gbk编码以方便中文搜索。参考了grepwin和ripgrep的源码。

输出到console会对rg速度有些影响，建议只在搜索中文时使用--pre参数。

emacs可以这样设置，只在搜索中文时开启`--pre rgpre`:

```
(defun chinese-char-p (char)
  (if (string-match "\\cC\\{1\\}" (string char))
      t
    nil))

(defun chinese-word-chinese-string-p (string)
  "Return t if STRING is a Chinese string."
  (cl-find-if 'chinese-char-p (string-to-list string)))

;; consult-ripgrep老版本
(defadvice consult--ripgrep-builder (around my-consult--ripgrep-builder activate)
             (if (chinese-word-chinese-string-p (ad-get-arg 0))
                 (let ((consult-ripgrep-args (concat consult-ripgrep-args " --pre rgpre")))
                   ad-do-it
                   )
               ad-do-it))

;; consult-ripgrep新版本
(define-advice consult--ripgrep-make-builder (:around (fn &rest args) fallback)
      (let ((maker (apply fn args)))
        (lambda (input)
          (let ((result (funcall maker input)))
            (when (chinese-word-chinese-string-p input)
              (let ((cmds (car result)))
                ;; 经测试不能包含--search-zip参数，不然搜索不到
                (setq cmds (delete "--search-zip" cmds))
                (setq result (append (list (append (list (car cmds)) (list "--pre" "rgpre") (cdr cmds)))
                                     (cdr result)))))
            result))))

;; helm
(defadvice helm-grep-ag-prepare-cmd-line (around my-helm-grep-ag-prepare-cmd-line activate)
             (if (chinese-word-chinese-string-p (ad-get-arg 0))
                 (let ((helm-grep-ag-command (concat helm-grep-ag-command " --pre rgpre")))
                   ad-do-it)
               ad-do-it))

;; rg.el
(defadvice rg-build-command (around my-rg-build-command activate)
      (if (chinese-word-chinese-string-p (ad-get-arg 0))
          (let ((rg-command-line-flags (list "--pre rgpre")))
            ad-do-it
            )
        ad-do-it))
```

调试
----
console窗口`rgpre file`就可以看到输出。

## 感谢 ##
ripgrep, grepwin，rust，encoding_rs，they are all awesome!
