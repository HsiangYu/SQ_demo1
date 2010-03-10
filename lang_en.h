

#define NET_SERVER			"ftp.sq.com.tw"//"ftp.sq.com.tw"//"www.sq.com.tw"
#define NET_USER			"3gtest2"
#define NET_PASSWORD			"3gtest2"

/*
#define NET_SERVER			"192.168.5.74"//"www.sq.com.tw"
#define NET_USER			"sq"
#define NET_PASSWORD			"123456"
*/

//file define
#define FILE_PHONELIST			"./phonelist"
#define FILE_SAVE_MSG_DAT             	"./file1.dat"
#define FILE_SEND_MSG_DAT             	"./file2.dat"
#define FILE_READ_MSG_DAT             	"./file3.dat"
#define FILE_INBOX_DAT                	"./file3.dat"
#define FILE_LAST_TIME_DAT            	"./lasttime.dat"
#define FILE_RECEIVED_CALLS_DAT       	"./received_call.dat"
#define FILE_MISSED_CALL_DAT		"./missed_call.dat"
#define FILE_DIALED_CALL_DAT		"./dialed_call.dat"

#define FILE_ALLCALLTIME_DAT		"./allcalltime.dat"
#define FILE_BACKGROUND_BMP		"/usr/local/lib/minigui/res/bmp/bmp.bmp"
#define FILE_TMP_BMP			"/tmp/tmp.bmp"
#define FILE_MPLAYER_AP			"mplayer"
#define FILE_MPLAYER_DIR		"/"
#define FILE_MUSIC_TMP_FILE		"/tmp/a.txt"
#define FILE_SERVER_DAT       		"./server.dat"
#define FILE_3G_FIN_DAT       		"/tmp/fin.tmp"
#define FILE_3G_FOUT_DAT       		"/tmp/fout.tmp"


//msg define

#define MSG_ERROR                       "error"
#define MSG_RETURN                      "Return"
#define MSG_SAVE                        "Save"
#define MSG_DELECT                      "Delect"
#define MSG_OK                          "Acknowledge"
#define MSG_CANCEL                      "Cancel"

#define MSG_ON                          "On"
#define MSG_OFF                         "off"
#define MSG_INDICATION                  "Indication"

#define FILE_FILE_ERROR			"Open File failed!!"
#define MSG_CREAT_FILE_ERROR            "Creat File failed!!"
#define MSG_READ_FILE_ERROR             "Read File failed!!"

#define MSG_ACCEPT                      "Accept"
#define MSG_REJECT                      "Reject"

#define MSG_YES                         "Yes"
#define MSG_NO                          "No"


#define MSG_CONGRATULATION              "Congratulation!!!"
#define MSG_SUCCESS                     "Success"
#define MSG_NEW                         "New"
#define MSG_EXIT                        "Exit"

#define MSG_CLEAR                       "Clear"
#define MSG_ADD                         "Add"
#define MSG_EDIT                        "Edit"

//main.c
#define MSG_PHONEBOOK                   "PhoneBook"
#define MSG_ALARM_CLOCK                 "Alarm Clock"
#define MSG_CALCULATION                 "calculation"
#define MSG_GAME                        "Game"
#define MSG_CALENDAR                    "Calendar"
#define MSG_MUTIMEDIA_PLAYER            "Mutimedia Player"
//#define MSG_3G_CONNECT                  "3G Connect"
#define MSG_TALK_TIME                   "Talk Time"
#define MSG_3G_CONNECT                  "3G Connect"
#define MSG_MINIFTP                         "miniftp"

#define MSG_AUDIO_COMMMUNICATION        "Audio Commmunication"
#define MSG_SYSTEM_SETTING              "System Setting"
#define MSG_DATA                        "Data"
#define MSG_NOTE                        "Note"
#define MSG_MEMO                        "Memo"
#define MSG_RESOURCE_MANAGE             "Resource Manage"

#define MSG_PDA                         "PDA"
#define MSG_SQ_PDA                      "SQ PDA v0.1 build 20100310-1201"
#define MSG_TOOL                        "TOOL"
#define MSG_HELLO                       "Hello World"
#define MSG_OPEN                        "Open"
#define MSG_TIME_OUT                    "Time Out"


//messaging.c
#define MSG_MESSAGE                     "Message"

#define MSG_WRITE_MESSAGE               "Write Message"
#define MSG_MAILBOX                     "MailBox"
#define MSG_DRAFT_BOX                   "Draft Box"
#define MSG_SEND_BOX                    "Send Box"

//writemsg.c
#define MSG_SEND                        "Send"
#define MSG_WRITE_NEW_MESSAGE           "Write New Message"

//sned_msg.c
#define MSG_SEND_MSG                    "Send Message"

//sentmsg.c
#define MSG_SENTMSG                     "Sent Message"


