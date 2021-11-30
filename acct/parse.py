acct_v3 = {"ac_flag":1, "ac_version":1, "ac_tty":2, "ac_exitcode":4, "ac_uid":4, "ac_gid":4, "ac_pid":4, "ac_ppid":4, "ac_btime":4,
           "ac_etime":4, "ac_utime":2, "ac_stime":2, "ac_mem":2, "ac_io":2, "ac_rw":2, "ac_minflt":2, "ac_majflt":2, "ac_swaps":2, "ac_comm":16}
acct_v3_size = 64

print("idx", end='   ')
for key,size in acct_v3.items():
    print(key, end = '   ')
print()

def format_print(val, padding, end=''):
    print(str(val).ljust(padding), end=end)

def parse_ac_flag(val):
    """ /usr/include/linux/acct.h """
    format_print(val, 10)

def parse_ac_version(val):
    format_print(val, 13)

def parse_ac_tty(val):
    format_print(val, 9)

def parse_ac_exitcode(val):
    format_print(val, 14)

def parse_ac_uid(val):
    format_print(val, 9)

def parse_ac_gid(val):
    format_print(val, 9)

def parse_ac_pid(val):
    format_print(val, 9)

def parse_ac_ppid(val):
    format_print(val, 10)

def parse_ac_btime(val):
    format_print(hex(val)[2:], 11)

def parse_ac_etime(val):
    format_print(hex(val)[2:], 11)

def parse_ac_utime(val):
    format_print(hex(val)[2:], 11)

def parse_ac_stime(val):
    format_print(hex(val)[2:], 11)

def parse_ac_mem(val):
    format_print(hex(val)[2:], 9)

def parse_ac_io(val):
    format_print(hex(val)[2:], 8)

def parse_ac_rw(val):
    format_print(hex(val)[2:], 8)

def parse_ac_minflt(val):
    format_print(hex(val)[2:], 12)

def parse_ac_majflt(val):
    format_print(hex(val)[2:], 12)

def parse_ac_swaps(val):
    format_print(hex(val)[2:], 11)

def parse_ac_comm(command):
    print(command.decode().replace('\x00', ''), end='\n')

def parse_acct_v3(data):
    pos = 0
    
    parse_ac_flag(int.from_bytes(data[pos:pos+1], "little"))
    pos += 1

    parse_ac_version(int.from_bytes(data[pos:pos+1], "little"))
    pos += 1
    
    parse_ac_tty(int.from_bytes(data[pos:pos+2], "little"))
    pos += 2

    parse_ac_exitcode(int.from_bytes(data[pos:pos+4], "little"))
    pos += 4

    parse_ac_uid(int.from_bytes(data[pos:pos+4], "little"))
    pos += 4
    
    parse_ac_gid(int.from_bytes(data[pos:pos+4], "little"))
    pos += 4
    
    parse_ac_pid(int.from_bytes(data[pos:pos+4], "little"))
    pos += 4

    parse_ac_ppid(int.from_bytes(data[pos:pos+4], "little"))
    pos += 4
    
    parse_ac_btime(int.from_bytes(data[pos:pos+4], "little"))
    pos += 4
    
    parse_ac_etime(int.from_bytes(data[pos:pos+4], "little"))
    pos += 4
    
    parse_ac_utime(int.from_bytes(data[pos:pos+2], "little"))
    pos += 2

    parse_ac_stime(int.from_bytes(data[pos:pos+2], "little"))
    pos += 2
    
    parse_ac_mem(int.from_bytes(data[pos:pos+2], "little"))
    pos += 2
    
    parse_ac_io(int.from_bytes(data[pos:pos+2], "little"))
    pos += 2
    
    parse_ac_rw(int.from_bytes(data[pos:pos+2], "little"))
    pos += 2
    
    parse_ac_minflt(int.from_bytes(data[pos:pos+2], "little"))
    pos += 2
    
    parse_ac_majflt(int.from_bytes(data[pos:pos+2], "little"))
    pos += 2
    
    parse_ac_swaps(int.from_bytes(data[pos:pos+2], "little"))
    pos += 2
    
    parse_ac_comm(data[pos:pos+16])

with open('log', 'rb') as f:
    data = b''.join(f.readlines())
    for i in range(0, len(data), acct_v3_size):
        format_print(i//acct_v3_size, 6)
        parse_acct_v3(data[i:])
    
