#
# simple gui app with four buttons to send commands 'l','r','b','f'
# via TCP on port 1122 to an Android tablet
#
# app is used to control an arduino robot which is attached via bluetooth
# to an android tablet
#
# Apache License 2.0
# http://www.apache.org/licenses/LICENSE-2.0.html
#
# 2013, Bearstech, Marcus Bauer
#


import socket
import Tkinter
from Tkinter import *

#------------
# tcp socket
#------------
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#-----------
# callbacks
#-----------
def cbConnect():
	ip = entryIP.get()
	port = int(entryPort.get())	
	try:
		s.connect((ip, port))
		strLabel.set('ok')
	except socket.error, msg:
		strLabel.set(msg)
	s.send('ready\n')

def cbFor():
	s.send('f\n')

def cbBack():
	s.send('b\n')

def cbLeft():
	s.send('l\n')

def cbRight():
	s.send('r\n')

#----------------
# user interface
#----------------

# root window
root = Tk()
root.title('Robo Control')

# layout frames
frame1 = Frame(root)
frame1.pack()
frame2 = Frame(root)
frame2.pack(side=BOTTOM, padx=20)

# fields and button for ip, port and connection
Label(frame1, text='IP: ').pack(side=LEFT, pady=10)
entryIP = Entry(frame1, width=10)
entryIP.pack(side=LEFT)
entryIP.insert(0, '192.168.0.10')

Label(frame1, text='  Port: ').pack(side=LEFT)
entryPort = Entry(frame1, width=5)
entryPort.pack(side=LEFT)
entryPort.insert(0,'1122')

btnConnect  = Button(frame1, text='Connect', command=cbConnect)
btnConnect.pack(side=LEFT, pady=10)

strLabel = StringVar()
label = Label(frame1, textvariable=strLabel, text='-')
label.pack(side=LEFT)

#
# motion buttons
#
btnFor  = Button(frame2, text='forward',  command=cbFor)
btnLeft = Button(frame2, text='<< left',  command=cbLeft)
btnRight= Button(frame2, text='right >>', command=cbRight)
btnBack = Button(frame2, text='backward', command=cbBack)

btnFor.pack  (side=LEFT, pady=10)
btnLeft.pack (side=LEFT)
btnRight.pack(side=LEFT)
btnBack.pack (side=LEFT)

# main loop
root.mainloop()