//last_time.c
#define MSG_LAST_TIME_TALK_TIME         "Last Time Talk Time"

//all_time.c
#define MSG_ALL_TIME                    "All Communicate Time"

//received_calls.c
#define MSG_RECEIVED_CALLS              "received calls"
//.c
#define MSG_LAST_TALK_TIME              "Last Talk Time"
#define MSG_TOTAL_TALK_TIME             "Total Talk Time"

//inbox.c
#define MSG_VIEW                        "View"


//keyboard.c
#define MSG_NUMBER                      "Number:"
#define MSG_INPUT_NUMBER                "Input Number"

#define MSG_CALL                        "Call"
#define MSG_MORE_DATA                   "More..."
#define MSG_KEYBOARD                    "Keyboard"
#define MSG_HUNG_UP                     "Hung Up"

//alarm.c
#define MSG_HOUR                        "Hour"
#define MSG_MINUTE                      "Minute"
#define MSG_SECORD                      "Secord"
#define MSG_STATUS                      "Status"
#define MSG_SET_ALARM_CLOCK             "Set Alarm Clock"
#define MSG_SOFT_DISK                   "SoftDisk"
#define MSG_DISPLAY_TIME                "%dYear %dMonth %dDay - %dHout %dMinute %dSecond"
#define MSG_SET_OK                      "Setting OK"
#define MSG_ILLEGAL_SET                 "Illegal Setting"


//ziyuanguanliqi.c
#define MSG_PATH                        "Path :"
#define MSG_DEL_FILE                    "You Delect file is :\n"

//phonenumber.c
#define MSG_PHONE_NUMBER                "Phone Number"


//missed_calls.c
#define MSG_DIAL                        "Dial"
#define MSG_MISSED_CALL                 "Missed Call"


//call_records
#define MSG_DIALED_CALLS                "Dialed Calls"
#define MSG_DELETE_ALL                  "Delete All"
#define MSG_AIR_TIME                    "Air Time"

//call.c
#define MSG_PHONE_CALL                  "you have a phone call"


//addnote.c
#define MSG_ADD_NOTE                    "Add Note"

//addedit.c
#define MSG_ADD_CONTACT                 "Add Contact"
#define MSG_NAME                        "Name "

//drafts.c
#define MSG_DRAFT                       "Draft"

//bomb.c
#define MSG_STEPPED_ON                  "stepped on!!"

//del.c
#define MSG_DELECT_CONTACT_PERSONS      "Delect Contact Persons"


//mplayer.c
#define MSG_MPLAYER                     "mplayer"
#define MSG_STOP                        "Stop"
#define MSG_PLAY                        "Play"
#define MSG_PAUSE                       "Pause"
#define MSG_MP_CLOSE                    "Close"
#define MSG_WANT_DELECT                 "Do You Want To Delect?"
#define MSG_WANT_SELECT                 "Do You Want To Select?"

//musicadd.c
#define MSG_MUSIC_NAME                  "Music Name"
#define MSG_SINGER                      "singer"
#define MSG_SELECT                      "Select"
#define MSG_ADD_MUSIC                   "Add Music"


//edit_note.c
#define MSG_EDIT_NOTE                   "Edit Note"


//time_set.c
#define MSG_DAY                         "Day"
#define MSG_MONTH                       "Month"
#define MSG_YEAR                        "Year"
#define MSG_TIME_FORMAT                 "Time Format"
#define MSG_TIME_SETTING                "Time Setting"
#define MSG_DATE_SETTING                "Date Setting"

//holding.c
#define MSG_ON_THE_PHONE                "On The Phone"

//viewnote.c
#define MSG_VIEW_NOTE                   "View Note"

//taskbar
#define MSG_INPUT_METHOD                "input method"

//pthread.c
#define MSG_NEW_MESSAGE1                "You Have New Message"
#define MSG_NEW_MESSAGE                 "New Message"


//phone_set.c
#define MSG_PHONE_SET                   "phone set"
#define MSG_PHONE_SET1                  "1.Time Set"
#define MSG_PHONE_SET2                  "2.Hello Set"

//contacts.c
#define MSG_OPTION                      "Option"
#define MSG_ADD_FRIEND                  "Add Friend"
#define MSG_READ_PHTOLIST_ERROR         "Read Phtolist Error"


//3g.c
#define MSG_3G				"3G"
#define MSG_CONNECT                     "Connect"
#define MSG_ADD_FILE                    "Add File"
#define MSG_DOWNLOAD			"DownLoad"
#define MSG_DOWNLOAD_FILE               "You DownLoad file is :\n"
#define MSG_TARGET_DIR                  "/mnt/sd/demo"
#define MSG_SERIVER                     "Seriver"
#define MSG_VIEW                        "View"




