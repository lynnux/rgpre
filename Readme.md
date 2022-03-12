# rgpre #

A tool for `rg --pre`.

Read file to console, automatically recognize file encoding, include ansi, utf16le, utf16be, utf8. Currently output ansi as gbk for chinese text search.

Usage
=====
`rg --pre rgpre ����`


����˵��
=====
rg�и�������ֻ���Զ�����bomʶ��utf-8,utf16�ȣ�����֮����gbk������ļ���ֻ����`rg -Egbk`��������������е㲻���㡣�����߸���rg�ṩ��--pre����˵����д���ɣ��Զ�ʶ���ļ����벢�����������console��rg������֧�ֱ�����ansi��utf16le/be��utf8��Ŀǰansiֱ����Ϊ��gbk�����Է��������������ο���grepwin��ripgrep��Դ�롣

�����console���rg�ٶ���ЩӰ�죬����ֻ����������ʱʹ��--pre������

emacs helm������������:

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

����
----
console����`rgpre file`�Ϳ��Կ��������

## ��л ##
ripgrep, grepwin��rust��encoding_rs��they are all awesome!
