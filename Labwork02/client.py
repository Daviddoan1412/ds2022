from aifc import Error
from xmlrpc.client import MultiCall, ServerProxy,Binary
import os
import datetime
from tkinter import Tk
from tkinter.filedialog import askopenfilename
from xmlrpc.server import XMLRPCDocGenerator

tk=Tk()
tk.geometry('100x200')
tk.withdraw()
filename=askopenfilename()

date_time_file_tranfer=os.stat(filename).st_ctime
time=datetime.date.fromtimestamp(date_time_file_tranfer)
time.strftime('%d-%m-%Y')

file=open(filename,'rb')
factory_bin=Binary(file.read())

try:
    Proxy=ServerProxy('http://localhost:3000')
    Proxy.file_transfer(factory_bin,filename,date_time_file_tranfer)
except Error as v:
    print("ERROR", v)