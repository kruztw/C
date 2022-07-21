import marshal

code = """
def main():
    print("hello world")
"""

o = compile(code, '', 'exec')
o = marshal.dumps(o)

for c in o:
    print(hex(c), end=',')

print()
