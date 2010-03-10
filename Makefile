
#LIBS_PC = -lminigui -lpthread -lc -lm -ljpeg -lmgext -lttf -lpng -I/usr/local/include -L/usr/local/lib

LIBS_PC = -lminigui -lpthread -lc -lm -ljpeg -lmgext -lttf -lpng -I/opt/crosstool/gcc-3.4.5-glibc-2.3.5/armv5te-softfloat-linux/include -L/usr/local/lib -lmgext
LIBS = -lminigui -lpthread -lc -lm -ljpeg -lmgext -lttf -lpng -lz -I/opt/crosstool/gcc-3.4.5-glibc-2.3.5/armv5te-softfloat-linux/include -L/opt/crosstool/gcc-3.4.5-glibc-2.3.5/armv5te-softfloat-linux/lib

S1 = main.c memoire.c kb.c lisen.c taskbar.c tty.c gprs.c alarm.c counter.c  monthcal.c mplayer.c musicadd.c \
notes.c more_note.c viewnote.c addnote.c edit_note.c phonenumber.c pthread.c send_msg.c sentmsg.c writemsg.c drafts.c \
inbox.c messaging.c del.c addedit.c ans.c contacts.c keyboard.c coolbar.c phone_set.c time_set.c salutation_set.c bomb.c \
call.c message_read_com.c call_records.c ziyuanguanliqi.c 3g.c 3gadd.c 3g2.c  network.c connect.c nonconnect.c

S = main.c memoire.c tty.c mplayer.c musicadd.c coolbar.c ziyuanguanliqi.c \
    3g.c 3gadd.c 3g2.c  network.c connect.c nonconnect.c \
    cmds.c  cmdtab.c  domacro.c  ftp.c  glob.c  miniftp.c  ruserpass.c



pc:$(S)
	gcc -g -o pda $(S) $(LIBS_PC)
#	cp pda ../

arm345:$(S)
	armv5te-softfloat-linux-gcc -o pda $(S) $(LIBS)
	cp pda /nfs/arm9_fs_k27bsp_3.4.5/usr/bin/

arm345s:$(S)
	armv5te-softfloat-linux-gcc -o pda $(S) $(LIBS)
	cp pda /nfs/arm9_fs_k27src_3.4.5/usr/bin/

arm432:$(S)
	arm-none-linux-gnueabi-gcc -o pda $(S) -lminigui -lpthread -lc -lm -ljpeg -lmgext -lttf -lpng -lz -I/opt/crosstool/arm-2008q3/arm-none-linux-gnueabi/include -L/opt/crosstool/arm-2008q3/arm-none-linux-gnueabi/lib
	cp pda /nfs/arm9_fs_k27bsp_4.3.2/home/pda/
clean:
	rm -f pda
