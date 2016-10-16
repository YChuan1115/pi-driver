#CROSS_COMPILE = arm-linux-

CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar

TARGETROOTFS=/home/work/filesystem/rootfs

all: dial send-mms  send-msg-pdu

install: dial send-mms send-msg-pud send-msg test
	sudo cp $^ $(TARGETROOTFS)/bin
	sudo cp *.utf8 $(TARGETROOTFS)/bin
	sudo cp phone-voice.txt $(TARGETROOTFS)/mnt
	sudo cp phone-mms.txt $(TARGETROOTFS)/mnt

dial: gsm.o uart.o 
	$(CC) dial-voice.c gsm.o uart.o -o $@

send-mms: gsm.o uart.o 
	$(CC) send-mms.c gsm.o uart.o  -o $@

send-msg-pdu: gsm.o uart.o send-msg-pdu.c
	$(CC) send-msg-pdu.c gsm.o uart.o  -o $@

send-msg: gsm.o uart.o 
	$(CC) send-msg.c gsm.o uart.o  -o $@
gsm.o:
	$(CC) -c gsm.c

#mms.o:
#	$(CC) -c mms.c

uart.o:
	$(CC) -c uart.c

#shm.o:
#	$(CC) -c shm.c
 	
clean :
	rm -rf dial
	rm -rf send-mms
	rm -rf gsmd
	rm -rf test
	rm -rf send-msg
	rm -rf send-msg-pdu
	rm -rf *.o
