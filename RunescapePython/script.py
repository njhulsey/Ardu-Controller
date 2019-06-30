import serial
import pyautogui as screen 
from time import sleep
import win32api, win32con
from const import AccountType
from hiscores import Hiscores

# 


x, y = screen.position()
ser = serial.Serial('COM15',128000, bytesize=8, parity='N', stopbits=1, timeout=0.031);
print("COM Port Open")
saved_x = 0
saved_y = 0
sleep(2)

print("Creating Player")
player = Hiscores('Nichoz');

ser.write('0Nichoz:'.encode());
sleep(0.05)

send = "1"+str(player.skills['hitpoints'].level)+ ":"
ser.write(send.encode());
sleep(0.05)

send = "2"+str(player.skills['attack'].level)+ ":"
ser.write(send.encode());
sleep(0.05)

send = '3'+str(player.skills['strength'].level) + ":"
ser.write(send.encode());
sleep(0.05)

send = '4'+str(player.skills['defence'].level) + ":"
ser.write(send.encode());

send = '5'+str(player.skills['ranged'].level) + ":"
ser.write(send.encode());
sleep(0.05)

send = '6'+str(player.skills['magic'].level) + ":"
ser.write(send.encode());
sleep(0.05)


'''
'K' - > allows for movement of WASD (when up button and joystick are moving)
''

'''

while True:
	data = ser.read(20);
	if len(data) > 0:
		data = str(data).lstrip("b").strip("'").rstrip("\\r\\n");
		data = data.split(':') #extract Data
		#print("Raw Data:", data,'\n');

		if(data[0] == 'K' and len(data) >= 9):
			#print(data)
			if(data[1] == 'W'):
				if(data[2] == 'D'):
					win32api.keybd_event(0x57, 0, 0, 0)
				else:
					win32api.keybd_event(0x57, 0, win32con.KEYEVENTF_KEYUP, 0)
			
			if(data[3] == 'A'):
				if(data[4] == 'D'):
					win32api.keybd_event(0x41, 0, 0, 0)
				else:
					win32api.keybd_event(0x41, 0, win32con.KEYEVENTF_KEYUP, 0)
			
			if(data[5] == 'S'):
				if(data[6] == 'D'):
					win32api.keybd_event(0x53, 0, 0, 0)
				else:
					win32api.keybd_event(0x53, 0, win32con.KEYEVENTF_KEYUP, 0)
			
			if(data[7] == 'D'):
				if(data[8] == 'D'):
					win32api.keybd_event(0x44, 0, 0, 0)
				else:
					win32api.keybd_event(0x44, 0, win32con.KEYEVENTF_KEYUP, 0)



		if(data[0] == 'M' and len(data) >= 3):
			#print(data)
			if(data[1] != '' and data[1] != '-'):
				x  += -1 * int(data[1])
			if(data[2] != '' and data[2] != '-'):
				y += 1 * int(data[2])
			win32api.SetCursorPos((x,y))

		if(data[0] == 'B' and len(data) >= 3):
			if(data[1] == 'R'):
				win32api.mouse_event(win32con.MOUSEEVENTF_LEFTDOWN,x,y,0,0) 
				sleep(0.05)
				win32api.mouse_event(win32con.MOUSEEVENTF_LEFTUP,x,y,0,0) 
			if(data[1] == 'L'):
				win32api.mouse_event(win32con.MOUSEEVENTF_RIGHTDOWN,x,y,0,0) 
				sleep(0.05)
				win32api.mouse_event(win32con.MOUSEEVENTF_RIGHTUP,x,y,0,0) 

			if(data[1] == 'D'):
				if(saved_y == 0 and saved_x == 0):
					saved_x, saved_y = screen.position()
				else:
					win32api.SetCursorPos((saved_x,saved_y))
					x = saved_x
					y = saved_y

ser.close()