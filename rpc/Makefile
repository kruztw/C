all:
	rpcgen ./math.x
	gcc -o client math_req.c math_clnt.c math_xdr.c -lnsl
	gcc -o server math_proc.c math_svc.c math_xdr.c -lnsl

info:
	rpcinfo

init:
	sudo apt install rpcbind

clean:
	rm math.h math_clnt.c math_svc.c math_xdr.c client server
