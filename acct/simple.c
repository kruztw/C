// 參考: https://man7.org/linux/man-pages/man5/acct.5.html
// 參考: http://www.cs.albany.edu/~sdc/CSI500/linux-2.6.31.14/Documentation/DocBook/kernel-api/re483.html
// acct(filename) : accounting (呼叫 sys_acct)
// 設定 acct(xxx) 之後, 每當有程序使用到 xxx, 在離開之後會在 xxx 留下 struct acct_v3 的紀錄
// 中止方式: filename == NULL

// 測試方式:
// gcc simple.c -o simple
// touch log
// ./simple &                # 需 root 權限
// wc ./log                 # 10 秒內會發現它持續增加, 當 acct(NULL) 被呼叫後, 就不會再增加了

// 解析: https://ctftime.org/task/16807
// dump-acct log | nl -v 0 | less
// lastcomm --pid -f log | tac | nl -v 0 | less

#include <stdio.h>
#include <unistd.h>
#include <sys/acct.h>

int main()
{
    acct("./log");
    sleep(10);         // 在這 10s 內只要有程序使用到 flag 就會在 flag 後面加上 acct_v3 的結構
    acct(NULL);
}
