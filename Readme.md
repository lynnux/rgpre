# rgpre #

A tool for `rg --pre`.

Read file to console, automatically recognize file encoding, include ansi, utf16le, utf16be, utf8. Currently output ansi as gbk for chinese text search.

Usage
=====
`rg --pre rgpre ����`


����˵��
=====
rg�и�������ֻ���Զ�����bomʶ��utf-8,utf16�ȣ�����֮����gbk������ļ���ֻ����`rg -Egbk`��������������е㲻���㡣�����߸���rg�ṩ��--pre����˵����д���ɣ��Զ�ʶ���ļ����벢�����������console��rg������֧�ֱ�����ansi��utf16le/be��utf8��Ŀǰansiֱ����Ϊ��gbk�����Է��������������ο���grepwin��ripgrep��Դ�롣
�����console���rg�ٶ���ЩӰ�죬����ֻ����������ʱʹ��--pre������emacs��

����
----
console����`rgpre file`�Ϳ��Կ��������

## ��л ##
ripgrep, grepwin��rust��encoding_rs��they are all awesome!
